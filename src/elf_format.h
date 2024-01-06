// File: elf_format.h
// Project: nooblink

#ifndef NOOBLINK_ELF_FORMAT_H
#define NOOBLINK_ELF_FORMAT_H

// json
#include <nlohmann/json.hpp>
// std
#include <cstddef>
#include <span>

namespace NoobLink {

// Describe offset of fields
struct FieldOffset {
  struct Header {
    // Offset of each fields from file start
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

  struct Section {
    // Offset of each fields from entry start
    static constexpr size_t k_Name = 0x00;
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
};

// Describe size (bytes) of fields
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
    static constexpr size_t k_Name = 0x04;
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

// Alias over sequence of bytes covering the Elf header
using ElfHeader =
    std::span<std::byte, FieldOffset::Header::k_SectionNameIndex + FieldLength::Header::k_SectionNameIndex>;

// Alias over sequence of bytes representing a section entry
using SectionEntry = std::span<std::byte, FieldOffset::Section::k_EntrySize + FieldLength::Section::k_EntrySize>;

} // namespace NoobLink

#endif // NOOBLINK_ELF_FORMAT_H
