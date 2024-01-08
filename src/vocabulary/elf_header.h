// File: elf_header.h
// Project: nooblink
//

#ifndef NOOBLINK_VOCABULARY_ELF_HEADER_H
#define NOOBLINK_VOCABULARY_ELF_HEADER_H

// nooblink
#include "raw/header_constants.h"
#include "raw/layout.h"
#include "raw/raw_elf_header.h"

namespace NoobLink {

class ElfHeader {
public:
  // CREATORS

  // Construct this object from the specified 'rawHeader', the behavior is undefined if 'rawHeader' is related to an
  // unsupported raw (ref. README)
  explicit ElfHeader(RawElfHeader rawHeader);

  // ACCESSORS

  // return the addressClass from this object
  AddressClass getAddressClass() const;

  // return the endianness from this object
  Endianness getEndianness() const;

  // return the headerVersion from this object
  uint8_t getHeaderVersion() const;

  // return the abi from this object
  Abi getAbi() const;

  // return the abiVersion from this object
  uint8_t getAbiVersion() const;

  // return the objectFileType from this object
  ObjectFileType getObjectFileType() const;

  // return the architecture from this object
  Architecture getArchitecture() const;

  // return the objectFileVersion from this object
  uint32_t getObjectFileVersion() const;

  // return the entry from this object
  uint64_t getEntry() const;

  // return the programTableAddress from this object
  uint64_t getProgramTableAddress() const;

  // return the sectionTableAddress from this object
  uint64_t getSectionTableAddress() const;

  // return the flags from this object
  uint32_t getFlags() const;

  // return the headerSize from this object
  uint16_t getHeaderSize() const;

  // return the programTableSize from this object
  uint16_t getProgramTableSize() const;

  // return the programTableCount from this object
  uint16_t getProgramTableCount() const;

  // return the sectionTableSize from this object
  uint16_t getSectionTableSize() const;

  // return the sectionTableCount from this object
  uint16_t getSectionTableCount() const;

  // return the sectionNameIndex from this object
  uint16_t getSectionNameIndex() const;

  // Output to the specified 'os' a JSON representation of this object, return the stream
  std::ostream &print(std::ostream &os) const;

private:
  bool d_isSupported;
  AddressClass d_addressClass;
  Endianness d_endianness;
  uint8_t d_headerVersion{};
  Abi d_abi{};
  uint8_t d_abiVersion{};
  ObjectFileType d_objectFileType;
  Architecture d_architecture;
  uint32_t d_objectFileVersion{};
  uint64_t d_entry{};
  uint64_t d_programTableAddress{};
  uint64_t d_sectionTableAddress{};
  uint32_t d_flags{};
  uint16_t d_headerSize{};
  uint16_t d_programTableSize{};
  uint16_t d_programTableCount{};
  uint16_t d_sectionTableSize{};
  uint16_t d_sectionTableCount{};
  uint16_t d_sectionNameIndex{};
};
} // namespace NoobLink

#endif // NOOBLINK_ELF_HEADER_H
