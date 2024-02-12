// -*-C++-*-
//
// File: object_file.cpp
// Project: nooblink
//

#include <vocabulary/object_file.h>
// nooblink
#include <utility/conversion.h>
#include <vocabulary/symbol_table_entry.h>
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
    d_sectionHeaders.emplace_back(i, sectionTableEntry);
    entryPtr += sectionHeaderSize;
  }

  if (d_sectionHeaders.empty()) {
    spdlog::error("No sections found in the object file '"s + d_backingFilePath.c_str() + "'");
    return;
  }
  // ELF header has the index for the section header name string, stash that index
  if ((d_strTabSectionIndex = d_elfHeader->sectionNameIndex()) >= 0xff00) {
    d_strTabSectionIndex = std::get<1>(d_sectionHeaders[0]).link();
  }
}

void ObjectFile::loadSymbolTable() {
  // Filter in Symbol sections
  for (const SectionHeaderWithIndex& sectionHeader :
       d_sectionHeaders | std::views::filter([](const SectionHeaderWithIndex& sectionHeaderWithIndex) {
         const auto& [index, header] = sectionHeaderWithIndex;
         return (header.type() == SectionType::e_Symtab || header.type() == SectionType::e_Dynsym);
       })) {
    const auto& [index, header] = sectionHeader;

    size_t nbSymbolEntries = header.size() / RawSymbolTableEntry::extent;
    std::vector<SymbolTableEntry> symbols;
    symbols.reserve(nbSymbolEntries);
    constexpr size_t entrySize = RawSymbolTableEntry::extent;
    auto* symbolStart = reinterpret_cast<std::byte*>(header.offset());
    std::advance(symbolStart, d_offsetBegin);
    for (size_t i = 0; i != nbSymbolEntries; ++i) {
      RawSymbolTableEntry rawSymbolTableEntry(symbolStart, entrySize);
      symbols.emplace_back(rawSymbolTableEntry);
      symbolStart += entrySize;
    }
    d_symbolTableEntries.emplace(index, std::move(symbols));
  }
}

ObjectFile::State ObjectFile::currentState() const { return d_currentState; }

std::string_view ObjectFile::extractStringFromTable(size_t sectionHeaderIndex, size_t stringIndex) const {
  const auto& [idx, strSectionHeader] = d_sectionHeaders[sectionHeaderIndex];
  auto* stringStart = reinterpret_cast<char*>(strSectionHeader.offset());
  std::advance(stringStart, d_offsetBegin);
  std::advance(stringStart, stringIndex);
#pragma clang diagnostic push
#pragma ide diagnostic ignored "LocalValueEscapesScope"
  return {stringStart};
#pragma clang diagnostic pop
}

nlohmann::json ObjectFile::json() const {
  using json = nlohmann::json;
  json j;

  j["ELFHeader"] = d_elfHeader->json();

  std::vector<nlohmann::json> decodedSections;

  std::transform(d_sectionHeaders.begin(), d_sectionHeaders.end(), std::back_inserter(decodedSections), [this](auto e) {
    const auto& [index, section] = e;
    json k;
    k["name"] = extractStringFromTable(d_strTabSectionIndex, section.nameIndex());
    k["section"] = section.json();
    return k;
  });

  j["sectionHeaders"] = decodedSections;

  std::vector<nlohmann::json> decodedSymbolTableEntries;
  for (const auto& indexedSymbols : d_symbolTableEntries) {
    const auto& [idx, symbols] = indexedSymbols;
    std::transform(symbols.begin(), symbols.end(), std::back_inserter(decodedSymbolTableEntries), [this, idx](auto e) {
      json k;
      k["name"] = extractStringFromTable(std::get<1>(d_sectionHeaders[idx]).link(), e.nameIndex());
      k["section"] = Conversion::toString(std::get<1>(d_sectionHeaders[idx]).type());
      k["symbol"] = e.json();
      return k;
    });
  }
  j["symbols"] = decodedSymbolTableEntries;
  return j;
}

std::filesystem::path ObjectFile::filePath() const { return d_backingFilePath; }

}  // namespace nooblink
