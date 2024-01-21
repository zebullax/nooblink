// -*-C++-*-
//
// File: elf_header.h
// Project: nooblink
//

#ifndef NOOBLINK_VOCABULARY_ELF_HEADER_H
#define NOOBLINK_VOCABULARY_ELF_HEADER_H

// nooblink
#include <raw/header_constants.h>
#include <raw/layout.h>
#include <raw/raw_elf_header.h>
// nlohmann
#include <nlohmann/json.hpp>
// std
#include <cstddef>

namespace nooblink {

class ElfHeader {
 public:
  // CREATORS

  // Construct this object from the specified 'rawHeader', the behavior is undefined if 'rawHeader' does not cover a
  // valid ELF raw header (ref. README).  Optionally specify an 'offset' to apply on all addresses that refer to content
  // to be found inside the object file described by this header
  explicit ElfHeader(RawElfHeader rawHeader, uint64_t offset = 0);

  // ACCESSORS

  // Return the offset applied to address referring to internal content
  [[nodiscard]] uint64_t offsetContent() const;

  // return the addressClass from this object
  [[nodiscard]] AddressClass addressClass() const;

  // return the endianness from this object
  [[nodiscard]] Endianness endianness() const;

  // return the headerVersion from this object
  [[nodiscard]] uint8_t headerVersion() const;

  // return the abi from this object
  [[nodiscard]] Abi abi() const;

  // return the abiVersion from this object
  [[nodiscard]] uint8_t abiVersion() const;

  // return the objectFileType from this object
  [[nodiscard]] ObjectFileType objectFileType() const;

  // return the architecture from this object
  [[nodiscard]] Architecture architecture() const;

  // return the objectFileVersion from this object
  [[nodiscard]] uint32_t objectFileVersion() const;

  // return the entry from this object
  [[nodiscard]] uint64_t entry() const;

  // return the programTableAddress from this object
  [[nodiscard]] std::byte* programTableAddress() const;

  // return the sectionTableAddress from this object
  [[nodiscard]] std::byte* sectionTableAddress() const;

  // return the flags from this object
  [[nodiscard]] uint32_t flags() const;

  // return the headerSize from this object
  [[nodiscard]] uint16_t headerSize() const;

  // return the programTableSize from this object
  [[nodiscard]] uint16_t programTableSize() const;

  // return the programTableCount from this object
  [[nodiscard]] uint16_t programTableCount() const;

  // return the sectionTableSize from this object. A section header is one entry in the section header table; all
  // entries are the same size.
  [[nodiscard]] uint16_t sectionTableSize() const;

  // return the sectionTableCount from this object.
  // This member holds the number of entries in the section header table.
  // Thus, the product of HeaderTableSize and HeaderTableCount gives the section header table's size in bytes. If a file
  // has no section header table, SectionTableSize holds the value zero. If the number of sections is greater than or
  // equal to SHN_LORESERVE (0xff00), this member has the value zero and the actual number of section header table
  // entries is contained in the Section::k_Size field of the section header at index 0. (Otherwise, the k_Size member
  // of the initial entry contains 0.)
  [[nodiscard]] uint16_t sectionTableCount() const;

  // return the sectionNameIndex from this object.
  // This member holds the section header table index of the entry associated with the section name string table. If
  // the file has no section name string table, this member holds the value SHN_UNDEF. If the section name string
  // table section index is greater than or equal to SHN_LORESERVE (0xff00), this member has the value SHN_XINDEX
  // (0xffff) and the actual index of the section name string table section is contained in the sh_link field of the
  // section header at index 0. (Otherwise, the sh_link member of the initial entry contains 0.)
  [[nodiscard]] uint16_t sectionNameIndex() const;

  // Render and return a json representation for this object
  nlohmann::json json() const;

 private:
  // FRIENDS

  friend std::ostream& operator<<(std::ostream& os, const ElfHeader& elfHeader);

  // DATA

  uint64_t d_offsetContent;
  [[maybe_unused]] bool d_isSupported;
  AddressClass d_addressClass;
  Endianness d_endianness;
  uint8_t d_headerVersion;
  Abi d_abi;
  uint8_t d_abiVersion;
  ObjectFileType d_objectFileType;
  Architecture d_architecture;
  uint32_t d_objectFileVersion;
  uint64_t d_entry;
  uint64_t d_programTableAddress;
  uint64_t d_sectionTableAddress;
  uint32_t d_flags;
  uint16_t d_headerSize;
  uint16_t d_programTableSize;
  uint16_t d_programTableCount;
  uint16_t d_sectionTableSize;
  uint16_t d_sectionTableCount;
  uint16_t d_sectionNameIndex;
};
}  // namespace nooblink

#endif
