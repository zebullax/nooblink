// File: elf_header_util.h
// Project: nooblink
//

#ifndef NOOBLINK_ELF_HEADER_UTIL_H
#define NOOBLINK_ELF_HEADER_UTIL_H

// nooblink
#include <elf_constants.h>
#include <elf_format.h>
// std
#include <cstdint>
#include <ostream>

namespace NoobLink {

struct ElfHeaderUtil {
  ElfHeaderUtil() = delete;

  // Return whether the specified 'header' is Elf
  static bool isElf(ElfHeader header);

  // Return the address class from the specified 'header'
  static AddressClass addressClass(ElfHeader header);

  // Return the endianness from the specified 'header'
  static Endianness endianness(ElfHeader header);

  // Return header version from specified 'header'
  static uint8_t headerVersion(ElfHeader header);

  // Return the ABI from the specified 'header'
  static Abi abi(ElfHeader header);

  // Return ABI version from specified 'header'
  static uint8_t abiVersion(ElfHeader header);

  // Return the object file type from the specified 'header'
  static ObjectFileType objectFileType(ElfHeader header);

  // Return object file version from specified 'header'
  static uint32_t objectFileVersion(ElfHeader header);

  // Return the architecture from the specified 'header'
  static Architecture architecture(ElfHeader header);

  // Return the ExecutionAddress from the specified 'header'
  static uint64_t executionAddress(ElfHeader header);

  // Return the size of the ELF header
  static uint16_t headerSize(ElfHeader header);

  // Return the HeaderTableAddress from the specified 'header'
  static uint64_t ProgramTableAddress(ElfHeader header);

  // Return the HeaderSize from the specified 'header'
  static uint16_t ProgramTableEntrySize(ElfHeader header);

  // Return the HeaderTableCount from the specified 'header'
  static uint16_t ProgramTableEntryCount(ElfHeader header);

  // Return the SectionTableAddress from the specified 'header'
  static uint64_t sectionTableAddress(ElfHeader header);

  // Return the flags from the specified 'header'
  static uint32_t flags(ElfHeader header);

  // Return the SectionTableSize from the specified 'header'
  static uint16_t sectionTableSize(ElfHeader header);

  // Return the SectionTableCount from the specified 'header'
  static uint16_t sectionTableCount(ElfHeader header);

  // Return the SectionNameIndex from the specified 'header'
  static uint16_t sectionNameIndex(ElfHeader header);

  // Print a description of the specified 'header' to the specified 'os' and return that stream
  static std::ostream &print(std::ostream &os, ElfHeader header);
};

} // namespace NoobLink

#endif // NOOBLINK_ELF_HEADER_UTIL_H
