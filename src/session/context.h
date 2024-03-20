// -*-C++-*-
//
// File: context.h
// Project: nooblink
//
// Description: This component provides context for the linking session that needs to be maintained during the process

#ifndef NOOBLINK_CONTEXT_H
#define NOOBLINK_CONTEXT_H

// std
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
// nooblink
#include <io/mem_mapped_file.h>
#include <vocabulary/object_file.h>

namespace nooblink {

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

 private:
  // DATA

  std::unordered_map<std::string, ObjectFileCookie> d_objectFiles;
};

}  // namespace nooblink

#endif  // NOOBLINK_CONTEXT_H
