// File: raw_section_util.h
// Project: nooblink
//

#ifndef NOOBLINK_RAW_SECTION_UTIL_H
#define NOOBLINK_RAW_SECTION_UTIL_H

// NoobLink
#include <format/elf_section.h>
#include <format/header_constants.h>
// std
#include <cstddef>
#include <vector>

namespace NoobLink {

// Bag of data describing the section table boundaries
struct SectionTableBound {
  uint64_t d_nbEntries;
  uint64_t d_entrySize;
  std::byte *d_tableStart;
};

struct RawSectionUtil {
  RawSectionUtil() = delete;

  // Lookup in section tables as described by specified 'sectionTableBound' all entries whose type is the specified
  // 'sectionType'. Return all entries addresses found
  static std::vector<std::byte *> findEntriesBySectionType(SectionTableBound sectionTableBound,
                                                           SectionType sectionType);

  // Return nameIndex from the specified 'rawEntry'
  static uint32_t getNameIndex(RawSectionEntry rawEntry);

  // Return type from the specified 'rawEntry'
  static SectionType getType(RawSectionEntry rawEntry);

  // Return flags from the specified 'rawEntry'
  static uint64_t getFlags(RawSectionEntry rawEntry);

  // Return addr from the specified 'rawEntry'
  static uint64_t getAddr(RawSectionEntry rawEntry);

  // Return offset from the specified 'rawEntry'
  static uint64_t getOffset(RawSectionEntry rawEntry);

  // Return size from the specified 'rawEntry'
  static uint64_t getSize(RawSectionEntry rawEntry);

  // Return link from the specified 'rawEntry'
  static uint32_t getLink(RawSectionEntry rawEntry);

  // Return info from the specified 'rawEntry'
  static uint32_t getInfo(RawSectionEntry rawEntry);

  // Return addrAlign from the specified 'rawEntry'
  static uint64_t getAddrAlign(RawSectionEntry rawEntry);

  // Return entrySize from the specified 'rawEntry'
  static uint64_t getEntrySize(RawSectionEntry rawEntry);
};
} // namespace NoobLink

#endif