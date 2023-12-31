// File: elf_format_util.cpp
// Project: nooblink
//

// nooblink
#include <elf_constants.h>
#include <elf_format_util.h>
// json
#include <nlohmann/json.hpp>
// std
#include <cstdint>
#include <iomanip>
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

} // anonymous namespace

bool ElfFormatUtil::isElf(Elf64Header header) {
  std::span ident = header.first(4);

  return ident[0] == std::byte(0x7F) && ident[1] == std::byte(0x45) && ident[2] == std::byte(0x4c) &&
         ident[3] == std::byte(0x46);
}

Endianness ElfFormatUtil::resolveEndianness(Elf64Header header) { RETURN_CAST_FIELD(Endianness, Endianness); }

uint8_t ElfFormatUtil::resolveHeaderVersion(Elf64Header header){RETURN_CAST_FIELD(uint8_t, HeaderVersion)}

AddressClass ElfFormatUtil::resolveAddressClass(Elf64Header header) {
  RETURN_CAST_FIELD(AddressClass, AddressClass);
}

Abi ElfFormatUtil::resolveABI(Elf64Header header) { RETURN_CAST_FIELD(Abi, Abi); }

uint8_t ElfFormatUtil::resolveAbiVersion(Elf64Header header){RETURN_CAST_FIELD(uint8_t, AbiVersion)}

ObjectFileType ElfFormatUtil::resolveObjectFileType(Elf64Header header) {
  RETURN_CAST_FIELD(ObjectFileType, ObjectFileType);
}

Architecture ElfFormatUtil::resolveArchitecture(Elf64Header header) { RETURN_CAST_FIELD(Architecture, Architecture); }

uint32_t ElfFormatUtil::resolveObjectFileVersion(Elf64Header header) { RETURN_CAST_FIELD(uint32_t, ObjectFileVersion); }

uint64_t ElfFormatUtil::resolveExecutionAddress(Elf64Header header) { RETURN_CAST_FIELD(uint64_t, ExecutionAddress); }

uint64_t ElfFormatUtil::resolveHeaderTableAddress(Elf64Header header) {
  RETURN_CAST_FIELD(uint64_t, HeaderTableAddress);
}

uint32_t ElfFormatUtil::resolveSectionTableAddress(Elf64Header header) {
  RETURN_CAST_FIELD(uint32_t, SectionTableAddress);
}

uint32_t ElfFormatUtil::resolveFlags(Elf64Header header) { RETURN_CAST_FIELD(uint32_t, Flags); }

uint16_t ElfFormatUtil::resolveHeaderSize(Elf64Header header) { RETURN_CAST_FIELD(uint16_t, HeaderSize); }

uint16_t ElfFormatUtil::resolveHeaderTableSize(Elf64Header header) { RETURN_CAST_FIELD(uint16_t, HeaderTableSize); }

uint16_t ElfFormatUtil::resolveHeaderTableCount(Elf64Header header) { RETURN_CAST_FIELD(uint16_t, HeaderTableCount); }

uint16_t ElfFormatUtil::resolveSectionTableSize(Elf64Header header) { RETURN_CAST_FIELD(uint16_t, SectionTableSize); }

uint16_t ElfFormatUtil::resolveSectionTableCount(Elf64Header header) { RETURN_CAST_FIELD(uint16_t, SectionTableCount); }

uint16_t ElfFormatUtil::resolveSectionNameIndex(Elf64Header header) { RETURN_CAST_FIELD(uint16_t, SectionNameIndex); }

std::ostream &ElfFormatUtil::print(std::ostream &os, Elf64Header header) {
  auto toString = [](auto e) {
    std::ostringstream oss;
    oss << e;
    return oss.str();
  };

  auto toHex = [](auto e) {
    std::ostringstream oss;
    oss << "0x" << std::hex << std::setw(sizeof(e)) << std::setfill('0') << e;
    return oss.str();
  };

  using json = nlohmann::json;
  json j;

  if (!isElf(header)) {
    return os << R"({"Error": "File is not Elf"})";
  }

  j["AddressClass"] = toString(ElfFormatUtil::resolveAddressClass(header));
  j["Endianness"] = toString(ElfFormatUtil::resolveEndianness(header));
  j["HeaderVersion"] = ElfFormatUtil::resolveHeaderVersion(header);
  j["Abi"] = toString(ElfFormatUtil::resolveABI(header));
  j["AbiVersion"] = ElfFormatUtil::resolveAbiVersion(header);
  j["Padding"] = "       ";
  j["ObjectFileType"] = toString(ElfFormatUtil::resolveObjectFileType(header));
  j["Architecture"] = toString(ElfFormatUtil::resolveArchitecture(header));
  j["ObjectFileVersion"] = ElfFormatUtil::resolveObjectFileVersion(header);
  j["ExecutionAddress"] = toHex(ElfFormatUtil::resolveExecutionAddress(header));
  j["HeaderTableAddress"] = toHex(ElfFormatUtil::resolveHeaderTableAddress(header));
  j["SectionTableAddress"] = toHex(ElfFormatUtil::resolveSectionTableAddress(header));
  j["Flags"] = toHex(ElfFormatUtil::resolveFlags(header));
  j["HeaderSize"] = ElfFormatUtil::resolveHeaderSize(header);
  j["HeaderTableSize"] = ElfFormatUtil::resolveHeaderTableSize(header);
  j["HeaderTableCount"] = ElfFormatUtil::resolveHeaderTableCount(header);
  j["SectionTableSize"] = ElfFormatUtil::resolveSectionTableSize(header);
  j["SectionTableCount"] = ElfFormatUtil::resolveSectionTableCount(header);
  j["SectionNameIndex"] = ElfFormatUtil::resolveSectionNameIndex(header);
  os << j;
  return os;
}

#undef RETURN_CAST_FIELD
} // namespace NoobLink
