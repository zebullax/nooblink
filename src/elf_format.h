// File: elf_format.h
// Project: nooblink

#ifndef NOOBLINK_ELF_FORMAT_H
#define NOOBLINK_ELF_FORMAT_H

// json
#include <nlohmann/json.hpp>
// std
#include <array>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <sstream>

namespace NoobLink {

// Describe size (bytes) of fields in ELF 64 header
struct ElfHeader64FieldLength {
  static constexpr size_t k_Ident = 4;
  static constexpr size_t k_AddressClass = 1;
  static constexpr size_t k_Endianness = 1;
  static constexpr size_t k_ElfVersion = 1;
  static constexpr size_t k_Abi = 1;
  static constexpr size_t k_AbiVersion = 1;
  static constexpr size_t k_Padding = 7;
  // Endianness matter from here onward
  static constexpr size_t k_ObjectFileType = 2;
  static constexpr size_t k_Machine = 2;
  static constexpr size_t k_Version = 4;
  static constexpr size_t k_ExecutionAddress = 4;
  static constexpr size_t k_HeaderTableAddress = 4;
  static constexpr size_t k_SectionTableAddress = 4;
  static constexpr size_t k_Flags = 4;
  static constexpr size_t k_ElfHeaderSize = 2;
  static constexpr size_t k_HeaderTableSize = 2;
  static constexpr size_t k_HeaderTableCount = 2;
  static constexpr size_t k_SectionTableSize = 2;
  static constexpr size_t k_SectionTableCount = 2;
  static constexpr size_t k_SectionNameIndex = 2;
};

// Describe offset of fields in ELF 64 header
struct ElfHeader64FieldOffset {
  static constexpr size_t k_Ident = 0x00;
  static constexpr size_t k_AddressClass = 0x04;
  static constexpr size_t k_Endianness = 0x05;
  static constexpr size_t k_ElfVersion = 0x06;
  static constexpr size_t k_Abi = 0x07;
  static constexpr size_t k_AbiVersion = 0x08;
  static constexpr size_t k_Padding = 0x09;
  static constexpr size_t k_ObjectFileType = 0x10;
  static constexpr size_t k_Machine = 0x12;
  static constexpr size_t k_Version = 0x14;
  static constexpr size_t k_ExecutionAddress = 0x18;
  static constexpr size_t k_HeaderTableAddress = 0x20;
  static constexpr size_t k_SectionTableAddress = 0x28;
  static constexpr size_t k_Flags = 0x30;
  static constexpr size_t k_ElfHeaderSize = 0x34;
  static constexpr size_t k_HeaderTableSize = 0x36;
  static constexpr size_t k_HeaderTableCount = 0x38;
  static constexpr size_t k_SectionTableSize = 0x3a;
  static constexpr size_t k_SectionTableCount = 0x3c;
  static constexpr size_t k_SectionNameIndex = 0x3e;
};

// Sequence of raw bytes covering the Elf 64 header
using Elf64Header =  std::array<std::byte, ElfHeader64FieldOffset::k_SectionNameIndex + ElfHeader64FieldLength::k_SectionNameIndex>;

} // namespace NoobLink

#endif // NOOBLINK_ELF_FORMAT_H
