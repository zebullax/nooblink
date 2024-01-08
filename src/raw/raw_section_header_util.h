// File: section_header_util.h
// Project: nooblink
//

#ifndef NOOBLINK_RAW_SECTION_HEADER_UTIL_H
#define NOOBLINK_RAW_SECTION_HEADER_UTIL_H

// NoobLink
#include "raw/header_constants.h"
#include "raw/layout.h"
#include "raw/raw_section_header.h"
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

struct RawSectionHeaderUtil {
  RawSectionHeaderUtil() = delete;

  // Lookup in section tables as described by specified 'sectionTableBound' all entries whose type is the specified
  // 'sectionType'. Return all entries addresses found
  static std::vector<std::byte *> findEntriesBySectionType(SectionTableBound sectionTableBound,
                                                           SectionType sectionType);

  // Return nameIndex from the specified 'rawSectionHeader'
  static uint32_t getNameIndex(RawSectionHeader rawSectionHeader);

  // Return type from the specified 'rawSectionHeader'
  static SectionType getType(RawSectionHeader rawSectionHeader);

  // Return flags from the specified 'rawSectionHeader'
  static uint64_t getFlags(RawSectionHeader rawSectionHeader);

  // Return addr from the specified 'rawSectionHeader'
  static uint64_t getAddr(RawSectionHeader rawSectionHeader);

  // Return offset from the specified 'rawSectionHeader'
  static uint64_t getOffset(RawSectionHeader rawSectionHeader);

  // Return size from the specified 'rawSectionHeader'
  static uint64_t getSize(RawSectionHeader rawSectionHeader);

  // Return link from the specified 'rawSectionHeader'
  static uint32_t getLink(RawSectionHeader rawSectionHeader);

  // Return info from the specified 'rawSectionHeader'
  static uint32_t getInfo(RawSectionHeader rawSectionHeader);

  // Return addrAlign from the specified 'rawSectionHeader'
  static uint64_t getAddrAlign(RawSectionHeader rawSectionHeader);

  // Return entrySize from the specified 'rawSectionHeader'
  static uint64_t getEntrySize(RawSectionHeader rawSectionHeader);
};

} // namespace NoobLink

#endif