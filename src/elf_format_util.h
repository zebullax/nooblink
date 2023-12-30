// File: elf_format_util.h
// Project: nooblink
//

#ifndef NOOBLINK_ELF_FORMAT_UTIL_H
#define NOOBLINK_ELF_FORMAT_UTIL_H

// nooblink
#include <elf_constants.h>
#include <elf_format.h>
// std
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

  // Return the ABI from the specified 'header'
  static Abi resolveABI(Elf64Header header);

  // Return the object file type from the specified 'header'
  static ObjectFileType resolveObjectFileType(Elf64Header header);

  // Return the architecture from the specified 'header'
  static Architecture resolveArchitecture(Elf64Header header);

  // Print a description of the specified 'header' to the specified 'os' and return that stream
  static std::ostream &print(std::ostream &os, Elf64Header header);
};

} // namespace NoobLink

#endif // NOOBLINK_ELF_FORMAT_UTIL_H
