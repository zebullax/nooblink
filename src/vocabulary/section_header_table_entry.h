// -*-C++-*-
//
// File: section_header_table_entry.h
// Project: nooblink
//
// Description: This component provides a vocabulary type to describe a section header
//

#ifndef NOOBLINK_SECTION_HEADER_TABLE_ENTRY_H
#define NOOBLINK_SECTION_HEADER_TABLE_ENTRY_H

// nooblink
#include <raw/header_constants.h>
#include <raw/layout.h>
#include <raw/raw_section_header.h>
#include <vocabulary/elf_header.h>
// nlohmann
#include <nlohmann/json.hpp>
// std
#include <array>
#include <cstddef>

namespace nooblink {

class SectionHeaderTableEntry {
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
  explicit SectionHeaderTableEntry(const RawSectionHeader& rawSectionHeader);

  // ACCESSORS

  // Return the name index
  [[nodiscard]] uint32_t nameIndex() const;

  // Return type
  [[nodiscard]] SectionType type() const;

  // Return flags
  [[nodiscard]] Flags flags() const;

  // If the section will appear in the memory image of a process, this member gives the address at which the section's
  // first byte should reside. Otherwise, the member contains 0.
  [[nodiscard]] uint64_t addr() const;

  // This member's value gives the byte offset from the beginning of the file to the first byte in the section. One
  // section type, 'SHT_NOBITS' occupies no space in the file, and its offset member locates the conceptual placement in
  // the file.
  [[nodiscard]] std::byte* offset() const;

  // Return size
  [[nodiscard]] uint64_t size() const;

  // Return link index. This member holds a section header table index link, whose interpretation depends on the section
  // type.
  [[nodiscard]] uint32_t link() const;

  // Return info
  [[nodiscard]] uint32_t info() const;

  // Return addrAlign
  [[nodiscard]] uint64_t addrAlign() const;

  // Return entrySize
  [[nodiscard]] uint64_t entrySize() const;

  // Render and return a json representation for this object
  [[nodiscard]] nlohmann::json json() const;

 private:
  // FRIENDS

  friend std::ostream& operator<<(std::ostream& os, const SectionHeaderTableEntry& sectionHeader);

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

}  // namespace nooblink

#endif  // NOOBLINK_SECTION_HEADER_TABLE_ENTRY_H
