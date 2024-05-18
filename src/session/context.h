// -*-C++-*-
//
// File: context.h
// Project: nooblink
//
// Description: This component provides context for the linking session that needs to be maintained throughout the
// process

#ifndef NOOBLINK_CONTEXT_H
#define NOOBLINK_CONTEXT_H

// std
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
// nooblink
#include <io/mem_mapped_file.h>
#include <raw/header_constants.h>
#include <vocabulary/object_file.h>
#include <vocabulary/section_header.h>

namespace nooblink {

struct PathHash {
  std::size_t operator()(const std::filesystem::path& p) const noexcept { return std::hash<std::string>{}(p.string()); }
};

struct PathCmp {
  bool operator()(const std::filesystem::path& lhs, const std::filesystem::path& rhs) const noexcept {
    return lhs.string() < rhs.string();
  }
};

class Context {
 public:
  // TYPES

  struct ObjectFileCookie {
    std::unique_ptr<MemMappedFile> d_backingFile;
    std::unique_ptr<ObjectFile> d_objectFile;
  };

  // CREATORS

  Context() = default;

  // MANIPULATORS

  // Load and return an object file from the specified 'path'
  ObjectFile* loadObjectFile(const std::filesystem::path& path);

  // Return the object file that was previously loaded, using the specified 'path' as identifier
  ObjectFile* getObjectFile(const std::filesystem::path& path);

  // Return for each section index, symbols that are undefined in the object file loaded at specified
  // 'path'
  std::unordered_map<SectionIndex, std::vector<SymbolTableEntry>> undefinedSymbols(
      const std::filesystem::path& path) const;

 private:
  // DATA

  std::unordered_map<std::filesystem::path, ObjectFileCookie, PathHash, PathCmp> d_objectFiles;
  std::vector<std::string> d_loadSequence;
};

}  // namespace nooblink

#endif  // NOOBLINK_CONTEXT_H
