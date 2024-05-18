// -*-C++-*-
//
// File: context.cpp
// Project: nooblink
//

#include <session/context.h>
// spdlog
#include <raw/header_constants.h>
#include <spdlog/spdlog.h>
#include <vocabulary/object_file.h>
#include <vocabulary/symbol_table_entry.h>
// std
#include <algorithm>
#include <iterator>
#include <unordered_map>

namespace nooblink {
using namespace std::string_literals;

ObjectFile* Context::loadObjectFile(const std::filesystem::path& path) {
  auto memMapGuard = std::make_unique<MemMappedFile>(path);
  auto begin = reinterpret_cast<std::byte*>(memMapGuard->mappedRegionStart());
  auto objFile = std::make_unique<ObjectFile>();

  if (objFile->load(begin) != ObjectFile::State::e_Loaded) {
    spdlog::error("Error while loading the object file: '"s + path.c_str() + "'");
  } else {
    spdlog::info("Loaded object file: '"s + path.c_str() + "'");
  }
  d_loadSequence.emplace_back(path.c_str());
  auto [iter, isInserted] = d_objectFiles.emplace(path, ObjectFileCookie{std::move(memMapGuard), std::move(objFile)});
  if (!isInserted) {
    spdlog::warn("Object file wasn't persisted, returning stale version");
  }
  return iter->second.d_objectFile.get();
}

ObjectFile* Context::getObjectFile(const std::filesystem::path& path) {
  if (auto iter = d_objectFiles.find(path.c_str()); iter != d_objectFiles.end()) {
    return iter->second.d_objectFile.get();
  }
  return nullptr;
}

std::unordered_map<SectionIndex, std::vector<SymbolTableEntry>> Context::undefinedSymbols(
    const std::filesystem::path& path) const {
  std::unordered_map<SectionIndex, std::vector<SymbolTableEntry>> result;

  if (auto it = d_objectFiles.find(path); it != d_objectFiles.end()) {
    auto symbolsPerSection = it->second.d_objectFile->symbols();
    for (const auto& [sectionIndex, symbols] : symbolsPerSection) {
      std::vector<SymbolTableEntry> undefSymbols;
      std::copy_if(symbols.begin(), symbols.end(), std::back_insert_iterator(undefSymbols),
                   [](const SymbolTableEntry& entry) { return entry.isUndef(); });
      if (!undefSymbols.empty()) {
        result[sectionIndex] = undefSymbols;
      }
    }
  } else {
    spdlog::error("File '"s + path.string() + "' not found in context");
  }
  return result;
}

}  // namespace nooblink