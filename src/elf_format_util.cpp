// File: elf_format_util.cpp
// Project: nooblink
//

// nooblink
#include <elf_constants.h>
#include <elf_format_util.h>
// json
#include <nlohmann/json.hpp>
// std
#include <span>
#include <sstream>

namespace NoobLink {
namespace {

// Helper function to reinterpret the specified 'source' span as a specified 'Target'
template <class Target, size_t NbBytes> Target convertTo(std::span<std::byte, NbBytes> source) {
  static_assert(sizeof(Target) == NbBytes);
  Target *head = reinterpret_cast<Target *>(source.data());
  return *head;
}

// Macro to cast the specified 'FIELD_NAME' from the header to the specified 'TARGET_TYPE'
#define RETURN_CAST_FIELD(TARGET_TYPE, FIELD_NAME)                                                                     \
  std::span field = header.subspan<ElfHeader64FieldOffset::k_##FIELD_NAME, ElfHeader64FieldLength::k_##FIELD_NAME>();  \
  return convertTo<TARGET_TYPE>(field);

} // namespace
bool ElfFormatUtil::isElf(Elf64Header header) {
  std::span ident = header.first(4);

  return ident[0] == std::byte(0x7F) && ident[1] == std::byte(0x45) && ident[2] == std::byte(0x4c) &&
         ident[3] == std::byte(0x46);
}

Endianness ElfFormatUtil::resolveEndianness(Elf64Header header) { RETURN_CAST_FIELD(Endianness, Endianness); }

AddressClass ElfFormatUtil::resolveAddressClass(Elf64Header header) { RETURN_CAST_FIELD(AddressClass, AddressClass); }

Abi ElfFormatUtil::resolveABI(Elf64Header header) { RETURN_CAST_FIELD(Abi, Abi); }

ObjectFileType ElfFormatUtil::resolveObjectFileType(Elf64Header header) {
  RETURN_CAST_FIELD(ObjectFileType, ObjectFileType);
}

Architecture ElfFormatUtil::resolveArchitecture(Elf64Header header) { RETURN_CAST_FIELD(Architecture, Architecture); }

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
  j["k_Architecture"] = toString(ElfFormatUtil::resolveArchitecture(header));
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

#undef RETURN_CAST_FIELD
} // namespace NoobLink
