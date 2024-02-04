// -*-C++-*-
//
// File: symbol_table_entry.h
// Project: nooblink
//
// Description: This component provides a vocabulary type covering an entry in the symbols table
//

#ifndef NOOBLINK_SYMBOL_TABLE_ENTRY_H
#define NOOBLINK_SYMBOL_TABLE_ENTRY_H

// nooblink
#include <raw/header_constants.h>
#include <raw/raw_symbol_table_entry.h>
// nlohmann
#include <nlohmann/json.hpp>
// std
#include <cstddef>
#include <ostream>

namespace nooblink {

class SymbolTableEntry {
  // This component describes an entry from the symbol table

 private:
  // DATA

  uint32_t d_nameIndex;
  uint64_t d_value;
  uint64_t d_size;
  uint16_t d_sectionHeaderIndex;
  SymbolVisibility d_visibility;
  SymbolBinding d_binding;
  SymbolType d_type;

  // PRIVATE FRIENDS
  friend std::ostream& operator<<(std::ostream& os, const SymbolTableEntry& entry) {
    auto j = entry.json();
    os << j;
    return os;
  }

 public:
  // CREATORS

  explicit SymbolTableEntry(const RawSymbolTableEntry& rawEntry);

  // ACCESSORS

  // Return the name index in the string table
  [[nodiscard]] uint32_t nameIndex() const;

  // Return this symbol visibility
  [[nodiscard]] SymbolVisibility visibility() const;

  // Return the value of this symbol
  [[nodiscard]] uint64_t value() const;

  // Return whether the symbol is undefined
  [[nodiscard]] bool isUndef() const;

  // Return the size of this symbol if it makes sense
  [[nodiscard]] uint64_t size() const;

  // Return the section header index. Every symbol table entry is defined in relation to some section. This member holds
  // the relevant section header table index.
  [[nodiscard]] uint16_t sectionHeaderIndex() const;

  // Return the symbol binding
  [[nodiscard]] SymbolBinding binding() const;

  // Return the symbol type
  [[nodiscard]] SymbolType type() const;

  // Render and return a json representation for this object
  [[nodiscard]] nlohmann::json json() const;
};

}  // namespace nooblink

#endif  // NOOBLINK_SYMBOL_TABLE_ENTRY_H
