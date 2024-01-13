// -*-C++-*-
//
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
  static uint32_t nameIndex(RawSectionHeader rawSectionHeader);

  // Return type from the specified 'rawSectionHeader'
  static SectionType type(RawSectionHeader rawSectionHeader);

  // Return flags from the specified 'rawSectionHeader'
  static uint64_t flags(RawSectionHeader rawSectionHeader);

  // Return addr from the specified 'rawSectionHeader'
  static uint64_t addr(RawSectionHeader rawSectionHeader);

  // Return offset from the specified 'rawSectionHeader'
  static uint64_t offset(RawSectionHeader rawSectionHeader);

  // Return size from the specified 'rawSectionHeader'
  static uint64_t size(RawSectionHeader rawSectionHeader);

  // Return link from the specified 'rawSectionHeader'
  static uint32_t link(RawSectionHeader rawSectionHeader);

  // Return info from the specified 'rawSectionHeader'
  static uint32_t info(RawSectionHeader rawSectionHeader);

  // Return addrAlign from the specified 'rawSectionHeader'
  static uint64_t addrAlign(RawSectionHeader rawSectionHeader);

  // Return entrySize from the specified 'rawSectionHeader'
  static uint64_t entrySize(RawSectionHeader rawSectionHeader);
};

}  // namespace NoobLink

#endif