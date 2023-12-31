// File: elf_format_util.h
// Project: nooblink
//

#ifndef NOOBLINK_ELF_FORMAT_UTIL_H
#define NOOBLINK_ELF_FORMAT_UTIL_H

// nooblink
#include <elf_constants.h>
#include <elf_format.h>
// std
#include <cstdint>
#include <ostream>

namespace NoobLink {

struct ElfFormatUtil {
  ElfFormatUtil() = delete;

  // Return whether the specified 'header' is Elf
  static bool isElf(Elf64Header header);

  // Return the address class from the specified 'header'
  static AddressClass resolveAddressClass(Elf64Header header);

  // Return the endianness from the specified 'header'
  static Endianness resolveEndianness(Elf64Header header);

  // Return header version from specified 'header'
  static uint8_t resolveHeaderVersion(Elf64Header header);

  // Return the ABI from the specified 'header'
  static Abi resolveABI(Elf64Header header);

  // Return ABI version from specified 'header'
  static uint8_t resolveAbiVersion(Elf64Header header);

  // Return the object file type from the specified 'header'
  static ObjectFileType resolveObjectFileType(Elf64Header header);

  // Return object file version from specified 'header'
  static uint32_t resolveObjectFileVersion(Elf64Header header);

  // Return the architecture from the specified 'header'
  static Architecture resolveArchitecture(Elf64Header header);

  // Return the ExecutionAddress from the specified 'header'
  static uint64_t resolveExecutionAddress(Elf64Header header);

  // Return the HeaderTableAddress from the specified 'header'
  static uint64_t resolveHeaderTableAddress(Elf64Header header);

  // Return the SectionTableAddress from the specified 'header'
  static uint32_t resolveSectionTableAddress(Elf64Header header);

  // Return the flags from the specified 'header'
  static uint32_t resolveFlags(Elf64Header header);

  // Return the HeaderSize from the specified 'header'
  static uint16_t resolveHeaderSize(Elf64Header header);

  // Return the HeaderTableSize from the specified 'header'
  static uint16_t resolveHeaderTableSize(Elf64Header header);

  // Return the HeaderTableCount from the specified 'header'
  static uint16_t resolveHeaderTableCount(Elf64Header header);

  // Return the SectionTableSize from the specified 'header'
  static uint16_t resolveSectionTableSize(Elf64Header header);

  // Return the SectionTableCount from the specified 'header'
  static uint16_t resolveSectionTableCount(Elf64Header header);

  // Return the SectionNameIndex from the specified 'header'
  static uint16_t resolveSectionNameIndex(Elf64Header header);

  // Print a description of the specified 'header' to the specified 'os' and return that stream
  static std::ostream &print(std::ostream &os, Elf64Header header);
};

} // namespace NoobLink

#endif // NOOBLINK_ELF_FORMAT_UTIL_H
