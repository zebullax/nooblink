// File: elf_header_util.cpp
// Project: nooblink
//

// nooblink
#include <byte_util.h>
#include <format/raw_header_util.h>
// std
#include <span>

namespace NoobLink {
namespace {

// Macro to cast the specified 'FIELD_NAME' from the header to the specified 'TARGET_TYPE'
#define RETURN_CAST_FIELD(TARGET_TYPE, FIELD_NAME)                                                                     \
  std::span field = header.subspan<FieldOffset::Header::k_##FIELD_NAME, FieldLength::Header::k_##FIELD_NAME>();        \
  return ByteUtil::convertTo<TARGET_TYPE>(field);

} // anonymous namespace

bool RawHeaderUtil::isElf(RawElfHeader header) {
  std::span ident = header.first(4);

  return ident[0] == std::byte(0x7F) && ident[1] == std::byte(0x45) && ident[2] == std::byte(0x4c) &&
         ident[3] == std::byte(0x46);
}

Endianness RawHeaderUtil::endianness(RawElfHeader header) { RETURN_CAST_FIELD(Endianness, Endianness); }

uint8_t RawHeaderUtil::headerVersion(RawElfHeader header){RETURN_CAST_FIELD(uint8_t, HeaderVersion)}

AddressClass RawHeaderUtil::addressClass(RawElfHeader header) {
  RETURN_CAST_FIELD(AddressClass, AddressClass);
}

Abi RawHeaderUtil::abi(RawElfHeader header) { RETURN_CAST_FIELD(Abi, Abi); }

uint8_t RawHeaderUtil::abiVersion(RawElfHeader header){RETURN_CAST_FIELD(uint8_t, AbiVersion)}

ObjectFileType RawHeaderUtil::objectFileType(RawElfHeader header) {
  RETURN_CAST_FIELD(ObjectFileType, ObjectFileType);
}

Architecture RawHeaderUtil::architecture(RawElfHeader header) { RETURN_CAST_FIELD(Architecture, Architecture); }

uint32_t RawHeaderUtil::objectFileVersion(RawElfHeader header) { RETURN_CAST_FIELD(uint32_t, ObjectFileVersion); }

uint64_t RawHeaderUtil::executionAddress(RawElfHeader header) { RETURN_CAST_FIELD(uint64_t, Entry); }

uint64_t RawHeaderUtil::ProgramTableAddress(RawElfHeader header) { RETURN_CAST_FIELD(uint64_t, ProgramTableAddress); }

uint64_t RawHeaderUtil::sectionTableAddress(RawElfHeader header) { RETURN_CAST_FIELD(uint64_t, SectionTableAddress); }

uint32_t RawHeaderUtil::flags(RawElfHeader header) { RETURN_CAST_FIELD(uint32_t, Flags); }

uint16_t RawHeaderUtil::headerSize(RawElfHeader header) { RETURN_CAST_FIELD(uint16_t, HeaderSize); }

uint16_t RawHeaderUtil::ProgramTableEntrySize(RawElfHeader header) { RETURN_CAST_FIELD(uint16_t, ProgramTableSize); }

uint16_t RawHeaderUtil::ProgramTableEntryCount(RawElfHeader header) { RETURN_CAST_FIELD(uint16_t, ProgramTableCount); }

uint16_t RawHeaderUtil::sectionTableSize(RawElfHeader header) { RETURN_CAST_FIELD(uint16_t, SectionTableSize); }

uint16_t RawHeaderUtil::sectionTableCount(RawElfHeader header) { RETURN_CAST_FIELD(uint16_t, SectionTableCount); }

uint16_t RawHeaderUtil::sectionNameIndex(RawElfHeader header) { RETURN_CAST_FIELD(uint16_t, SectionNameIndex); }

#undef RETURN_CAST_FIELD
} // namespace NoobLink
