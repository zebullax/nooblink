// File: elf_format_util.cpp
// Project: nooblink
//

// nooblink
#include <elf_format_util.h>
// json
#include <nlohmann/json.hpp>
// std
#include <span>
#include <sstream>
#include <utility>

namespace NoobLink {

bool ElfFormatUtil::isElf(Elf64Header header) {
  std::span ident = header.first(4);

  return ident[0] == std::byte(0x7F) && ident[1] == std::byte(0x45) && ident[2] == std::byte(0x4c) &&
         ident[3] == std::byte(0x46);
}

Endianness ElfFormatUtil::resolveEndianness(Elf64Header header) {
  const std::byte &endianness = header[ElfHeader64FieldOffset::k_Endianness];
  return endianness == std::byte(static_cast<unsigned char>(Endianness::e_Invalid)) ? Endianness::e_Invalid
         : endianness == std::byte(static_cast<unsigned char>(Endianness::e_LittleEndian))
             ? Endianness::e_LittleEndian
             : Endianness::e_BigEndian;
}

AddressClass ElfFormatUtil::resolveAddressClass(Elf64Header header) {
  const std::byte &addressClass = header[ElfHeader64FieldOffset::k_AddressClass];
  return addressClass == std::byte(static_cast<unsigned char>(AddressClass::e_Invalid)) ? AddressClass::e_Invalid
         : addressClass == std::byte(static_cast<unsigned char>(AddressClass::e_64))    ? AddressClass::e_64
                                                                                        : AddressClass::e_32;
}
ABI ElfFormatUtil::resolveABI(Elf64Header header) {
  const std::byte &abi = header[ElfHeader64FieldOffset::k_Abi];
  switch (abi) {
  case std::byte(0):
    return ABI::e_None;
  case std::byte(1):
    return ABI::e_Hpux;
  case std::byte(2):
    return ABI::e_Netbsd;
  case std::byte(3):
    return ABI::e_Linux;
  case std::byte(6):
    return ABI::e_Solaris;
  case std::byte(7):
    return ABI::e_Aix;
  case std::byte(8):
    return ABI::e_Irix;
  case std::byte(9):
    return ABI::e_Freebsd;
  case std::byte(10):
    return ABI::e_Tru64;
  case std::byte(11):
    return ABI::e_Modesto;
  case std::byte(12):
    return ABI::e_Openbsd;
  case std::byte(13):
    return ABI::e_Openvms;
  case std::byte(14):
    return ABI::e_Nsk;
  case std::byte(15):
    return ABI::e_Aros;
  case std::byte(16):
    return ABI::e_Fenixos;
  case std::byte(64):
    return ABI::e_C6000Elfabi;
  case std::byte(65):
    return ABI::e_C6000Linux;
  case std::byte(97):
    return ABI::e_Arm;
  default:
    return ABI::e_Unknown;
  }
}

std::ostream &ElfFormatUtil::print(std::ostream &os, Elf64Header header) {
  auto toString = [](auto e) {
    std::ostringstream oss;
    oss << e;
    return oss.str();
  };
  using json = nlohmann::json;
  json j;

  if (!isElf(header)) {
    return os << R"({"Error": "File is not Elf"})";
  }

  j["AddressClass"] = toString(ElfFormatUtil::resolveAddressClass(header));
  j["Endianness"] = toString(ElfFormatUtil::resolveEndianness(header));
  j["k_ElfVersion"] = header[ElfHeader64FieldOffset::k_Version] == std::byte(1) ? "Current" : "Invalid";
  j["k_Abi"] = toString(ElfFormatUtil::resolveABI(header));
  j["k_AbiVersion"] = "k_AbiVersion";
//  j["k_Padding"] = "k_Padding";
  j["k_ObjectFileType"] = toString(ElfFormatUtil::resolveObjectFileType(header));
  j["k_Architecture"] = "k_Architecture";
  j["k_Version"] = "k_Version";
  j["k_ExecutionAddress"] = "k_ExecutionAddress";
  j["k_HeaderTableAddress"] = "k_HeaderTableAddress";
  j["k_SectionTableAddress"] = "k_SectionTableAddress";
  j["k_Flags"] = "k_Flags";
  j["k_ElfHeaderSize"] = "k_ElfHeaderSize";
  j["k_HeaderTableSize"] = "k_HeaderTableSize";
  j["k_HeaderTableCount"] = "k_HeaderTableCount";
  j["k_SectionTableSize"] = "k_SectionTableSize";
  j["k_SectionTableCount"] = "k_SectionTableCount";
  j["k_SectionNameIndex"] = "k_SectionNameIndex";
  os << j;
  return os;
}

} // namespace NoobLink
