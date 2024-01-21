// -*-C++-*-
//
// File: mem_mapped_file.cpp
// Project: nooblink
//
// Description: Describe me
//

// nooblink
#include <io/mem_mapped_file.h>
// std
#include <filesystem>
#include <stdexcept>

namespace nooblink {

MemMappedFile::MemMappedFile(const std::string &filename) : d_fileDescriptor{}, d_fileSize{}, d_mappedRegionStart{} {
  namespace fs = std::filesystem;
  using namespace std::string_literals;
  fs::path objectFilePath(filename);
  if (!fs::exists(objectFilePath)) {
    throw std::runtime_error("The file "s + filename + " does not exist");
  }
  d_fileSize = fs::file_size(objectFilePath);
  d_fileDescriptor = open(filename.c_str(), O_RDONLY);
  if (d_fileDescriptor == -1) {
    throw std::runtime_error("Error opening the file '"s + filename + "'");
  }
  d_mappedRegionStart = mmap(nullptr, d_fileSize, PROT_READ, MAP_PRIVATE, d_fileDescriptor, 0);
}

MemMappedFile::~MemMappedFile() {
  munmap(d_mappedRegionStart, d_fileSize);
  close(d_fileDescriptor);
}

int MemMappedFile::fileDescriptor() const { return d_fileDescriptor; }

size_t MemMappedFile::fileSize() const { return d_fileSize; }

void *MemMappedFile::mappedRegionStart() const { return d_mappedRegionStart; }
}  // namespace nooblink
