// -*-C++-*-
//
// File: object_file.cpp
// Project: nooblink
//

// nooblink
#include <vocabulary/elf_header_util.h>
#include <vocabulary/object_file.h>
// spdlog
#include <spdlog/spdlog.h>
// nlohmann
#include <nlohmann/json.hpp>
// std
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <string>

namespace nooblink {
namespace {
constexpr const size_t k_ElfHeaderLength = RawElfHeader::extent;
using namespace std::string_literals;
}  // namespace

ObjectFile::ObjectFile()
    : d_currentState{State::e_Idle},
      d_backingFilePath{},
      d_mMapGuard{},
      d_mappedRegionStart{},
      d_regionStartOffset{},
      d_elfHeader{},
      d_sectionHeaders{},
      d_strTabSectionIndex{} {}

ObjectFile::State ObjectFile::load(const std::filesystem::path& filePath) {
  d_backingFilePath = filePath;
  try {
    spdlog::info("Loading '"s + filePath.c_str() + "'");
    d_mMapGuard = std::make_unique<MemMappedFile>(d_backingFilePath.c_str());
    d_mappedRegionStart = reinterpret_cast<std::byte*>(d_mMapGuard->mappedRegionStart());
    d_regionStartOffset = reinterpret_cast<uint64_t>(d_mappedRegionStart);
    loadElfHeader();
    loadSectionTable();
    return State::e_Loaded;
  } catch (const std::exception& e) {
    spdlog::error("Error while loading the object file: "s + e.what());
    return State::e_Error;
  }
}
void ObjectFile::loadElfHeader() {
  spdlog::debug("Loading ELF header");
  RawElfHeader rawElfHeader(d_mappedRegionStart, k_ElfHeaderLength);
  d_elfHeader = std::make_unique<ElfHeader>(rawElfHeader, d_regionStartOffset);
}

void ObjectFile::loadSectionTable() {
  spdlog::debug("Loading section table");
  d_sectionHeaders = ElfHeaderUtil::extractSections(*d_elfHeader);
  if (d_sectionHeaders.empty()) {
    spdlog::error("No sections found in the object file '"s + d_backingFilePath.c_str() + "'");
    return;
  }
  // No need to loop over to find the strtab, the ELF header has the proper index set already
  if ((d_strTabSectionIndex = d_elfHeader->sectionNameIndex()) >= 0xff00) {
    d_strTabSectionIndex = d_sectionHeaders[0].link();
  }
}

ObjectFile::State ObjectFile::currentState() const { return d_currentState; }

std::string_view ObjectFile::extractStringFromTable(size_t stringIndex) const {
  auto* stringTableStart = reinterpret_cast<char*>(d_sectionHeaders[d_strTabSectionIndex].offset() + stringIndex);
#pragma clang diagnostic push
#pragma ide diagnostic ignored "LocalValueEscapesScope"
  return {stringTableStart};
#pragma clang diagnostic pop
}

nlohmann::json ObjectFile::json() const {
  using json = nlohmann::json;
  json j;

  auto toString = [](auto e) {
    std::ostringstream oss;
    oss << e;
    return oss.str();
  };

  j["ELFHeader"] = d_elfHeader->json();

  std::vector<nlohmann::json> decodedSections;

  std::transform(d_sectionHeaders.begin(), d_sectionHeaders.end(), std::back_inserter(decodedSections), [this](auto e) {
    json k;
    k["name"] = extractStringFromTable(e.nameIndex());
    k["content"] = e.json();
    return k;
  });

  j["sectionHeaders"] = decodedSections;
  return j;
}

std::ostream& operator<<(std::ostream& os, const ObjectFile& objectFile) {
  os << objectFile.json();
  return os;
}

}  // namespace nooblink
