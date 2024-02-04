// -*-C++-*-
//
// File: elf_header.cpp
// Project: nooblink
//

// nooblink
#include <raw/raw_elf_header_util.h>
#include <vocabulary/elf_header.h>
// json
#include <nlohmann/json.hpp>
// std
#include <cassert>
#include <iomanip>
#include <sstream>

namespace nooblink {

ElfHeader::ElfHeader(RawElfHeader rawHeader)
    : d_isSupported((assert(RawElfHeaderUtil::isElf(rawHeader)), true)),
      d_addressClass(RawElfHeaderUtil::addressClass(rawHeader)),
      d_endianness(RawElfHeaderUtil::endianness(rawHeader)),
      d_headerVersion(RawElfHeaderUtil::headerVersion(rawHeader)),
      d_abi(RawElfHeaderUtil::abi(rawHeader)),
      d_abiVersion(RawElfHeaderUtil::abiVersion(rawHeader)),
      d_objectFileType(RawElfHeaderUtil::objectFileType(rawHeader)),
      d_architecture(RawElfHeaderUtil::architecture(rawHeader)),
      d_objectFileVersion(RawElfHeaderUtil::objectFileVersion(rawHeader)),
      d_entry(RawElfHeaderUtil::executionAddress(rawHeader)),
      d_programTableAddress(RawElfHeaderUtil::ProgramTableAddress(rawHeader)),
      d_sectionTableAddress(RawElfHeaderUtil::sectionTableAddress(rawHeader)),
      d_flags(RawElfHeaderUtil::flags(rawHeader)),
      d_headerSize(RawElfHeaderUtil::headerSize(rawHeader)),
      d_programTableSize(RawElfHeaderUtil::ProgramTableEntrySize(rawHeader)),
      d_programTableCount(RawElfHeaderUtil::ProgramTableEntryCount(rawHeader)),
      d_sectionTableSize(RawElfHeaderUtil::sectionTableSize(rawHeader)),
      d_sectionTableCount(RawElfHeaderUtil::sectionTableCount(rawHeader)),
      d_sectionNameIndex(RawElfHeaderUtil::sectionNameIndex(rawHeader)) {}

AddressClass ElfHeader::addressClass() const { return d_addressClass; }

Endianness ElfHeader::endianness() const { return d_endianness; }

uint8_t ElfHeader::headerVersion() const { return d_headerVersion; }

Abi ElfHeader::abi() const { return d_abi; }

uint8_t ElfHeader::abiVersion() const { return d_abiVersion; }

ObjectFileType ElfHeader::objectFileType() const { return d_objectFileType; }

Architecture ElfHeader::architecture() const { return d_architecture; }

uint32_t ElfHeader::objectFileVersion() const { return d_objectFileVersion; }

uint64_t ElfHeader::entry() const { return d_entry; }

std::byte* ElfHeader::programTableAddress() const { return reinterpret_cast<std::byte*>(d_programTableAddress); }

std::byte* ElfHeader::sectionTableAddress() const { return reinterpret_cast<std::byte*>(d_sectionTableAddress); }

uint32_t ElfHeader::flags() const { return d_flags; }

uint16_t ElfHeader::headerSize() const { return d_headerSize; }

uint16_t ElfHeader::programTableSize() const { return d_programTableSize; }

uint16_t ElfHeader::programTableCount() const { return d_programTableCount; }

uint16_t ElfHeader::sectionTableSize() const { return d_sectionTableSize; }

uint16_t ElfHeader::sectionTableCount() const { return d_sectionTableCount; }

uint16_t ElfHeader::sectionNameIndex() const { return d_sectionNameIndex; }

nlohmann::json ElfHeader::json() const {
  auto toString = [](auto e) {
    std::ostringstream oss;
    oss << e;
    return oss.str();
  };

  auto toHex = [](auto e) {
    std::ostringstream oss;
    oss << "0x" << std::hex << std::setw(sizeof(e)) << std::setfill('0') << e;
    return oss.str();
  };

  using json = nlohmann::json;
  json j;

  j["addressClass"] = toString(d_addressClass);
  j["endianness"] = toString(d_endianness);
  j["headerVersion"] = d_headerVersion;
  j["abi"] = toString(d_abi);
  j["abiVersion"] = d_abiVersion;
  j["padding"] = "       ";
  j["objectFileType"] = toString(d_objectFileType);
  j["architecture"] = toString(d_architecture);
  j["objectFileVersion"] = d_objectFileVersion;
  j["executionAddress"] = toHex(d_entry);
  j["programTableAddress"] = toHex(d_programTableAddress);
  j["sectionTableAddress"] = toHex(d_sectionTableAddress);
  j["flags"] = toHex(d_flags);
  j["headerSize"] = d_headerSize;
  j["programTableSize"] = d_programTableSize;
  j["programTableCount"] = d_programTableCount;
  j["sectionTableSize"] = d_sectionTableSize;
  j["sectionTableCount"] = d_sectionTableCount;
  j["sectionNameIndex"] = d_sectionNameIndex;
  return j;
}

}  // namespace nooblink
