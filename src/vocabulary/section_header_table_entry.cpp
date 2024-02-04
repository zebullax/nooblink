// -*-C++-*-
//
// File: section_header_table_entry.cpp
// Project: nooblink
//

#include <vocabulary/section_header_table_entry.h>
// nooblink
#include <raw/raw_section_header_util.h>
// json
#include <nlohmann/json.hpp>
// std
#include <sstream>
#include <utility>

namespace nooblink {
namespace {
SectionHeaderTableEntry::Flags decodeSectionFlags(uint64_t rawFlags) {
  return SectionHeaderTableEntry::Flags{
      (rawFlags & std::to_underlying(SectionFlag::e_Write)) == std::to_underlying(SectionFlag::e_Write),
      (rawFlags & std::to_underlying(SectionFlag::e_Alloc)) == std::to_underlying(SectionFlag::e_Alloc),
      (rawFlags & std::to_underlying(SectionFlag::e_Execinstr)) == std::to_underlying(SectionFlag::e_Execinstr),
      (rawFlags & std::to_underlying(SectionFlag::e_Merge)) == std::to_underlying(SectionFlag::e_Merge),
      (rawFlags & std::to_underlying(SectionFlag::e_Strings)) == std::to_underlying(SectionFlag::e_Strings),
      (rawFlags & std::to_underlying(SectionFlag::e_Info_link)) == std::to_underlying(SectionFlag::e_Info_link),
      (rawFlags & std::to_underlying(SectionFlag::e_Link_order)) == std::to_underlying(SectionFlag::e_Link_order),
      (rawFlags & std::to_underlying(SectionFlag::e_Os_nonconforming)) ==
          std::to_underlying(SectionFlag::e_Os_nonconforming),
      (rawFlags & std::to_underlying(SectionFlag::e_Group)) == std::to_underlying(SectionFlag::e_Group),
      (rawFlags & std::to_underlying(SectionFlag::e_Tls)) == std::to_underlying(SectionFlag::e_Tls),
      (rawFlags & std::to_underlying(SectionFlag::e_Maskos)) == std::to_underlying(SectionFlag::e_Maskos),
      (rawFlags & std::to_underlying(SectionFlag::e_Maskproc)) == std::to_underlying(SectionFlag::e_Maskproc),
  };
}

}  // namespace

uint32_t SectionHeaderTableEntry::nameIndex() const { return d_nameIndex; }

SectionType SectionHeaderTableEntry::type() const { return d_type; }

SectionHeaderTableEntry::Flags SectionHeaderTableEntry::flags() const { return d_flags; }

uint64_t SectionHeaderTableEntry::addr() const { return d_addr; }

std::byte* SectionHeaderTableEntry::offset() const { return reinterpret_cast<std::byte*>(d_offset); }

uint64_t SectionHeaderTableEntry::size() const { return d_size; }

uint32_t SectionHeaderTableEntry::link() const { return d_link; }

uint32_t SectionHeaderTableEntry::info() const { return d_info; }

uint64_t SectionHeaderTableEntry::addrAlign() const { return d_addrAlign; }

uint64_t SectionHeaderTableEntry::entrySize() const { return d_entrySize; }

SectionHeaderTableEntry::SectionHeaderTableEntry(const RawSectionHeader& rawSectionHeader)
    : d_nameIndex{RawSectionHeaderUtil::nameIndex(rawSectionHeader)},
      d_type{RawSectionHeaderUtil::type(rawSectionHeader)},
      d_flags{decodeSectionFlags(RawSectionHeaderUtil::flags(rawSectionHeader))},
      d_addr{RawSectionHeaderUtil::addr(rawSectionHeader)},
      d_offset{RawSectionHeaderUtil::offset(rawSectionHeader)},
      d_size{RawSectionHeaderUtil::size(rawSectionHeader)},
      d_link{RawSectionHeaderUtil::link(rawSectionHeader)},
      d_info{RawSectionHeaderUtil::info(rawSectionHeader)},
      d_addrAlign{RawSectionHeaderUtil::addrAlign(rawSectionHeader)},
      d_entrySize{RawSectionHeaderUtil::entrySize(rawSectionHeader)} {}

nlohmann::json SectionHeaderTableEntry::json() const {
  using json = nlohmann::json;

  auto toString = [](auto e) {
    std::ostringstream oss;
    oss << e;
    return oss.str();
  };
  auto toVec = [](auto e) {
    std::vector<std::string> properties;
    if (e.d_isWrite) properties.emplace_back("isWrite");
    if (e.d_isAlloc) properties.emplace_back("isAlloc");
    if (e.d_isExecinstr) properties.emplace_back("isExecinstr");
    if (e.d_isMerge) properties.emplace_back("isMerge");
    if (e.d_isStrings) properties.emplace_back("isStrings");
    if (e.d_isInfo_link) properties.emplace_back("isInfo_link");
    if (e.d_isLink_order) properties.emplace_back("isLink_order");
    if (e.d_isOs_nonconforming) properties.emplace_back("isOs_nonconforming");
    if (e.d_isGroup) properties.emplace_back("isGroup");
    if (e.d_isTls) properties.emplace_back("isTls");
    if (e.d_isMaskos) properties.emplace_back("isMaskos");
    if (e.d_isMaskproc) properties.emplace_back("isMaskproc");
    return properties;
  };

  json j;

  j["nameIndex"] = d_nameIndex;
  j["type"] = toString(d_type);
  j["flags"] = toVec(d_flags);
  j["addr"] = d_addr;
  j["offset"] = d_offset;
  j["size"] = d_size;
  j["link"] = d_link;
  j["info"] = d_info;
  j["addrAlign"] = d_addrAlign;
  j["entrySize"] = d_entrySize;
  return j;
}

std::ostream& operator<<(std::ostream& os, const SectionHeaderTableEntry& sectionHeader) {
  os << sectionHeader.json();
  return os;
}

}  // namespace nooblink
