// -*-C++-*-
//
// File: layout.h
// Project: nooblink
//

#ifndef NOOBLINK_RAW_LAYOUT_H
#define NOOBLINK_RAW_LAYOUT_H

// std
#include <cstddef>
#include <span>

namespace NoobLink {

struct Layout {
  // Describe offset of fields
  struct FieldOffset {
    // Offset of each fields from file start
    struct Header {
      static constexpr size_t k_Ident = 0x00;
      static constexpr size_t k_AddressClass = 0x04;
      static constexpr size_t k_Endianness = 0x05;
      static constexpr size_t k_HeaderVersion = 0x06;
      static constexpr size_t k_Abi = 0x07;
      static constexpr size_t k_AbiVersion = 0x08;
      static constexpr size_t k_Padding = 0x09;
      static constexpr size_t k_ObjectFileType = 0x10;
      static constexpr size_t k_Architecture = 0x12;
      static constexpr size_t k_ObjectFileVersion = 0x14;
      static constexpr size_t k_Entry = 0x18;
      static constexpr size_t k_ProgramTableAddress = 0x20;
      static constexpr size_t k_SectionTableAddress = 0x28;
      static constexpr size_t k_Flags = 0x30;
      static constexpr size_t k_HeaderSize = 0x34;
      static constexpr size_t k_ProgramTableSize = 0x36;
      static constexpr size_t k_ProgramTableCount = 0x38;
      static constexpr size_t k_SectionTableSize = 0x3a;
      static constexpr size_t k_SectionTableCount = 0x3c;
      static constexpr size_t k_SectionNameIndex = 0x3e;
    };

    // Offset of each fields from individual entry start
    struct Section {
      // Index into section header string table
      static constexpr size_t k_NameIndex = 0x00;
      static constexpr size_t k_Type = 0x04;
      static constexpr size_t k_Flags = 0x08;
      static constexpr size_t k_Addr = 0x10;
      static constexpr size_t k_Offset = 0x18;
      static constexpr size_t k_Size = 0x20;
      static constexpr size_t k_Link = 0x28;
      static constexpr size_t k_Info = 0x2c;
      static constexpr size_t k_AddrAlign = 0x30;
      static constexpr size_t k_EntrySize = 0x38;
    };
  };  // Describe size (bytes) of fields

  struct FieldLength {
    struct Header {
      static constexpr size_t k_Ident = 4;
      static constexpr size_t k_AddressClass = 1;
      static constexpr size_t k_Endianness = 1;
      static constexpr size_t k_HeaderVersion = 1;
      static constexpr size_t k_Abi = 1;
      static constexpr size_t k_AbiVersion = 1;
      static constexpr size_t k_Padding = 7;
      // Endianness matter from here onward
      static constexpr size_t k_ObjectFileType = 2;
      static constexpr size_t k_Architecture = 2;
      static constexpr size_t k_ObjectFileVersion = 4;
      static constexpr size_t k_Entry = 8;
      static constexpr size_t k_ProgramTableAddress = 8;
      static constexpr size_t k_SectionTableAddress = 8;
      static constexpr size_t k_Flags = 4;
      static constexpr size_t k_HeaderSize = 2;
      static constexpr size_t k_ProgramTableSize = 2;
      static constexpr size_t k_ProgramTableCount = 2;
      static constexpr size_t k_SectionTableSize = 2;
      static constexpr size_t k_SectionTableCount = 2;
      static constexpr size_t k_SectionNameIndex = 2;
    };

    struct Section {
      static constexpr size_t k_NameIndex = 0x04;
      static constexpr size_t k_Type = 0x04;
      static constexpr size_t k_Flags = 0x08;
      static constexpr size_t k_Addr = 0x08;
      static constexpr size_t k_Offset = 0x08;
      static constexpr size_t k_Size = 0x08;
      static constexpr size_t k_Link = 0x04;
      static constexpr size_t k_Info = 0x04;
      static constexpr size_t k_AddrAlign = 0x08;
      static constexpr size_t k_EntrySize = 0x08;
    };
  };
};

}  // namespace NoobLink

#endif  // NOOBLINK_LAYOUT_H
