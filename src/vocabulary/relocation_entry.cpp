// -*-C++-*-
//
// File: relocation_entry.cpp
// Project: nooblink
//

#include <vocabulary/relocation_entry.h>
// nooblink
#include <utility/conversion.h>
#include <vocabulary/relocation_entry_util.h>

#include "raw/raw_relocation_entry_util.h"

namespace nooblink {
namespace {
auto toHex = [](auto e) {
  std::ostringstream oss;
  oss << "0x" << std::hex << std::setw(sizeof(e)) << std::setfill('0') << e;
  return oss.str();
};
}

RelocationEntry::RelocationEntry(RawRelocationEntry raw)
    : d_offset(RawRelocationEntryUtil::offset(raw)), d_info(RawRelocationEntryUtil::info(raw)) {}

nlohmann::json RelocationEntry::json() const {
  using json = nlohmann::json;
  json j;
  j["offset"] = toHex(d_offset);
  json info;
  info["symbolIndex"] = RelocationEntryUtil::symbolIndex(d_info);
  info["type"] = Conversion::toString(RelocationEntryUtil::type(d_info));
  j["info"] = info;
  return j;
}

RelocationEntryWithAddend::RelocationEntryWithAddend(RawRelocationEntryWithAddend raw)
    : d_offset(RawRelocationEntryUtil::offset(raw)),
      d_info(RawRelocationEntryUtil::info(raw)),
      d_addend(RawRelocationEntryUtil::addend(raw)) {}

nlohmann::json RelocationEntryWithAddend::json() const {
  using json = nlohmann::json;
  json j;
  j["offset"] = toHex(d_offset);
  json info;
  info["symbolIndex"] = RelocationEntryUtil::symbolIndex(d_info);
  info["type"] = Conversion::toString(RelocationEntryUtil::type(d_info));
  j["info"] = info;
  j["addend"] = d_addend;
  return j;
}

}  // namespace nooblink