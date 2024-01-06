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

Endianness ElfHeaderUtil::endianness(ElfHeader header) { RETURN_CAST_FIELD(Endianness, Endianness); }

uint8_t ElfHeaderUtil::headerVersion(ElfHeader header){RETURN_CAST_FIELD(uint8_t, HeaderVersion)}

AddressClass ElfHeaderUtil::addressClass(ElfHeader header) {
  RETURN_CAST_FIELD(AddressClass, AddressClass);
}

Abi ElfHeaderUtil::abi(ElfHeader header) { RETURN_CAST_FIELD(Abi, Abi); }

uint8_t ElfHeaderUtil::abiVersion(ElfHeader header){RETURN_CAST_FIELD(uint8_t, AbiVersion)}

ObjectFileType ElfHeaderUtil::objectFileType(ElfHeader header) {
  RETURN_CAST_FIELD(ObjectFileType, ObjectFileType);
}

Architecture ElfHeaderUtil::architecture(ElfHeader header) { RETURN_CAST_FIELD(Architecture, Architecture); }

uint32_t ElfHeaderUtil::objectFileVersion(ElfHeader header) { RETURN_CAST_FIELD(uint32_t, ObjectFileVersion); }

uint64_t ElfHeaderUtil::executionAddress(ElfHeader header) { RETURN_CAST_FIELD(uint64_t, Entry); }

uint64_t ElfHeaderUtil::ProgramTableAddress(ElfHeader header) { RETURN_CAST_FIELD(uint64_t, ProgramTableAddress); }

uint64_t ElfHeaderUtil::sectionTableAddress(ElfHeader header) { RETURN_CAST_FIELD(uint64_t, SectionTableAddress); }

uint32_t ElfHeaderUtil::flags(ElfHeader header) { RETURN_CAST_FIELD(uint32_t, Flags); }

uint16_t ElfHeaderUtil::headerSize(ElfHeader header) { RETURN_CAST_FIELD(uint16_t, HeaderSize); }

uint16_t ElfHeaderUtil::ProgramTableEntrySize(ElfHeader header) { RETURN_CAST_FIELD(uint16_t, ProgramTableSize); }

uint16_t ElfHeaderUtil::ProgramTableEntryCount(ElfHeader header) { RETURN_CAST_FIELD(uint16_t, ProgramTableCount); }

uint16_t ElfHeaderUtil::sectionTableSize(ElfHeader header) { RETURN_CAST_FIELD(uint16_t, SectionTableSize); }

uint16_t ElfHeaderUtil::sectionTableCount(ElfHeader header) { RETURN_CAST_FIELD(uint16_t, SectionTableCount); }

uint16_t ElfHeaderUtil::sectionNameIndex(ElfHeader header) { RETURN_CAST_FIELD(uint16_t, SectionNameIndex); }

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

  j["AddressClass"] = toString(ElfHeaderUtil::addressClass(header));
  j["Endianness"] = toString(ElfHeaderUtil::endianness(header));
  j["HeaderVersion"] = ElfHeaderUtil::headerVersion(header);
  j["Abi"] = toString(ElfHeaderUtil::abi(header));
  j["AbiVersion"] = ElfHeaderUtil::abiVersion(header);
  j["Padding"] = "       ";
  j["ObjectFileType"] = toString(ElfHeaderUtil::objectFileType(header));
  j["Architecture"] = toString(ElfHeaderUtil::architecture(header));
  j["ObjectFileVersion"] = ElfHeaderUtil::objectFileVersion(header);
  j["ExecutionAddress"] = toHex(ElfHeaderUtil::executionAddress(header));
  j["ProgramTableAddress"] = toHex(ElfHeaderUtil::ProgramTableAddress(header));
  j["SectionTableAddress"] = toHex(ElfHeaderUtil::sectionTableAddress(header));
  j["Flags"] = toHex(ElfHeaderUtil::flags(header));
  j["HeaderSize"] = ElfHeaderUtil::headerSize(header);
  j["ProgramTableSize"] = ElfHeaderUtil::ProgramTableEntrySize(header);
  j["ProgramTableCount"] = ElfHeaderUtil::ProgramTableEntryCount(header);
  j["SectionTableSize"] = ElfHeaderUtil::sectionTableSize(header);
  j["SectionTableCount"] = ElfHeaderUtil::sectionTableCount(header);
  j["SectionNameIndex"] = ElfHeaderUtil::sectionNameIndex(header);
  os << j;
  return os;
}

#undef RETURN_CAST_FIELD
} // namespace NoobLink
