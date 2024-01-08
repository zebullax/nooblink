// File: section_header_util.cpp
// Project: nooblink
//

// nooblink
#include "raw/raw_section_header_util.h"
#include "byte_util.h"

namespace NoobLink {

// Macro to cast the specified 'FIELD_NAME' from the section entry to the specified 'TARGET_TYPE'
#define RETURN_CAST_FIELD(TARGET_TYPE, FIELD_NAME)                                                                     \
  std::span field =                                                                                                    \
      rawSectionHeader                                                                                                 \
          .subspan<Layout::FieldOffset::Section::k_##FIELD_NAME, Layout::FieldLength::Section::k_##FIELD_NAME>();      \
  return ByteUtil::convertTo<TARGET_TYPE>(field);

std::vector<std::byte *> RawSectionHeaderUtil::findEntriesBySectionType(SectionTableBound sectionTableBound,
                                                                        SectionType sectionType) {
  auto [nbSectionEntries, sectionEntrySize, sectionTableStart] = sectionTableBound;
  std::vector<std::byte *> entries;
  std::byte *start = sectionTableStart;
  auto rawSectionType = static_cast<std::underlying_type_t<SectionType>>(sectionType);

  for (size_t i = 0; i != nbSectionEntries; ++i) {
    std::span<std::byte, Layout::FieldLength::Section::k_Type> entryType(start + Layout::FieldOffset::Section::k_Type,
                                                                         Layout::FieldLength::Section::k_Type);
    uint32_t sectionEntryType = ByteUtil::convertTo<uint32_t>(entryType);
    if (sectionEntryType == rawSectionType) {
      entries.push_back(start);
    }
    start += sectionEntrySize;
  }

  return entries;
}

uint32_t RawSectionHeaderUtil::getNameIndex(RawSectionHeader rawSectionHeader){RETURN_CAST_FIELD(uint32_t, NameIndex)}

uint64_t RawSectionHeaderUtil::getAddr(RawSectionHeader rawSectionHeader){RETURN_CAST_FIELD(uint64_t, Addr)}

uint64_t RawSectionHeaderUtil::getOffset(RawSectionHeader rawSectionHeader){RETURN_CAST_FIELD(uint64_t, Offset)}

uint64_t RawSectionHeaderUtil::getSize(RawSectionHeader rawSectionHeader){RETURN_CAST_FIELD(uint64_t, Size)}

uint32_t RawSectionHeaderUtil::getLink(RawSectionHeader rawSectionHeader){RETURN_CAST_FIELD(uint64_t, Addr)}

uint32_t RawSectionHeaderUtil::getInfo(RawSectionHeader rawSectionHeader){RETURN_CAST_FIELD(uint32_t, Info)}

uint64_t RawSectionHeaderUtil::getAddrAlign(RawSectionHeader rawSectionHeader){RETURN_CAST_FIELD(uint64_t, AddrAlign)}

uint64_t RawSectionHeaderUtil::getEntrySize(RawSectionHeader rawSectionHeader) {
  RETURN_CAST_FIELD(uint64_t, EntrySize)
}

#undef RETURN_CAST_FIELD
} // namespace NoobLink
