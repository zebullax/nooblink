// File: elf_header_util.cpp
// Project: nooblink
//

// nooblink
#include <elf_constants.h>
#include <elf_header_util.h>
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
  auto *head = reinterpret_cast<Target *>(source.data());
  return *head;
}

// Macro to cast the specified 'FIELD_NAME' from the header to the specified 'TARGET_TYPE'
#define RETURN_CAST_FIELD(TARGET_TYPE, FIELD_NAME)                                                                     \
  std::span field = header.subspan<FieldOffset::Header::k_##FIELD_NAME, FieldLength::Header::k_##FIELD_NAME>();        \
  return convertTo<TARGET_TYPE>(field);

} // anonymous namespace

bool ElfHeaderUtil::isElf(ElfHeader header) {
  std::span ident = header.first(4);

  return ident[0] == std::byte(0x7F) && ident[1] == std::byte(0x45) && ident[2] == std::byte(0x4c) &&
         ident[3] == std::byte(0x46);
}

Endianness ElfHeaderUtil::resolveEndianness(ElfHeader header) { RETURN_CAST_FIELD(Endianness, Endianness); }

uint8_t ElfHeaderUtil::resolveHeaderVersion(ElfHeader header){RETURN_CAST_FIELD(uint8_t, HeaderVersion)}

AddressClass ElfHeaderUtil::resolveAddressClass(ElfHeader header) {
  RETURN_CAST_FIELD(AddressClass, AddressClass);
}

Abi ElfHeaderUtil::resolveABI(ElfHeader header) { RETURN_CAST_FIELD(Abi, Abi); }

uint8_t ElfHeaderUtil::resolveAbiVersion(ElfHeader header){RETURN_CAST_FIELD(uint8_t, AbiVersion)}

ObjectFileType ElfHeaderUtil::resolveObjectFileType(ElfHeader header) {
  RETURN_CAST_FIELD(ObjectFileType, ObjectFileType);
}

Architecture ElfHeaderUtil::resolveArchitecture(ElfHeader header) { RETURN_CAST_FIELD(Architecture, Architecture); }

uint32_t ElfHeaderUtil::resolveObjectFileVersion(ElfHeader header) { RETURN_CAST_FIELD(uint32_t, ObjectFileVersion); }

uint64_t ElfHeaderUtil::resolveExecutionAddress(ElfHeader header) { RETURN_CAST_FIELD(uint64_t, Entry); }

uint64_t ElfHeaderUtil::resolveProgramHeaderTableAddress(ElfHeader header) {
  RETURN_CAST_FIELD(uint64_t, ProgramHeaderTableAddress);
}

uint64_t ElfHeaderUtil::resolveSectionTableAddress(ElfHeader header) {
  RETURN_CAST_FIELD(uint64_t, SectionTableAddress);
}

uint32_t ElfHeaderUtil::resolveFlags(ElfHeader header) { RETURN_CAST_FIELD(uint32_t, Flags); }

uint16_t ElfHeaderUtil::resolveHeaderSize(ElfHeader header) { RETURN_CAST_FIELD(uint16_t, HeaderSize); }

uint16_t ElfHeaderUtil::resolveProgramHeaderTableEntrySize(ElfHeader header) {
  RETURN_CAST_FIELD(uint16_t, ProgramHeaderTableSize);
}

uint16_t ElfHeaderUtil::resolveProgramHeaderTableEntryCount(ElfHeader header) {
  RETURN_CAST_FIELD(uint16_t, ProgramHeaderTableCount);
}

uint16_t ElfHeaderUtil::resolveSectionTableSize(ElfHeader header) { RETURN_CAST_FIELD(uint16_t, SectionTableSize); }

uint16_t ElfHeaderUtil::resolveSectionTableCount(ElfHeader header) { RETURN_CAST_FIELD(uint16_t, SectionTableCount); }

uint16_t ElfHeaderUtil::resolveSectionNameIndex(ElfHeader header) { RETURN_CAST_FIELD(uint16_t, SectionNameIndex); }

std::ostream &ElfHeaderUtil::print(std::ostream &os, ElfHeader header) {
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

  j["AddressClass"] = toString(ElfHeaderUtil::resolveAddressClass(header));
  j["Endianness"] = toString(ElfHeaderUtil::resolveEndianness(header));
  j["HeaderVersion"] = ElfHeaderUtil::resolveHeaderVersion(header);
  j["Abi"] = toString(ElfHeaderUtil::resolveABI(header));
  j["AbiVersion"] = ElfHeaderUtil::resolveAbiVersion(header);
  j["Padding"] = "       ";
  j["ObjectFileType"] = toString(ElfHeaderUtil::resolveObjectFileType(header));
  j["Architecture"] = toString(ElfHeaderUtil::resolveArchitecture(header));
  j["ObjectFileVersion"] = ElfHeaderUtil::resolveObjectFileVersion(header);
  j["ExecutionAddress"] = toHex(ElfHeaderUtil::resolveExecutionAddress(header));
  j["ProgramHeaderTableAddress"] = toHex(ElfHeaderUtil::resolveProgramHeaderTableAddress(header));
  j["SectionTableAddress"] = toHex(ElfHeaderUtil::resolveSectionTableAddress(header));
  j["Flags"] = toHex(ElfHeaderUtil::resolveFlags(header));
  j["HeaderSize"] = ElfHeaderUtil::resolveHeaderSize(header);
  j["ProgramHeaderTableSize"] = ElfHeaderUtil::resolveProgramHeaderTableEntrySize(header);
  j["ProgramHeaderTableCount"] = ElfHeaderUtil::resolveProgramHeaderTableEntryCount(header);
  j["SectionTableSize"] = ElfHeaderUtil::resolveSectionTableSize(header);
  j["SectionTableCount"] = ElfHeaderUtil::resolveSectionTableCount(header);
  j["SectionNameIndex"] = ElfHeaderUtil::resolveSectionNameIndex(header);
  os << j;
  return os;
}

#undef RETURN_CAST_FIELD
} // namespace NoobLink
