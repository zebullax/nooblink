﻿// File: layout.h
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
      // This member holds a section header's size in bytes. A section header is one entry in the section
      // header table; all entries are the same size.
      static constexpr size_t k_SectionTableSize = 0x3a;
      // This member holds the number of entries in the section header table. Thus the product of HeaderTableSize and
      // HeaderTableCount gives the section header table's size in bytes. If a file has no section header table,
      // k_SectionTableSize holds the value zero. If the number of sections is greater than or equal to SHN_LORESERVE
      // (0xff00), this member has the value zero and the actual number of section header table entries is contained
      // in the Section::k_Size field of the section header at index 0. (Otherwise, the k_Size member of the initial
      // entry contains 0.)
      static constexpr size_t k_SectionTableCount = 0x3c;
      // This member holds the section header table index of the entry associated with the section name string table. If
      // the file has no section name string table, this member holds the value SHN_UNDEF. If the section name string
      // table section index is greater than or equal to SHN_LORESERVE (0xff00), this member has the value SHN_XINDEX
      // (0xffff) and the actual index of the section name string table section is contained in the sh_link field of the
      // section header at index 0. (Otherwise, the sh_link member of the initial entry contains 0.)
      static constexpr size_t k_SectionNameIndex = 0x3e;
    };

    // Offset of each fields from individual entry start
    struct Section {
      // Index into section header string table
      static constexpr size_t k_NameIndex = 0x00;
      static constexpr size_t k_Type = 0x04;
      static constexpr size_t k_Flags = 0x08;
      // If section appear in final image of the process, this is the address where the section should start (otherwise
      // 0)
      static constexpr size_t k_Addr = 0x10;
      // Offset from the beginning of the file where first byte of this section appears
      static constexpr size_t k_Offset = 0x18;
      static constexpr size_t k_Size = 0x20;
      static constexpr size_t k_Link = 0x28;
      static constexpr size_t k_Info = 0x2c;
      static constexpr size_t k_AddrAlign = 0x30;
      static constexpr size_t k_EntrySize = 0x38;
    };
  }; // Describe size (bytes) of fields

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

} // namespace NoobLink

#endif // NOOBLINK_LAYOUT_H
