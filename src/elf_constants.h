// File: elf_constants.h
// Project: nooblink
//

#ifndef NOOBLINK_ELF_CONSTANTS_H
#define NOOBLINK_ELF_CONSTANTS_H

namespace NoobLink {

enum class AddressClass : unsigned char  { e_Invalid, e_32, e_64 };

enum class Endianness : unsigned char { e_Invalid, e_LowEndian, e_HighEndian };

enum class ObjectFileType  {
  e_Unknown,
  e_Relocatable,
  e_Executable,
  e_Shared,
};

}
#endif // NOOBLINK_ELF_CONSTANTS_H
