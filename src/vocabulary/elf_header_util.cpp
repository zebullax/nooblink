// -*-C++-*-
//
// File: elf_header_util.cpp
// Project: nooblink
//

// nooblink
#include "vocabulary/elf_header_util.h"

namespace NoobLink {

std::vector<SectionHeader> ElfHeaderUtil::extractSections(const ElfHeader &elfHeader, std::byte *offset) {
  std::vector<SectionHeader> result;
  std::byte *entryPtr = elfHeader.getSectionTableAddress() + (offset ? offset : 0);
  const uint64_t nbSectionHeaders = elfHeader.getSectionTableCount();
  const uint64_t sectionHeaderSize = elfHeader.getSectionTableSize();
  result.reserve(elfHeader.getSectionTableCount());

  for (size_t i = 0; i != nbSectionHeaders; ++i) {
    RawSectionHeader sectionTableEntry(entryPtr, entryPtr + sectionHeaderSize);
    result.push_back(SectionHeader(sectionTableEntry));
    entryPtr += sectionHeaderSize;
  }

  return result;
}

}  // namespace NoobLink
