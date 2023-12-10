// File: elf_format.h
// Project: nooblink

#ifndef NOOBLINK_ELF_FORMAT_H
#define NOOBLINK_ELF_FORMAT_H

// nooblink
#include <address.h>
// std
#include <cstddef>
#include <cstdint>

namespace Nooblink {

// Describe length of fields in 32/64 bits ELF header
template <AddressingType AdType> struct ElfHeaderLength {
  static constexpr uint8_t k_Ident = 16;
  static constexpr uint8_t k_ObjectFileType = 2;
  static constexpr uint8_t k_Machine = 2;
  static constexpr uint8_t k_Version = 4;
  static constexpr uint8_t k_ExecutionAddress = AddressSize<AdType>::k_Value;
  static constexpr uint8_t k_HeaderTableAddress = AddressSize<AdType>::k_Value;
  static constexpr uint8_t k_SectionTableAddress = AddressSize<AdType>::k_Value;
  static constexpr uint8_t k_Flags = 4;
  static constexpr uint8_t k_ElfHeaderSize = 2;
  static constexpr uint8_t k_HeaderTableSize = 2;
  static constexpr uint8_t k_HeaderTableCount = 2;
  static constexpr uint8_t k_SectionTableSize = 2;
  static constexpr uint8_t k_SectionTableCount = 2;
  static constexpr uint8_t k_SectionNameIndex = 2;
};

template <AddressingType Length> struct ElfHeader {
  std::byte ident[ElfHeaderLength<Length>::k_Ident];
  std::byte objectFileType[ElfHeaderLength<Length>::k_ObjectFileType];
  std::byte machine[ElfHeaderLength<Length>::k_Machine];
  std::byte version[ElfHeaderLength<Length>::k_Version];
  std::byte executionEntryPoint[ElfHeaderLength<Length>::k_ExecutionAddress];
  std::byte headerTableOffset[ElfHeaderLength<Length>::k_HeaderTableAddress];
  std::byte sectionTableOffset[ElfHeaderLength<Length>::k_SectionTableAddress];
};

} // namespace Nooblink

#endif // NOOBLINK_ELF_FORMAT_H
