// -*-C++-*-
//
// File: raw_elf_header_util.h
// Project: nooblink
//

#ifndef NOOBLINK_RAW_ELF_HEADER_UTIL_H
#define NOOBLINK_RAW_ELF_HEADER_UTIL_H

// nooblink
#include <raw/header_constants.h>
#include <raw/layout.h>
#include <raw/raw_elf_header.h>
// std
#include <cstdint>

namespace nooblink {

struct RawElfHeaderUtil {
  RawElfHeaderUtil() = delete;

  // Return whether the specified 'header' is Elf
  static bool isElf(RawElfHeader header);

  // Return the address class from the specified 'header'
  static AddressClass addressClass(RawElfHeader header);

  // Return the endianness from the specified 'header'
  static Endianness endianness(RawElfHeader header);

  // Return header version from specified 'header'
  static uint8_t headerVersion(RawElfHeader header);

  // Return the ABI from the specified 'header'
  static Abi abi(RawElfHeader header);

  // Return ABI version from specified 'header'
  static uint8_t abiVersion(RawElfHeader header);

  // Return the object file type from the specified 'header'
  static ObjectFileType objectFileType(RawElfHeader header);

  // Return object file version from specified 'header'
  static uint32_t objectFileVersion(RawElfHeader header);

  // Return the architecture from the specified 'header'
  static Architecture architecture(RawElfHeader header);

  // Return the ExecutionAddress from the specified 'header'
  static uint64_t executionAddress(RawElfHeader header);

  // Return the size of the ELF header
  static uint16_t headerSize(RawElfHeader header);

  // Return the flags from the specified 'header'
  static uint32_t flags(RawElfHeader header);

  // Return the ProgramTableAddress from the specified 'header'
  static uint64_t ProgramTableAddress(RawElfHeader header);

  // Return the ProgramTableEntrySize from the specified 'header'
  static uint16_t ProgramTableEntrySize(RawElfHeader header);

  // Return the ProgramTableEntryCount from the specified 'header'
  static uint16_t ProgramTableEntryCount(RawElfHeader header);

  // Return the SectionTableAddress from the specified 'header'
  static uint64_t sectionTableAddress(RawElfHeader header);

  // Return the size of a section table entry from the specified 'header'
  static uint16_t sectionTableSize(RawElfHeader header);

  // Return the number of section table entry from the specified 'header'
  static uint16_t sectionTableCount(RawElfHeader header);

  // Return the SectionNameIndex from the specified 'header'
  static uint16_t sectionNameIndex(RawElfHeader header);
};

}  // namespace nooblink

#endif  // NOOBLINK_RAW_ELF_HEADER_UTIL_H
