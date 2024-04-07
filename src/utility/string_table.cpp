// -*-C++-*-
//
// File: string_table.cpp
// Project: nooblink
//

#include <utility/string_table.h>

namespace nooblink {

void StringTable::storeSection(size_t sectionIndex, std::string_view content) {
  d_sectionStrings[sectionIndex] = content;
}

std::string_view StringTable::get(size_t sectionIndex, uint64_t offset) const {
  if (auto it = d_sectionStrings.find(sectionIndex); it != d_sectionStrings.end()) {
    std::string_view content = it->second;
    auto nextNull = content.find_first_of('\0', offset);
    return content.substr(offset, nextNull - offset);
  }
  static std::string_view k_notFound;
  return k_notFound;
}

}  // namespace nooblink