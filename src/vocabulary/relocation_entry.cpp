// -*-C++-*-
//
// File: relocation_entry.cpp
// Project: nooblink
//

#include <vocabulary/relocation_entry.h>
// nooblink
#include <vocabulary/relocation_entry_util.h>

namespace nooblink {

nlohmann::json RelocationEntry::json() const {
  using json = nlohmann::json;
  json j;
  j["offset"] = d_offset;
  json info;
  info["symbolIndex"] = RelocationEntryUtil::symbolIndex(d_info);
  info["type"] = RelocationEntryUtil::type(d_info);
  j["info"] = info;
  return j;
}

nlohmann::json RelocationEntryWithAddend::json() const {
  using json = nlohmann::json;
  json j;
  j["offset"] = d_offset;
  json info;
  info["symbolIndex"] = RelocationEntryUtil::symbolIndex(d_info);
  info["type"] = RelocationEntryUtil::type(d_info);
  j["info"] = info;
  j["addend"] = d_addend;
  return j;
}

}  // namespace nooblink