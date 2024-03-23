// -*-C++-*-
//
// File: object_file.cpp
// Project: nooblink
//

#include <vocabulary/object_file.h>
// nooblink
#include <raw/header_constants.h>
#include <raw/raw_relocation_entry.h>
#include <raw/raw_relocation_entry_util.h>
#include <utility/conversion.h>
#include <vocabulary/relocation_entry.h>
#include <vocabulary/relocation_entry_util.h>
#include <vocabulary/section_header_table_entry.h>
#include <vocabulary/symbol_table_entry.h>
// spdlog
#include <spdlog/spdlog.h>
// std
#include <algorithm>
#include <concepts>
#include <cstddef>
#include <iterator>
#include <memory>
#include <ranges>
#include <string>

namespace nooblink {
namespace {

using namespace std::string_literals;

constexpr const size_t k_ElfHeaderLength = RawElfHeader::extent;

// Utility to filter the specified 'sections' indexed section header on specified 'sectionTypes' section types
auto filteredSections(std::ranges::range auto&& sections, std::same_as<SectionType> auto&&... sectionTypes) {
  return sections |
         std::views::filter(
             [sectionTypes...](const std::tuple<ObjectFile::SectionIndex, SectionHeaderTableEntry>& sectionHeader) {
               return ((std::get<1>(sectionHeader).type() == sectionTypes) || ...);
             });
}

}  // namespace

ObjectFile::ObjectFile()
    : d_currentState{State::e_Idle},
      d_begin{},
      d_offsetBegin{},
      d_elfHeader{},
      d_sectionHeaders{},
      d_symbolTableEntries{},
      d_strTabSectionIndex{} {}

ObjectFile::State ObjectFile::load(std::byte* begin) {
  try {
    d_begin = begin;
    d_offsetBegin = reinterpret_cast<uint64_t>(begin);
    loadElfHeader();
    loadSectionTable();
    loadSymbolTable();
    loadRelocationEntries();
    d_currentState = State::e_Loaded;
  } catch (const std::exception& e) {
    spdlog::error("Error while loading the object file: "s + e.what());
    d_currentState = State::e_Error;
  }
  return d_currentState;
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
    spdlog::error("No sections found in the object file");
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
       filteredSections(d_sectionHeaders, SectionType::e_Symtab, SectionType::e_Dynsym)) {
    const auto& [index, header] = sectionHeader;

    size_t nbSymbolEntries = header.size() / RawSymbolTableEntry::extent;
    std::vector<SymbolTableEntry> symbols;
    symbols.reserve(nbSymbolEntries);
    auto* symbolStart = reinterpret_cast<std::byte*>(header.offset());
    std::advance(symbolStart, d_offsetBegin);
    for (size_t i = 0; i != nbSymbolEntries; ++i) {
      RawSymbolTableEntry rawSymbolTableEntry(symbolStart, RawSymbolTableEntry::extent);
      symbols.emplace_back(rawSymbolTableEntry);
      symbolStart += RawSymbolTableEntry::extent;
    }
    d_symbolTableEntries.emplace(index, std::move(symbols));
  }
}

void ObjectFile::loadRelocationEntries() {
  // FIXME This kinda clunkilicious...

  for (const SectionHeaderWithIndex& sectionHeader :
       filteredSections(d_sectionHeaders, SectionType::e_Rel, SectionType::e_Rela)) {
    const auto& [index, header] = sectionHeader;
    auto* relocationStart = reinterpret_cast<std::byte*>(header.offset());
    std::advance(relocationStart, d_offsetBegin);
    // For rel sections, info() will point to the section where the relocations apply, link() point to the
    // symbol section containing the symbol the relocation applies to
    const bool hasAddend = header.type() == SectionType::e_Rela;
    size_t nbSymbolEntries =
        header.size() / (hasAddend ? RawRelocationEntryWithAddend ::extent : RawRelocationEntry::extent);
    size_t relocatedSectionIndex = header.info();
    size_t symbolSectionIndex = header.link();
    d_relocationsEntries[relocatedSectionIndex] = {};
    for (size_t i = 0; i != nbSymbolEntries; ++i) {
      if (hasAddend) {
        RawRelocationEntry rawEntry(relocationStart, RawRelocationEntry::extent);
        uint64_t symbolIndex = RawRelocationEntryUtil::offset(rawEntry);
        RelocationEntry entry{symbolIndex, RawRelocationEntryUtil::info(rawEntry)};
        d_relocationsEntries[relocatedSectionIndex].push_back(std::move(entry));
        relocationStart += RawRelocationEntryWithAddend ::extent;
      } else {
        RawRelocationEntryWithAddend rawEntry(relocationStart, RawRelocationEntryWithAddend ::extent);
        uint64_t symbolIndex = RawRelocationEntryUtil::offset(rawEntry);
        RelocationEntryWithAddend entry{symbolIndex, RawRelocationEntryUtil::info(rawEntry),
                                        RawRelocationEntryUtil::addend(rawEntry)};
        d_relocationsEntries[relocatedSectionIndex].push_back(std::move(entry));
        relocationStart += RawRelocationEntry ::extent;
      }
    }
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
  json objFileJson;

  objFileJson["ELFHeader"] = d_elfHeader->json();

  std::vector<nlohmann::json> decodedSections;

  std::transform(d_sectionHeaders.begin(), d_sectionHeaders.end(), std::back_inserter(decodedSections), [this](auto e) {
    const auto& [index, section] = e;
    json k;
    k["name"] = extractStringFromTable(d_strTabSectionIndex, section.nameIndex());
    k["section"] = section.json();
    return k;
  });

  objFileJson["sectionHeaders"] = decodedSections;

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
  objFileJson["symbols"] = decodedSymbolTableEntries;

  std::vector<json> relEntriesPerSectionsJson;
  for (auto&& relEntries : d_relocationsEntries) {
    std::vector<nlohmann::json> decodedRelocations;
    std::transform(relEntries.second.begin(), relEntries.second.end(), std::back_inserter(decodedRelocations),
                   [](auto e) {
                     json k;
                     std::visit([&k](auto e) { k["relocation"] = e.json(); }, e);
                     return k;
                   });
    nlohmann::json entry;
    entry["section"] = relEntries.first;
    entry["relocationEntries"] = decodedRelocations;
    relEntriesPerSectionsJson.push_back(std::move(entry));
  }
  objFileJson["relocations"] = relEntriesPerSectionsJson;

  return objFileJson;
}

const ObjectFile::IndexedSymbolTable& ObjectFile::symbols() const { return d_symbolTableEntries; }

}  // namespace nooblink
