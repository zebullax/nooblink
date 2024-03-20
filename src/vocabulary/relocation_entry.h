// -*-C++-*-
//
// File: relocation_entry.h
// Project: nooblink
//
// Description: This component provides vocabulary types to describe relocation entries
//

#ifndef NOOBLINK_RELOCATION_ENTRY_H
#define NOOBLINK_RELOCATION_ENTRY_H

// std
#include <cstdint>
#include <ostream>
// nlohmann
#include <nlohmann/json.hpp>

namespace nooblink {

struct RelocationEntry {
  // This member gives the location at which to apply the relocation action. For a relocatable file, the value is the
  // byte offset from the beginning of the section to the storage unit affected by the relocation. For an executable
  // file or a shared object, the value is the virtual address of the storage unit affected by the relocation.
  uint64_t d_offset;

  // This member gives both the symbol table index with respect to which the relocation must be made, and the type of
  // relocation to apply. For example, a call instruction's relocation entry would hold the symbol table index of the
  // function being called. If the index is STN_UNDEF, the undefined symbol index, the relocation uses 0 as the ``symbol
  // value''. Relocation types are processor-specific; descriptions of their behavior appear in the processor supplement
  uint64_t d_info;

  // Render and return a json representation for this object
  nlohmann::json json() const;
};

struct RelocationEntryWithAddend {
  // This member gives the location at which to apply the relocation action. For a relocatable file, the value is the
  // byte offset from the beginning of the section to the storage unit affected by the relocation. For an executable
  // file or a shared object, the value is the virtual address of the storage unit affected by the relocation.
  uint64_t d_offset;

  // This member gives both the symbol table index with respect to which the relocation must be made, and the type of
  // relocation to apply. For example, a call instruction's relocation entry would hold the symbol table index of the
  // function being called. If the index is STN_UNDEF, the undefined symbol index, the relocation uses 0 as the ``symbol
  // value''. Relocation types are processor-specific; descriptions of their behavior appear in the processor supplement
  uint64_t d_info;

  // This member specifies a constant addend used to compute the value to be stored into the relocatable field.
  uint64_t d_addend;

  // Render and return a json representation for this object
  nlohmann::json json() const;
};

}  // namespace nooblink

#endif  // NOOBLINK_RELOCATION_ENTRY_H
