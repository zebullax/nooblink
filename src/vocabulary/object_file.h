// -*-C++-*-
//
// File: object_file.h
// Project: nooblink
//
// Description: This component wraps over and articulate the subcomponents (e.g. header, sections) that make up an
// ELF object file
//

#ifndef NOOBLINK_OBJECT_FILE_H
#define NOOBLINK_OBJECT_FILE_H

// nooblink
#include <raw/byte_util.h>
#include <vocabulary/elf_header.h>
#include <vocabulary/relocation_entry.h>
#include <vocabulary/section_header_table_entry.h>
#include <vocabulary/symbol_table_entry.h>
// nlohmann
#include <nlohmann/json.hpp>
// std
#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <tuple>
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
  using SectionIndex = size_t;

  // Alias over a section index and the sequence of related symbol table entries. The order of symbols for a given
  // section index is left as per the original object file. The section index is critical to be able to reach the
  // strings table via the 'link' attribute; The section index should point to a 'DynSym' or 'SymTab' section header
  using IndexedSymbolTable = std::unordered_map<SectionIndex, std::vector<SymbolTableEntry>>;

  // Alias over both kind of possible relocation entry
  using AnyRelocationEntry = std::variant<RelocationEntry, RelocationEntryWithAddend>;

  // Alias over a lookup table from section index to relocation entries related to this section
  using IndexedRelocationEntries = std::unordered_map<SectionIndex, std::vector<AnyRelocationEntry>>;

 private:
  //  PRIVATE TYPES

  // Alias over a section header and its natural index in the object file
  using SectionHeaderWithIndex = std::tuple<SectionIndex, SectionHeaderTableEntry>;

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
  std::vector<SectionHeaderWithIndex> d_sectionHeaders;
  IndexedRelocationEntries d_relocationsEntries;
  IndexedSymbolTable d_symbolTableEntries;
  size_t d_strTabSectionIndex;

  // MANIPULATORS

  // Load the content of the ELF main header
  void loadElfHeader();

  // Load all section header entries from the section header table
  void loadSectionTable();

  // Load all symbol table entries
  void loadSymbolTable();

  // Load all relocation entries
  void loadRelocationEntries();

  // Extract from the string table the string pointed to by the specified 'stringIndex' and return a view over it.  The
  // section containing the string table is given by the specified 'sectionHeaderIndex'
  [[nodiscard]] std::string_view extractStringFromTable(size_t sectionHeaderIndex, size_t stringIndex) const;

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
  [[nodiscard]] const IndexedSymbolTable& symbols() const;

  // Return all relocation entries, indexed by their related section index
  [[nodiscard]] const IndexedRelocationEntries& relocations() const;
};

}  // namespace nooblink

#endif  // NOOBLINK_OBJECT_FILE_H
