// -*-C++-*-
//
// File: elf_section.h
// Project: nooblink
//

#ifndef NOOBLINK_ELF_SECTION_H
#define NOOBLINK_ELF_SECTION_H

// nooblink
#include "raw/header_constants.h"
#include "raw/raw_section_header.h"
#include "vocabulary/elf_header.h"

namespace NoobLink {

class SectionTableEntry {
 public:
  // CREATORS

  // Construct this object using the specified 'rawSectionHeader' to decode from
  SectionTableEntry(const RawSectionHeader &rawSectionHeader);

  // ACCESSORS

  // Return the name index
  uint32_t nameIndex() const;

  // Return type
  SectionType type() const;

  // Return flags
  uint64_t flags() const;

  // Return addr
  uint64_t addr() const;

  // Return offset
  uint64_t offset() const;

  // Return size
  uint64_t size() const;

  // Return link
  uint32_t link() const;

  // Return info
  uint32_t info() const;

  // Return addrAlign
  uint64_t addrAlign() const;

  // Return entrySize
  uint64_t entrySize() const;

 private:
  // DATA
  uint32_t d_nameIndex;
  SectionType d_type;
  uint64_t d_flags;
  uint64_t d_addr;
  uint64_t d_offset;
  uint64_t d_size;
  uint32_t d_link;
  uint32_t d_info;
  uint64_t d_addrAlign;
  uint64_t d_entrySize;
};

}  // namespace NoobLink

#endif  // NOOBLINK_ELF_SECTION_H
