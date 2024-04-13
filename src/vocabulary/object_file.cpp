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
#include <vocabulary/section_header.h>
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
#include <string_view>

namespace nooblink {
namespace {

using namespace std::string_literals;

constexpr const size_t k_ElfHeaderLength = RawElfHeader::extent;

// Utility to filter the specified 'sections' indexed section header on specified 'sectionTypes' section types
auto filteredSections(std::ranges::range auto&& sections, std::same_as<SectionType> auto&&... sectionTypes) {
  return sections | std::views::filter(
                        [sectionTypes...](const std::tuple<ObjectFile::SectionIndex, SectionHeader>& sectionHeader) {
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
      d_symbolEntries{},
      d_strTabSectionIndex{},
      d_names{} {}

ObjectFile::State ObjectFile::load(std::byte* begin) {
  try {
    d_begin = begin;
    d_offsetBegin = reinterpret_cast<uint64_t>(begin);
    loadElfHeader();
    loadSectionTable();
    loadSymbolTable();
    loadRelocationEntries();
    loadNames();
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
    d_sectionHeaders.emplace(i, sectionTableEntry);
    entryPtr += sectionHeaderSize;
  }

  if (d_sectionHeaders.empty()) {
    spdlog::error("No sections found in the object file");
    return;
  }

  // ELF header has the index for the section header name string, stash that index
  if ((d_strTabSectionIndex = d_elfHeader->sectionNameIndex()) >= 0xff00) {
    d_strTabSectionIndex = d_sectionHeaders.begin()->second.link();
  }
}

void ObjectFile::loadSymbolTable() {
  // Filter in Symbol sections
  for (const auto& sectionHeader : filteredSections(d_sectionHeaders, SectionType::e_Symtab, SectionType::e_Dynsym)) {
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
    d_symbolEntries.emplace(index, std::move(symbols));
  }
}

void ObjectFile::loadNames() {
  auto storeFromSectionIdx = [this](size_t idx) {
    if (auto iter = d_sectionHeaders.find(idx); iter != d_sectionHeaders.end()) {
      const auto& sectionHeader = iter->second;
      size_t sectionSize = sectionHeader.size();
      auto* sectionStart = reinterpret_cast<char*>(iter->second.offset());
      std::advance(sectionStart, d_offsetBegin);
      d_names.storeSection(idx, std::string_view(sectionStart, sectionSize));
    }
  };

  // Stash section names
  storeFromSectionIdx(d_strTabSectionIndex);

  // Stash symbols
  // For section 'symtab' and 'dynsym' the link field point to the section that contains the strings
  for (const auto& sectionHeader : filteredSections(d_sectionHeaders, SectionType::e_Symtab, SectionType::e_Dynsym)) {
    const auto& [sectionIndex, header] = sectionHeader;
    storeFromSectionIdx(header.link());
  }
}

void ObjectFile::loadRelocationEntries() {
  using namespace std::string_literals;

  for (const auto& sectionHeader : filteredSections(d_sectionHeaders, SectionType::e_Rel, SectionType::e_Rela)) {
    const auto& [sectionIndex, header] = sectionHeader;
    auto* relocationStart = reinterpret_cast<std::byte*>(header.offset());
    std::advance(relocationStart, d_offsetBegin);
    // For rel sections, info() will point to the section where the relocations apply, link() point to the
    // symbol section containing the symbol the relocation applies to
    const bool hasAddend = header.type() == SectionType::e_Rela;
    spdlog::debug("Found relocation entries in section "s + std::to_string(sectionIndex));
    size_t nbSymbolEntries =
        header.size() / (hasAddend ? RawRelocationEntryWithAddend::extent : RawRelocationEntry::extent);
    // size_t relocatedSectionIndex = header.info();
    size_t symbolSectionIndex = header.link();
    d_relocationsEntries[sectionIndex] = {};
    // FIXME This kinda clunkilicious...
    for (size_t i = 0; i != nbSymbolEntries; ++i) {
      if (!hasAddend) {
        RawRelocationEntry rawEntry(relocationStart, RawRelocationEntry::extent);
        RelocationEntry entry(rawEntry);
        d_relocationsEntries[sectionIndex].push_back(std::move(entry));
        relocationStart += RawRelocationEntry ::extent;
      } else {
        RawRelocationEntryWithAddend rawEntry(relocationStart, RawRelocationEntryWithAddend::extent);
        RelocationEntryWithAddend entry(rawEntry);
        d_relocationsEntries[sectionIndex].push_back(std::move(entry));
        relocationStart += RawRelocationEntryWithAddend::extent;
      }
    }
  }
}

ObjectFile::State ObjectFile::currentState() const { return d_currentState; }

nlohmann::json ObjectFile::json() const {
  using json = nlohmann::json;
  json objFileJson;

  objFileJson["ELFHeader"] = d_elfHeader->json();

  std::vector<nlohmann::json> decodedSections;

  std::transform(d_sectionHeaders.begin(), d_sectionHeaders.end(), std::back_inserter(decodedSections), [this](auto e) {
    const auto& [index, section] = e;
    json k;
    k["index"] = index;
    k["name"] = d_names.get(d_strTabSectionIndex, section.nameIndex());
    k["section"] = section.json();
    return k;
  });

  objFileJson["sectionHeaders"] = decodedSections;

  std::vector<nlohmann::json> decodedSymbolTableEntries;
  for (const auto& indexedSymbols : d_symbolEntries) {
    const auto& [idx, symbols] = indexedSymbols;
    if (auto iter = d_sectionHeaders.find(idx); iter != d_sectionHeaders.end()) {
      std::transform(symbols.begin(), symbols.end(), std::back_inserter(decodedSymbolTableEntries),
                     [this, iter](auto e) {
                       json k;
                       if (e.type() == SymbolType::e_Section) {
                         if (auto sectionHeaderIter = d_sectionHeaders.find(e.sectionHeaderIndex());
                             sectionHeaderIter != d_sectionHeaders.end()) {
                           k["name"] = d_names.get(d_strTabSectionIndex, sectionHeaderIter->second.nameIndex());
                         }
                       } else {
                         k["name"] = d_names.get(iter->second.link(), e.nameIndex());
                       }
                       k["section"] = Conversion::toString(iter->second.type());
                       k["symbol"] = e.json();
                       return k;
                     });
    }
  }
  objFileJson["symbols"] = decodedSymbolTableEntries;

  std::vector<json> relEntriesPerSectionsJson;
  for (auto&& relEntries : d_relocationsEntries) {
    std::vector<nlohmann::json> decodedRelocations;
    for (auto relEntry : relEntries.second) {
      std::visit([&decodedRelocations](auto e) { decodedRelocations.push_back(e.json()); }, relEntry);
    }
    nlohmann::json entry;
    entry["section"] = relEntries.first;
    // entry["section"] = d_names.get(d_strTabSectionIndex, relEntries.first);
    entry["relocationEntries"] = decodedRelocations;
    relEntriesPerSectionsJson.push_back(std::move(entry));
  }
  objFileJson["relocations"] = relEntriesPerSectionsJson;

  return objFileJson;
}

const ObjectFile::IndexedSymbols& ObjectFile::symbols() const { return d_symbolEntries; }

}  // namespace nooblink
