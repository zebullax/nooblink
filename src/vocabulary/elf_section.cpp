// -*-C++-*-
//
// File: elf_section.cpp
// Project: nooblink
//

// nooblink
#include "vocabulary/elf_section.h"

#include "raw/raw_section_header_util.h"

namespace NoobLink {

uint32_t SectionTableEntry::nameIndex() const { return d_nameIndex; }

SectionType SectionTableEntry::type() const { return d_type; }

uint64_t SectionTableEntry::flags() const { return d_flags; }

uint64_t SectionTableEntry::addr() const { return d_addr; }

uint64_t SectionTableEntry::offset() const { return d_offset; }

uint64_t SectionTableEntry::size() const { return d_size; }

uint32_t SectionTableEntry::link() const { return d_link; }

uint32_t SectionTableEntry::info() const { return d_info; }

uint64_t SectionTableEntry::addrAlign() const { return d_addrAlign; }

uint64_t SectionTableEntry::entrySize() const { return d_entrySize; }

SectionTableEntry::SectionTableEntry(const RawSectionHeader &rawSectionHeader)
    : d_nameIndex{RawSectionHeaderUtil::nameIndex(rawSectionHeader)},
      d_type{RawSectionHeaderUtil::type(rawSectionHeader)},
      d_flags{RawSectionHeaderUtil::flags(rawSectionHeader)},
      d_addr{RawSectionHeaderUtil::addr(rawSectionHeader)},
      d_offset{RawSectionHeaderUtil::offset(rawSectionHeader)},
      d_size{RawSectionHeaderUtil::size(rawSectionHeader)},
      d_link{RawSectionHeaderUtil::link(rawSectionHeader)},
      d_info{RawSectionHeaderUtil::info(rawSectionHeader)},
      d_addrAlign{RawSectionHeaderUtil::addrAlign(rawSectionHeader)},
      d_entrySize{RawSectionHeaderUtil::entrySize(rawSectionHeader)} {}

}  // namespace NoobLink
