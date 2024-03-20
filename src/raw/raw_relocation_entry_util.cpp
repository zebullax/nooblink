// -*-C++-*-
//
// File: raw_relocation_entry_util.cpp
// Project: nooblink
//

#include <raw/raw_relocation_entry_util.h>
// nooblink

namespace nooblink {

uint64_t RawRelocationEntryUtil::addend(RawRelocationEntryWithAddend relocation) {
  std::span field = relocation.subspan<Layout::FieldOffset::RelocationEntryWithAddend::k_Offset,
                                       Layout::FieldLength::RelocationEntryWithAddend::k_Offset>();
  return ByteUtil::convertTo<uint64_t>(field);
}

}  // namespace nooblink
