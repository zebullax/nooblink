// File: elf_section_util.h
// Project: nooblink
//

#ifndef NOOBLINK_ELF_SECTION_UTIL_H
#define NOOBLINK_ELF_SECTION_UTIL_H

// nooblink
#include "vocabulary/elf_section.h"
// std
#include <vector>

namespace NoobLink {
class ElfSectionUtil {
  // CREATORS

  ElfSectionUtil() = delete;

  // CLASS METHODS
  std::vector<SectionTableEntry> get();
};
}  // namespace NoobLink

#endif  // NOOBLINK_ELF_SECTION_UTIL_H
