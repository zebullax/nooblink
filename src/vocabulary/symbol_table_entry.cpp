// -*-C++-*-
//
// File: symbol_table_entry.cpp
// Project: nooblink
//

// nooblink
#include <raw/raw_symbol_table_entry_util.h>
#include <vocabulary/symbol_table_entry.h>
// std
#include <sstream>

namespace nooblink {
namespace {
struct SymbolBTV {
  SymbolBinding binding;
  SymbolType type;
  SymbolVisibility visibility;
};

SymbolBTV extractBTV(const RawSymbolTableEntry& rawEntry) {
  uint8_t info = RawSymbolTableEntryUtil::info(rawEntry);
  uint8_t other = RawSymbolTableEntryUtil::other(rawEntry);
  uint8_t bind = info >> 4;
  uint8_t type = info & 0xf;
  uint8_t visibility = other & 0x3;
  return {SymbolBinding{bind}, SymbolType{type}, SymbolVisibility{visibility}};
}

}  // unnamed namespace

SymbolTableEntry::SymbolTableEntry(const RawSymbolTableEntry& rawEntry)
    : d_nameIndex{RawSymbolTableEntryUtil::nameIndex(rawEntry)},
      d_value{RawSymbolTableEntryUtil::value(rawEntry)},
      d_size{RawSymbolTableEntryUtil::size(rawEntry)},
      d_sectionHeaderIndex{RawSymbolTableEntryUtil::sectionHeaderIndex(rawEntry)},
      d_visibility{},
      d_binding{},
      d_type{} {
  SymbolBTV btv = extractBTV(rawEntry);
  d_visibility = btv.visibility;
  d_binding = btv.binding;
  d_type = btv.type;
}

SymbolBinding SymbolTableEntry::binding() const { return d_binding; }

SymbolVisibility SymbolTableEntry::visibility() const { return d_visibility; }

uint64_t SymbolTableEntry::value() const { return d_value; }

uint64_t SymbolTableEntry::size() const { return d_size; }

uint16_t SymbolTableEntry::sectionHeaderIndex() const { return d_sectionHeaderIndex; }

SymbolType SymbolTableEntry::type() const { return d_type; }

uint32_t SymbolTableEntry::nameIndex() const { return d_nameIndex; }

bool SymbolTableEntry::isUndef() const {
  return d_nameIndex == 0 && d_value == 0 && d_size == 0 && d_sectionHeaderIndex == 0;
}

nlohmann::json SymbolTableEntry::json() const {
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
  nlohmann::json j;
  j["nameIndex"] = d_nameIndex;
  j["value"] = toHex(d_value);
  j["size"] = d_size;
  j["sectionHeaderIndex"] = toString(d_sectionHeaderIndex);
  j["visibility"] = toString(d_visibility);
  j["binding"] = toString(d_binding);
  j["type"] = d_type;
  return j;
}

}  // namespace nooblink
