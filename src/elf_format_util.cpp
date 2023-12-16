// File: elf_format_util.cpp
// Project: nooblink
//

// std
#include <span>
#include <utility>
// nooblink
#include <elf_constants.h>
#include <elf_format_util.h>

namespace NoobLink {

bool ElfFormatUtil::isElf(const Elf64Header &header) {
  std::span<const std::byte, 4> ident(header.begin(), 4);

  return ident[0] == std::byte(0x7F) && ident[1] == std::byte(0x45) && ident[2] == std::byte(0x4c) &&
         ident[3] == std::byte(0x46);
}

Endianness ElfFormatUtil::resolveEndianness(const Elf64Header &header) {
  const std::byte &endiannessByte = header[ElfHeader64FieldOffset::k_Endianness];
  return endiannessByte == std::byte(static_cast<unsigned char>(Endianness::e_Invalid))     ? Endianness::e_Invalid
         : endiannessByte == std::byte(static_cast<unsigned char>(Endianness::e_LowEndian)) ? Endianness::e_LowEndian
                                                                                            : Endianness::e_HighEndian;
}
AddressClass ElfFormatUtil::resolveAddressClass(const Elf64Header &header) {
  const std::byte &addressClass = header[ElfHeader64FieldOffset::k_AddressClass];
  return addressClass == std::byte(static_cast<unsigned char>(AddressClass::e_Invalid)) ? AddressClass::e_Invalid
         : addressClass == std::byte(static_cast<unsigned char>(AddressClass::e_64))    ? AddressClass::e_64
                                                                                        : AddressClass::e_32;
}

} // namespace NoobLink
