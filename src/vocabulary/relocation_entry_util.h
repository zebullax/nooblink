// -*-C++-*-
//
// File: relocation_entry_util.h
// Project: nooblink
//
// Description: This component provides utility dedicated to relocation entry
//

#ifndef NOOBLINK_RELOCATION_ENTRY_UTIL_H
#define NOOBLINK_RELOCATION_ENTRY_UTIL_H

// std
#include <cstddef>
#include <cstdint>

namespace nooblink {

struct RelocationEntryUtil {
  // Decode and return the symbol index as found in the specified 'infoField'
  static size_t symbolIndex(uint64_t infoField);

  // Decode and return the relocation type as found in the specified 'infoField'
  static size_t type(uint64_t infoField);
};

}  // namespace nooblink

#endif  // NOOBLINK_RELOCATION_ENTRY_UTIL_H
