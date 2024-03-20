// -*-C++-*-
//
// File: relocation_entry_util.cpp
// Project: nooblink
//

#include <vocabulary/relocation_entry_util.h>
// std
#include <bit>

namespace nooblink {

size_t RelocationEntryUtil::symbolIndex(uint64_t infoField) { return std::bit_cast<int64_t>(infoField) >> 32; }

size_t RelocationEntryUtil::type(uint64_t infoField) { return std::bit_cast<int64_t>(infoField) & (0xffff); }

}  // namespace nooblink