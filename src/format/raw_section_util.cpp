// File: elf_section_util.cpp
// Project: nooblink
//

// nooblink
#include <byte_util.h>
#include <format/raw_description.h>
#include <format/raw_section_util.h>

namespace NoobLink {
namespace {

// Macro to cast the specified 'FIELD_NAME' from the section entry to the specified 'TARGET_TYPE'
#define RETURN_CAST_FIELD(TARGET_TYPE, FIELD_NAME)                                                                     \
  std::span field = rawEntry.subspan<FieldOffset::Section::k_##FIELD_NAME, FieldLength::Section::k_##FIELD_NAME>();    \
  return ByteUtil::convertTo<TARGET_TYPE>(field);

} // anonymous namespace

std::vector<std::byte *> RawSectionUtil::findEntriesBySectionType(SectionTableBound sectionTableBound,
                                                                  SectionType sectionType) {
  auto [nbSectionEntries, sectionEntrySize, sectionTableStart] = sectionTableBound;
  std::vector<std::byte *> entries;
  std::byte *start = sectionTableStart;
  auto rawSectionType = static_cast<std::underlying_type_t<SectionType>>(sectionType);

  for (size_t i = 0; i != nbSectionEntries; ++i) {
    std::span<std::byte, FieldLength::Section::k_Type> entryType(start + FieldOffset::Section::k_Type,
                                                                 FieldLength::Section::k_Type);
    uint32_t sectionEntryType = ByteUtil::convertTo<uint32_t>(entryType);
    if (sectionEntryType == rawSectionType) {
      entries.push_back(start);
    }
    start += sectionEntrySize;
  }

  return entries;
}

uint32_t RawSectionUtil::getNameIndex(RawSectionEntry rawEntry){RETURN_CAST_FIELD(uint32_t, NameIndex)}

uint64_t RawSectionUtil::getAddr(RawSectionEntry rawEntry){RETURN_CAST_FIELD(uint64_t, Addr)}

uint64_t RawSectionUtil::getOffset(RawSectionEntry rawEntry){RETURN_CAST_FIELD(uint64_t, Offset)}

uint64_t RawSectionUtil::getSize(RawSectionEntry rawEntry){RETURN_CAST_FIELD(uint64_t, Size)}

uint32_t RawSectionUtil::getLink(RawSectionEntry rawEntry){RETURN_CAST_FIELD(uint64_t, Addr)}

uint32_t RawSectionUtil::getInfo(RawSectionEntry rawEntry){RETURN_CAST_FIELD(uint32_t, Info)}

uint64_t RawSectionUtil::getAddrAlign(RawSectionEntry rawEntry){RETURN_CAST_FIELD(uint64_t, AddrAlign)}

uint64_t RawSectionUtil::getEntrySize(RawSectionEntry rawEntry) {
  RETURN_CAST_FIELD(uint64_t, EntrySize)
}

#undef RETURN_CAST_FIELD
} // namespace NoobLink
