// -*-C++-*-
//
// File: section_header_util.cpp
// Project: nooblink
//

// nooblink
#include <raw/byte_util.h>
#include <raw/raw_section_header_util.h>
// std
#include <utility>

namespace nooblink {

// Macro to cast the specified 'FIELD_NAME' from the section entry to the specified 'TARGET_TYPE'
#define RETURN_CAST_FIELD(TARGET_TYPE, FIELD_NAME)                                                                \
  std::span field =                                                                                               \
      rawSectionHeader                                                                                            \
          .subspan<Layout::FieldOffset::Section::k_##FIELD_NAME, Layout::FieldLength::Section::k_##FIELD_NAME>(); \
  return ByteUtil::convertTo<TARGET_TYPE>(field);

uint32_t RawSectionHeaderUtil::nameIndex(RawSectionHeader rawSectionHeader){RETURN_CAST_FIELD(uint32_t, NameIndex)}

uint64_t RawSectionHeaderUtil::addr(RawSectionHeader rawSectionHeader){RETURN_CAST_FIELD(uint64_t, Addr)}

uint64_t RawSectionHeaderUtil::offset(RawSectionHeader rawSectionHeader){RETURN_CAST_FIELD(uint64_t, Offset)}

uint64_t RawSectionHeaderUtil::size(RawSectionHeader rawSectionHeader){RETURN_CAST_FIELD(uint64_t, Size)}

uint32_t RawSectionHeaderUtil::link(RawSectionHeader rawSectionHeader){RETURN_CAST_FIELD(uint64_t, Addr)}

uint32_t RawSectionHeaderUtil::info(RawSectionHeader rawSectionHeader){RETURN_CAST_FIELD(uint32_t, Info)}

uint64_t RawSectionHeaderUtil::addrAlign(RawSectionHeader rawSectionHeader){RETURN_CAST_FIELD(uint64_t, AddrAlign)}

uint64_t RawSectionHeaderUtil::entrySize(RawSectionHeader rawSectionHeader){RETURN_CAST_FIELD(uint64_t, EntrySize)}

SectionType RawSectionHeaderUtil::type(RawSectionHeader rawSectionHeader) {
  RETURN_CAST_FIELD(SectionType, Type);
}

uint64_t RawSectionHeaderUtil::flags(RawSectionHeader rawSectionHeader) { RETURN_CAST_FIELD(uint64_t, Flags); }

#undef RETURN_CAST_FIELD
}  // namespace nooblink
