// -*-C++-*-
//
// File: string_table.h
// Project: nooblink
//
// Description: This component provides a container to store and access strings as they are defined in object file
// strings table.
//
// Note: Two fundamental entities require names in an object file: sections, and symbols. For symbols, the
// symbol (SymTab, DynSym) section header point to the strings table via the link field.  For sections, the object file
// directly point to the string table via the section header string index field
//

#ifndef NOOBLINK_UTILITY_STRING_TABLE_H
#define NOOBLINK_UTILITY_STRING_TABLE_H

// std
#include <cstdint>
#include <string_view>
#include <unordered_map>

namespace nooblink {

class StringTable {
 public:
  // CREATORS
  StringTable() = default;

  // MANIPULATORS

  // Add the names from the specified 'sectionIndex' having the specified 'content'
  void storeSection(size_t sectionIndex, std::string_view content);

  // ACCESSORS

  // Return the string from the section at specified 'sectionIndex' and starting from specified 'offset'
  std::string_view get(size_t sectionIndex, uint64_t offset) const;

 private:
  // DATA
  std::unordered_map<size_t, std::string_view> d_sectionStrings;
};

}  // namespace nooblink

#endif
