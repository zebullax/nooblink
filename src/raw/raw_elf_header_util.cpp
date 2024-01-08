// File: elf_header_util.cpp
// Project: nooblink
//

// nooblink
#include "raw/raw_elf_header_util.h"
#include "byte_util.h"
// std
#include <span>

namespace NoobLink {

// Macro to cast the specified 'FIELD_NAME' from the header to the specified 'TARGET_TYPE'
#define RETURN_CAST_FIELD(TARGET_TYPE, FIELD_NAME)                                                                     \
  std::span field =                                                                                                    \
      header.subspan<Layout::FieldOffset::Header::k_##FIELD_NAME, Layout::FieldLength::Header::k_##FIELD_NAME>();      \
  return ByteUtil::convertTo<TARGET_TYPE>(field);

bool RawElfHeaderUtil::isElf(RawElfHeader header) {
  std::span ident = header.first(4);

  return ident[0] == std::byte(0x7F) && ident[1] == std::byte(0x45) && ident[2] == std::byte(0x4c) &&
         ident[3] == std::byte(0x46);
}

Endianness RawElfHeaderUtil::endianness(RawElfHeader header) { RETURN_CAST_FIELD(Endianness, Endianness); }

uint8_t RawElfHeaderUtil::headerVersion(RawElfHeader header){RETURN_CAST_FIELD(uint8_t, HeaderVersion)}

AddressClass RawElfHeaderUtil::addressClass(RawElfHeader header) {
  RETURN_CAST_FIELD(AddressClass, AddressClass);
}

Abi RawElfHeaderUtil::abi(RawElfHeader header) { RETURN_CAST_FIELD(Abi, Abi); }

uint8_t RawElfHeaderUtil::abiVersion(RawElfHeader header){RETURN_CAST_FIELD(uint8_t, AbiVersion)}

ObjectFileType RawElfHeaderUtil::objectFileType(RawElfHeader header) {
  RETURN_CAST_FIELD(ObjectFileType, ObjectFileType);
}

Architecture RawElfHeaderUtil::architecture(RawElfHeader header) { RETURN_CAST_FIELD(Architecture, Architecture); }

uint32_t RawElfHeaderUtil::objectFileVersion(RawElfHeader header) { RETURN_CAST_FIELD(uint32_t, ObjectFileVersion); }

uint64_t RawElfHeaderUtil::executionAddress(RawElfHeader header) { RETURN_CAST_FIELD(uint64_t, Entry); }

uint64_t RawElfHeaderUtil::ProgramTableAddress(RawElfHeader header) {
  RETURN_CAST_FIELD(uint64_t, ProgramTableAddress);
}

uint64_t RawElfHeaderUtil::sectionTableAddress(RawElfHeader header) {
  RETURN_CAST_FIELD(uint64_t, SectionTableAddress);
}

uint32_t RawElfHeaderUtil::flags(RawElfHeader header) { RETURN_CAST_FIELD(uint32_t, Flags); }

uint16_t RawElfHeaderUtil::headerSize(RawElfHeader header) { RETURN_CAST_FIELD(uint16_t, HeaderSize); }

uint16_t RawElfHeaderUtil::ProgramTableEntrySize(RawElfHeader header) { RETURN_CAST_FIELD(uint16_t, ProgramTableSize); }

uint16_t RawElfHeaderUtil::ProgramTableEntryCount(RawElfHeader header) {
  RETURN_CAST_FIELD(uint16_t, ProgramTableCount);
}

uint16_t RawElfHeaderUtil::sectionTableSize(RawElfHeader header) { RETURN_CAST_FIELD(uint16_t, SectionTableSize); }

uint16_t RawElfHeaderUtil::sectionTableCount(RawElfHeader header) { RETURN_CAST_FIELD(uint16_t, SectionTableCount); }

uint16_t RawElfHeaderUtil::sectionNameIndex(RawElfHeader header) { RETURN_CAST_FIELD(uint16_t, SectionNameIndex); }

#undef RETURN_CAST_FIELD
} // namespace NoobLink
