// File: elf_format_util.h
// Project: nooblink
//

#ifndef NOOBLINK_ELF_FORMAT_UTIL_H
#define NOOBLINK_ELF_FORMAT_UTIL_H

// nooblink
#include <byte_util.h>
#include <elf_constants.h>
#include <elf_format.h>
// std
#include <cassert>
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
  static ABI resolveABI(Elf64Header header);

  // Return the object file type from the specified 'header'
  template <Endianness HeaderEndianness = Endianness::e_LittleEndian>
  static ObjectFileType resolveObjectFileType(Elf64Header header);

  // Print a description of the specified 'header' to the specified 'os' and return that stream
  static std::ostream &print(std::ostream &os, Elf64Header header);
};

} // namespace NoobLink

template <NoobLink::Endianness HeaderEndianness>
NoobLink::ObjectFileType NoobLink::ElfFormatUtil::resolveObjectFileType(NoobLink::Elf64Header header) {
  static_assert(sizeof(NoobLink::ObjectFileType) == NoobLink::ElfHeader64FieldLength::k_ObjectFileType);

  std::span objectFileType = NoobLink::ByteUtil::toNativeEndian<HeaderEndianness>(header.subspan(
      NoobLink::ElfHeader64FieldOffset::k_ObjectFileType, NoobLink::ElfHeader64FieldLength::k_ObjectFileType));
  // FIXME harden against UB
  NoobLink::ObjectFileType *head = reinterpret_cast<NoobLink::ObjectFileType *>(objectFileType.begin());
  return *head;
}

#endif // NOOBLINK_ELF_FORMAT_UTIL_H
