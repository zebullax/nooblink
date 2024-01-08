// File: elf_section.h
// Project: nooblink
//

#ifndef NOOBLINK_ELF_SECTION_H
#define NOOBLINK_ELF_SECTION_H

// nooblink
#include "raw/header_constants.h"

namespace NoobLink {

struct SectionTableEntry {
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

} // namespace NoobLink

#endif // NOOBLINK_ELF_SECTION_H
