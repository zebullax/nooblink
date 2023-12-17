// File: elf_constants.h
// Project: nooblink
//

#ifndef NOOBLINK_ELF_CONSTANTS_H
#define NOOBLINK_ELF_CONSTANTS_H

// std
#include <ostream>

namespace NoobLink {

enum class AddressClass : unsigned char { e_Invalid, e_32, e_64 };
std::ostream &operator<<(std::ostream &os, const AddressClass &addressClass);

enum class Endianness : unsigned char { e_Invalid, e_LowEndian, e_HighEndian };
std::ostream &operator<<(std::ostream &os, const Endianness &endianness);

enum class ObjectFileType {
  e_Unknown,
  e_Relocatable,
  e_Executable,
  e_Shared,
};
std::ostream &operator<<(std::ostream &os, const ObjectFileType &objectFileType);

} // namespace NoobLink

inline std::ostream &NoobLink::operator<<(std::ostream &os, const AddressClass &addressClass) {
  switch (addressClass) {

  case AddressClass::e_Invalid:
    return os << "Invalid";
  case AddressClass::e_32:
    return os << "32bits";
  case AddressClass::e_64:
    return os << "64bits";
  }
}

inline std::ostream &NoobLink::operator<<(std::ostream &os, const Endianness &endianness) {
  switch (endianness) {

  case Endianness::e_Invalid:
    return os << "Invalid";
  case Endianness::e_LowEndian:
    return os << "LowEndian";
  case Endianness::e_HighEndian:
    return os << "HighEndian";
  }
}

inline std::ostream &NoobLink::operator<<(std::ostream &os, const ObjectFileType &objectFileType)
{
  switch (objectFileType) {

  case ObjectFileType::e_Unknown:
    return os << "Unknown";
  case ObjectFileType::e_Relocatable:
    return os << "Relocatable";
  case ObjectFileType::e_Executable:
    return os << "Executable";
  case ObjectFileType::e_Shared:
    return os << "Shared";
  }
}

#endif // NOOBLINK_ELF_CONSTANTS_H
