// -*-C++-*-
//
// File: raw_symbol_table_entry_util.h
// Project: nooblink
//
// Description: Describe me
//

#ifndef NOOBLINK_RAW_SYMBOL_TABLE_ENTRY_UTIL_H
#define NOOBLINK_RAW_SYMBOL_TABLE_ENTRY_UTIL_H

// nooblink
#include <raw/raw_symbol_table_entry.h>
// std
#include <cstdint>

namespace nooblink {

struct RawSymbolTableEntryUtil {
  // CREATORS

  RawSymbolTableEntryUtil() = delete;

  // CLASS METHODS

  static uint32_t nameIndex(RawSymbolTableEntry rawSymbolTableEntry);

  static uint64_t value(RawSymbolTableEntry rawSymbolTableEntry);

  static uint64_t size(RawSymbolTableEntry rawSymbolTableEntry);

  static uint16_t sectionHeaderIndex(RawSymbolTableEntry rawSymbolTableEntry);

  static uint8_t info(RawSymbolTableEntry rawSymbolTableEntry);

  static uint8_t other(RawSymbolTableEntry rawSymbolTableEntry);
};

}  // namespace nooblink

#endif  // NOOBLINK_RAW_SYMBOL_TABLE_ENTRY_UTIL_H
