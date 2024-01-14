// -*-C++-*-
//
// File: section_header.h
// Project: nooblink
//
// Description: This component provides a vocabulary type to describe a decoded section entry in the section table
//

#ifndef NOOBLINK_SECTION_HEADER_H
#define NOOBLINK_SECTION_HEADER_H

// nooblink
#include "raw/header_constants.h"
#include "raw/layout.h"
#include "raw/raw_section_header.h"
#include "vocabulary/elf_header.h"
// std
#include <array>
#include <cstddef>

namespace NoobLink {

class SectionHeader {
 public:
  // TYPES

  struct Flags {
    bool d_isWrite;
    bool d_isAlloc;
    bool d_isExecinstr;
    bool d_isMerge;
    bool d_isStrings;
    bool d_isInfo_link;
    bool d_isLink_order;
    bool d_isOs_nonconforming;
    bool d_isGroup;
    bool d_isTls;
    bool d_isMaskos;
    bool d_isMaskproc;
  };

  // CREATORS

  // Construct this object using the specified 'rawSectionHeader' to decode from
  SectionHeader(const RawSectionHeader& rawSectionHeader);

  // ACCESSORS

  // Return the name index
  uint32_t nameIndex() const;

  // Return type
  SectionType type() const;

  // Return flags
  Flags flags() const;

  // Return addr. If the section will appear in the memory image of a process, this member gives the address at which
  // the section's first byte should reside. Otherwise, the member contains 0.
  uint64_t addr() const;

  // Return offset
  uint64_t offset() const;

  // Return size
  uint64_t size() const;

  // Return link index. This member holds a section header table index link, whose interpretation depends on the section
  // type.
  uint32_t link() const;

  // Return info
  uint32_t info() const;

  // Return addrAlign
  uint64_t addrAlign() const;

  // Return entrySize
  uint64_t entrySize() const;

  // Output to the specified 'os' a JSON representation of this object, return the stream
  std::ostream& print(std::ostream& os) const;

 private:
  // FRIENDS

  friend std::ostream& operator<<(std::ostream& os, const SectionHeader& sectionHeader);

  // DATA
  uint32_t d_nameIndex;
  SectionType d_type;
  Flags d_flags;
  uint64_t d_addr;
  uint64_t d_offset;
  uint64_t d_size;
  uint32_t d_link;
  uint32_t d_info;
  uint64_t d_addrAlign;
  uint64_t d_entrySize;
};

}  // namespace NoobLink

#endif  // NOOBLINK_SECTION_HEADER_H
