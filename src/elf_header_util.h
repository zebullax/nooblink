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
  static AddressClass resolveAddressClass(ElfHeader header);

  // Return the endianness from the specified 'header'
  static Endianness resolveEndianness(ElfHeader header);

  // Return header version from specified 'header'
  static uint8_t resolveHeaderVersion(ElfHeader header);

  // Return the ABI from the specified 'header'
  static Abi resolveABI(ElfHeader header);

  // Return ABI version from specified 'header'
  static uint8_t resolveAbiVersion(ElfHeader header);

  // Return the object file type from the specified 'header'
  static ObjectFileType resolveObjectFileType(ElfHeader header);

  // Return object file version from specified 'header'
  static uint32_t resolveObjectFileVersion(ElfHeader header);

  // Return the architecture from the specified 'header'
  static Architecture resolveArchitecture(ElfHeader header);

  // Return the ExecutionAddress from the specified 'header'
  static uint64_t resolveExecutionAddress(ElfHeader header);

  // Return the size of the ELF header
  static uint16_t resolveHeaderSize(ElfHeader header);

  // Return the HeaderTableAddress from the specified 'header'
  static uint64_t resolveProgramHeaderTableAddress(ElfHeader header);

  // Return the HeaderSize from the specified 'header'
  static uint16_t resolveProgramHeaderTableEntrySize(ElfHeader header);

  // Return the HeaderTableCount from the specified 'header'
  static uint16_t resolveProgramHeaderTableEntryCount(ElfHeader header);

  // Return the SectionTableAddress from the specified 'header'
  static uint64_t resolveSectionTableAddress(ElfHeader header);

  // Return the flags from the specified 'header'
  static uint32_t resolveFlags(ElfHeader header);

  // Return the SectionTableSize from the specified 'header'
  static uint16_t resolveSectionTableSize(ElfHeader header);

  // Return the SectionTableCount from the specified 'header'
  static uint16_t resolveSectionTableCount(ElfHeader header);

  // Return the SectionNameIndex from the specified 'header'
  static uint16_t resolveSectionNameIndex(ElfHeader header);

  // Print a description of the specified 'header' to the specified 'os' and return that stream
  static std::ostream &print(std::ostream &os, ElfHeader header);
};

} // namespace NoobLink

#endif // NOOBLINK_ELF_HEADER_UTIL_H
