// File: ElfHeader.cpp
// Project: nooblink
//

// nooblink
#include <format/elf_header.h>
#include <format/raw_header_util.h>
// json
#include <nlohmann/json.hpp>
// std
#include <cassert>
#include <iomanip>
#include <sstream>

namespace NoobLink {

ElfHeader::ElfHeader(NoobLink::RawElfHeader rawHeader)
    : d_isSupported(RawHeaderUtil::isElf(rawHeader)), d_addressClass(RawHeaderUtil::addressClass(rawHeader)),
      d_endianness(RawHeaderUtil::endianness(rawHeader)), d_headerVersion(RawHeaderUtil::headerVersion(rawHeader)),
      d_abi(RawHeaderUtil::abi(rawHeader)), d_abiVersion(RawHeaderUtil::abiVersion(rawHeader)),
      d_objectFileType(RawHeaderUtil::objectFileType(rawHeader)),
      d_architecture(RawHeaderUtil::architecture(rawHeader)),
      d_objectFileVersion(RawHeaderUtil::objectFileVersion(rawHeader)),
      d_entry(RawHeaderUtil::executionAddress(rawHeader)),
      d_programTableAddress(RawHeaderUtil::ProgramTableAddress(rawHeader)),
      d_sectionTableAddress(RawHeaderUtil::sectionTableAddress(rawHeader)), d_flags(RawHeaderUtil::flags(rawHeader)),
      d_headerSize(RawHeaderUtil::headerSize(rawHeader)),
      d_programTableSize(RawHeaderUtil::ProgramTableEntrySize(rawHeader)),
      d_programTableCount(RawHeaderUtil::ProgramTableEntryCount(rawHeader)),
      d_sectionTableSize(RawHeaderUtil::sectionTableSize(rawHeader)),
      d_sectionTableCount(RawHeaderUtil::sectionTableCount(rawHeader)),
      d_sectionNameIndex(RawHeaderUtil::sectionNameIndex(rawHeader)) {}

AddressClass ElfHeader::getAddressClass() const { return d_addressClass; }

Endianness ElfHeader::getEndianness() const { return d_endianness; }

uint8_t ElfHeader::getHeaderVersion() const { return d_headerVersion; }

Abi ElfHeader::getAbi() const { return d_abi; }

uint8_t ElfHeader::getAbiVersion() const { return d_abiVersion; }

ObjectFileType ElfHeader::getObjectFileType() const { return d_objectFileType; }

Architecture ElfHeader::getArchitecture() const { return d_architecture; }

uint32_t ElfHeader::getObjectFileVersion() const { return d_objectFileVersion; }

uint64_t ElfHeader::getEntry() const { return d_entry; }

uint64_t ElfHeader::getProgramTableAddress() const { return d_programTableAddress; }

uint64_t ElfHeader::getSectionTableAddress() const { return d_sectionTableAddress; }

uint32_t ElfHeader::getFlags() const { return d_flags; }

uint16_t ElfHeader::getHeaderSize() const { return d_headerSize; }

uint16_t ElfHeader::getProgramTableSize() const { return d_programTableSize; }

uint16_t ElfHeader::getProgramTableCount() const { return d_programTableCount; }

uint16_t ElfHeader::getSectionTableSize() const { return d_sectionTableSize; }

uint16_t ElfHeader::getSectionTableCount() const { return d_sectionTableCount; }

uint16_t ElfHeader::getSectionNameIndex() const { return d_sectionNameIndex; }

std::ostream &ElfHeader::print(std::ostream &os) const {
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

  j["AddressClass"] = toString(d_addressClass);
  j["Endianness"] = toString(d_endianness);
  j["HeaderVersion"] = d_headerVersion;
  j["Abi"] = toString(d_abi);
  j["AbiVersion"] = d_abiVersion;
  j["Padding"] = "       ";
  j["ObjectFileType"] = toString(d_objectFileType);
  j["Architecture"] = toString(d_architecture);
  j["ObjectFileVersion"] = d_objectFileVersion;
  j["ExecutionAddress"] = toHex(d_entry);
  j["ProgramTableAddress"] = toHex(d_programTableAddress);
  j["SectionTableAddress"] = toHex(d_sectionTableAddress);
  j["Flags"] = toHex(d_flags);
  j["HeaderSize"] = d_headerSize;
  j["ProgramTableSize"] = d_programTableSize;
  j["ProgramTableCount"] = d_programTableCount;
  j["SectionTableSize"] = d_sectionTableSize;
  j["SectionTableCount"] = d_sectionTableCount;
  j["SectionNameIndex"] = d_sectionNameIndex;
  os << j;
  return os;
}

} // namespace NoobLink
