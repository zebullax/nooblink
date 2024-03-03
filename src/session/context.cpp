// -*-C++-*-
//
// File: context.cpp
// Project: nooblink
//

#include <session/context.h>
// spdlog
#include <spdlog/spdlog.h>

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

  auto [iter, isInserted] =
      d_objectFiles.emplace(path.c_str(), ObjectFileCookie{std::move(memMapGuard), std::move(objFile)});
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

}  // namespace nooblink