// -*-C++-*-
//
// File: relocation_entry_util.cpp
// Project: nooblink
//

#include <vocabulary/relocation_entry_util.h>
// std
#include <bit>

#include "raw/header_constants.h"

namespace nooblink {

size_t RelocationEntryUtil::symbolIndex(uint64_t infoField) { return std::bit_cast<int64_t>(infoField) >> 32; }

RelocationType RelocationEntryUtil::type(uint64_t infoField) {
  return static_cast<RelocationType>((infoField) & (0xffff));
}

}  // namespace nooblink