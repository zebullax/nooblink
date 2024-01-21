// -*-C++-*-
//
// File: elf_header_util.cpp
// Project: nooblink
//

// nooblink
#include <vocabulary/elf_header_util.h>

namespace nooblink {

std::vector<SectionHeader> ElfHeaderUtil::extractSections(const ElfHeader &elfHeader) {
  std::vector<SectionHeader> result;
  std::byte *entryPtr = elfHeader.sectionTableAddress();
  const uint64_t nbSectionHeaders = elfHeader.sectionTableCount();
  const uint64_t sectionHeaderSize = elfHeader.sectionTableSize();
  result.reserve(elfHeader.sectionTableCount());

  for (size_t i = 0; i != nbSectionHeaders; ++i) {
    RawSectionHeader sectionTableEntry(entryPtr, entryPtr + sectionHeaderSize);
    result.emplace_back(sectionTableEntry, elfHeader.offsetContent());
    entryPtr += sectionHeaderSize;
  }

  return result;
}

}  // namespace nooblink
