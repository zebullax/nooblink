// -*-C++-*-
//
// File: mem_mapped_file.h
// Project: nooblink
//
// Description: This component provides a RAII wrapper around a memory mapped file
//

#ifndef NOOBLINK_MEM_MAPPED_FILE_H
#define NOOBLINK_MEM_MAPPED_FILE_H

// std
#include <cstdlib>
#include <filesystem>
#include <string>
// C
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

namespace nooblink {

class MemMappedFile {
 private:
  // DATA
  int d_fileDescriptor;
  size_t d_fileSize;
  void *d_mappedRegionStart;

 public:
  // CREATORS

  // Create this object mapping the specified 'filename' to memory. The behavior is undefined if the file does not exist
  explicit MemMappedFile(const std::filesystem::path &filename);

  ~MemMappedFile();

  // ACCESSORS

  [[nodiscard]] int fileDescriptor() const;

  [[nodiscard]] size_t fileSize() const;

  [[nodiscard]] void *mappedRegionStart() const;
};
}  // namespace nooblink

#endif  // NOOBLINK_MEM_MAPPED_FILE_H
