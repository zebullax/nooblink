// -*-C++-*-
//
// File: object_file.h
// Project: nooblink
//
// Description: This component wraps over and articulate the subcomponents (e.g. header, sections) that make up an
// ELF object file
//

#ifndef NOOBLINK_VOCABULARY_OBJECT_FILE_H
#define NOOBLINK_VOCABULARY_OBJECT_FILE_H

// nooblink
#include <utility/byte_util.h>
#include <utility/string_table.h>
#include <vocabulary/elf_header.h>
#include <vocabulary/relocation_entry.h>
#include <vocabulary/section_header.h>
#include <vocabulary/symbol_table_entry.h>
// nlohmann
#include <nlohmann/json.hpp>
// std
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>

namespace nooblink {

class ObjectFile {
 public:
  // TYPES

  enum class State {
    // This object does not back any loaded object file
    e_Idle,
    // This object backs a successfully loaded object file
    e_Loaded,
    // This object is not in a usable state
    e_Error,
  };

  // Alias over section index as found in object file natural order
  using SectionIndex = uint32_t;

  // Alias over a section index and the sequence of related symbol table entries. The order of symbols for a given
  // section index is left as per the original object file. The section index is critical to be able to reach the
  // strings table via the 'link' attribute; The section index should point to a 'DynSym' or 'SymTab' section header
  using IndexedSymbols = std::unordered_map<SectionIndex, std::vector<SymbolTableEntry>>;

  // Alias over both kind of possible relocation entry
  using AnyRelocationEntry = std::variant<RelocationEntry, RelocationEntryWithAddend>;

  // Alias over a lookup table from section index to relocation entries related to this section
  // {2: [rel1, rel2]} mean that 'rel1' and 'rel2' are relocations taking place in section 2
  using IndexedRelocations = std::unordered_map<SectionIndex, std::vector<AnyRelocationEntry>>;

 private:
  // FRIENDS

  // Output to the specified 'os' a JSON representation of this object, return the stream
  friend std::ostream& operator<<(std::ostream& os, const ObjectFile& objectFile) {
    os << objectFile.json();
    return os;
  }

  // DATA

  State d_currentState;
  std::byte* d_begin;      // Starting address for the loaded objectFile
  uint64_t d_offsetBegin;  // Numeric offset corresponding to `d_begin` for convenience
  std::unique_ptr<ElfHeader> d_elfHeader;
  std::unordered_map<SectionIndex, SectionHeader> d_sectionHeaders;
  IndexedRelocations d_relocationsEntries;
  IndexedSymbols d_symbolEntries;
  SectionIndex d_strTabSectionIndex;
  StringTable d_names;

  // MANIPULATORS

  // Load the content of the ELF main header
  void loadElfHeader();

  // Load all section header entries from the section header table
  void loadSectionTable();

  // Load all symbol table entries
  void loadSymbolTable();

  // Load all relocation entries
  void loadRelocationEntries();

  // Load all names for section and symbols.  Calling this before having loaded sections and symbols is undefined
  // behavior
  void loadNames();

 public:
  // CREATORS

  // Create this object backing no object file
  ObjectFile();

  // MANIPULATORS

  // Load the object file starting at the specified 'begin' address and return the state on completion. Behavior is
  // undefined if 'begin' does not point to the beginning of a valid ELF object file
  [[nodiscard]] State load(std::byte* begin);

  // ACCESSORS

  // Return the current state of this object
  [[nodiscard]] State currentState() const;

  // Render and return a json representation for this object
  [[nodiscard]] nlohmann::json json() const;

  // Return all symbols referenced or defined in this object file, indexed by their related section index
  [[nodiscard]] const IndexedSymbols& symbols() const;

  // Return all relocation entries, indexed by their related section index
  [[nodiscard]] const IndexedRelocations& relocations() const;
};

}  // namespace nooblink

#endif  // NOOBLINK_VOCABULARY_OBJECT_FILE_H
