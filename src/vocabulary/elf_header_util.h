// -*-C++-*-
//
// File: elf_header_util.h
// Project: nooblink
//
// Description: This component provides utility related to a decoded elf header
//

#ifndef NOOBLINK_ELF_HEADER_UTIL_H
#define NOOBLINK_ELF_HEADER_UTIL_H

// nooblink
#include "vocabulary/elf_header.h"
#include "vocabulary/section_header.h"
// std
#include <cstddef>
#include <vector>

namespace NoobLink {
struct ElfHeaderUtil {
  // CREATORS

  ElfHeaderUtil() = delete;

  // CLASS METHODS

  // Extract from the specified 'elfHeader' all section table entries, optionally specify an offset to be applied to
  // address as they are originally decoded from the header
  static std::vector<SectionHeader> extractSections(const ElfHeader& elfHeader, std::byte* offset = nullptr);
};

}  // namespace NoobLink

#endif  // NOOBLINK_ELF_HEADER_UTIL_H
