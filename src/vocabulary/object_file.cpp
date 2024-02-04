// -*-C++-*-
//
// File: object_file.cpp
// Project: nooblink
//

#include <vocabulary/object_file.h>
// spdlog
#include <spdlog/spdlog.h>
// std
#include <algorithm>
#include <iterator>
#include <memory>
#include <ranges>
#include <string>

namespace nooblink {
namespace {

using namespace std::string_literals;

constexpr const size_t k_ElfHeaderLength = RawElfHeader::extent;

}  // namespace

ObjectFile::ObjectFile()
    : d_currentState{State::e_Idle},
      d_backingFilePath{},
      d_mMapGuard{},
      d_begin{},
      d_offsetBegin{},
      d_elfHeader{},
      d_sectionHeaders{},
      d_symbolTableEntries{},
      d_strTabSectionIndex{} {}

ObjectFile::State ObjectFile::load(const std::filesystem::path& filePath) {
  d_backingFilePath = filePath;
  try {
    spdlog::info("Loading '"s + filePath.c_str() + "'");
    d_mMapGuard = std::make_unique<MemMappedFile>(d_backingFilePath.c_str());
    d_begin = reinterpret_cast<std::byte*>(d_mMapGuard->mappedRegionStart());
    d_offsetBegin = reinterpret_cast<uint64_t>(d_begin);
    loadElfHeader();
    loadSectionTable();
    loadSymbolTable();
    return State::e_Loaded;
  } catch (const std::exception& e) {
    spdlog::error("Error while loading the object file: "s + e.what());
    return State::e_Error;
  }
}
void ObjectFile::loadElfHeader() {
  spdlog::debug("Loading ELF header");
  RawElfHeader rawElfHeader(d_begin, k_ElfHeaderLength);
  d_elfHeader = std::make_unique<ElfHeader>(rawElfHeader);
}

void ObjectFile::loadSectionTable() {
  spdlog::debug("Loading section table");
  std::byte* entryPtr = d_elfHeader->sectionTableAddress();
  std::advance(entryPtr, d_offsetBegin);
  const uint64_t nbSectionHeaders = d_elfHeader->sectionTableCount();
  const uint64_t sectionHeaderSize = d_elfHeader->sectionTableSize();
  d_sectionHeaders.reserve(d_elfHeader->sectionTableCount());

  for (size_t i = 0; i != nbSectionHeaders; ++i) {
    RawSectionHeader sectionTableEntry(entryPtr, RawSectionHeader::extent);
    d_sectionHeaders.emplace_back(sectionTableEntry);
    entryPtr += sectionHeaderSize;
  }

  if (d_sectionHeaders.empty()) {
    spdlog::error("No sections found in the object file '"s + d_backingFilePath.c_str() + "'");
    return;
  }
  // No need to loop over to find the strtab, the ELF header has the proper index set already
  if ((d_strTabSectionIndex = d_elfHeader->sectionNameIndex()) >= 0xff00) {
    d_strTabSectionIndex = d_sectionHeaders[0].link();
  }
}

void ObjectFile::loadSymbolTable() {
  // Filter sections that describe symbol tables
  for (const auto& symbolSectionHeader :
       d_sectionHeaders | std::views::filter([](const SectionHeaderTableEntry& entry) {
         return (entry.type() == SectionType::e_Symtab || entry.type() == SectionType::e_Dynsym);
       })) {
    size_t nbEntries = symbolSectionHeader.size() / RawSymbolTableEntry::extent;
    constexpr size_t entrySize = RawSymbolTableEntry::extent;
    auto* symbolStart = reinterpret_cast<std::byte*>(symbolSectionHeader.offset());
    std::advance(symbolStart, d_offsetBegin);
    for (size_t i = 0; i != nbEntries; ++i) {
      RawSymbolTableEntry rawSymbolTableEntry(symbolStart, entrySize);
      d_symbolTableEntries.emplace_back(rawSymbolTableEntry);
      symbolStart += entrySize;
    }
  }
}

ObjectFile::State ObjectFile::currentState() const { return d_currentState; }

std::string_view ObjectFile::extractStringFromTable(size_t stringIndex) const {
  auto* stringTableStart = reinterpret_cast<char*>(d_sectionHeaders[d_strTabSectionIndex].offset() + stringIndex);
  std::advance(stringTableStart, d_offsetBegin);
#pragma clang diagnostic push
#pragma ide diagnostic ignored "LocalValueEscapesScope"
  return {stringTableStart};
#pragma clang diagnostic pop
}

nlohmann::json ObjectFile::json() const {
  using json = nlohmann::json;
  json j;

  j["ELFHeader"] = d_elfHeader->json();

  std::vector<nlohmann::json> decodedSections;

  std::transform(d_sectionHeaders.begin(), d_sectionHeaders.end(), std::back_inserter(decodedSections), [this](auto e) {
    json k;
    k["name"] = extractStringFromTable(e.nameIndex());
    k["content"] = e.json();
    return k;
  });

  j["sectionHeaders"] = decodedSections;

  std::vector<nlohmann::json> decodedSymbolTableEntries;
  std::transform(d_symbolTableEntries.begin(), d_symbolTableEntries.end(),
                 std::back_inserter(decodedSymbolTableEntries), [this](auto e) {
                   json k;
                   // FIXME symbol string table is not the same as section, must look into sh_link
                   //                   k["name"] = extractStringFromTable(e.nameIndex());
                   k["content"] = e.json();
                   return k;
                 });
  j["symbols"] = decodedSymbolTableEntries;
  return j;
}

std::filesystem::path ObjectFile::filePath() const { return d_backingFilePath; }

}  // namespace nooblink
