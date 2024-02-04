// -*-C++-*-
//
// File: object_file.h
// Project: nooblink
//
// Description: This component wraps over and articulate the subcomponents (e.g. ELF header, sections) that make up an
// object file
//

#ifndef NOOBLINK_OBJECT_FILE_H
#define NOOBLINK_OBJECT_FILE_H

// nooblink
#include <io/mem_mapped_file.h>
#include <raw/byte_util.h>
#include <session/context.h>
#include <vocabulary/elf_header.h>
#include <vocabulary/section_header_table_entry.h>
#include <vocabulary/symbol_table_entry.h>
// nlohmann
#include <nlohmann/json.hpp>
// std
#include <cstddef>
#include <filesystem>
#include <functional>
#include <memory>
#include <ostream>
#include <string_view>
#include <type_traits>
#include <vector>

namespace nooblink {

class ObjectFile {
 public:
  // TYPES

  enum class State {
    e_Idle,    // This object does not back any loaded object file
    e_Loaded,  // This object backs a successfully loaded object file
    e_Error,   // This object is not in a usable state
  };

 private:
  // FRIENDS

  // Output to the specified 'os' a JSON representation of this object, return the stream
  friend std::ostream& operator<<(std::ostream& os, const ObjectFile& objectFile) {
    os << objectFile.json();
    return os;
  }

  // DATA

  State d_currentState;
  std::filesystem::path d_backingFilePath;
  std::unique_ptr<MemMappedFile> d_mMapGuard;
  std::byte* d_begin;      // Address where the backing file is being mapped to
  uint64_t d_offsetBegin;  // Numeric offset corresponding to `d_begin` for convenience
  std::unique_ptr<ElfHeader> d_elfHeader;
  std::vector<SectionHeaderTableEntry> d_sectionHeaders;
  std::vector<SymbolTableEntry> d_symbolTableEntries;
  size_t d_strTabSectionIndex;

  // MANIPULATORS

  // Load the content of the ELF main header
  void loadElfHeader();

  // Load all section header entries from the section header table
  void loadSectionTable();

  // Load all symbol table entries
  void loadSymbolTable();

  // Extract from the string table the string pointed to by the specified 'stringIndex' and return a view over it
  [[nodiscard]] std::string_view extractStringFromTable(size_t stringIndex) const;

 public:
  // CREATORS

  // Create this object backing no object file
  ObjectFile();

  // MANIPULATORS

  // Load the backing specified 'filePath' into this object and return the new state
  [[nodiscard]] State load(const std::filesystem::path& filePath);

  // ACCESSORS

  // Return the current state of this object
  [[nodiscard]] State currentState() const;

  // Render and return a json representation for this object
  [[nodiscard]] nlohmann::json json() const;

  // Return the backing filePath
  [[nodiscard]] std::filesystem::path filePath() const;
};

}  // namespace nooblink

#endif  // NOOBLINK_OBJECT_FILE_H
