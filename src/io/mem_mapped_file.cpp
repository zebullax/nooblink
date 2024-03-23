// -*-C++-*-
//
// File: mem_mapped_file.cpp
// Project: nooblink
//

#include <io/mem_mapped_file.h>
// std
#include <stdexcept>
// C
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

namespace nooblink {

MemMappedFile::MemMappedFile(const std::filesystem::path& filename)
    : d_fileDescriptor{}, d_fileSize{}, d_mappedRegionStart{} {
  namespace fs = std::filesystem;
  using namespace std::string_literals;
  if (!fs::exists(filename)) {
    throw std::runtime_error("The file "s + filename.c_str() + " does not exist");
  }
  d_fileSize = fs::file_size(filename);
  d_fileDescriptor = open(filename.c_str(), O_RDONLY);
  if (d_fileDescriptor == -1) {
    throw std::runtime_error("Error opening the file '"s + filename.c_str() + "'");
  }
  d_mappedRegionStart = mmap(nullptr, d_fileSize, PROT_READ, MAP_PRIVATE, d_fileDescriptor, 0);
}

MemMappedFile::~MemMappedFile() {
  munmap(d_mappedRegionStart, d_fileSize);
  close(d_fileDescriptor);
}

int MemMappedFile::fileDescriptor() const { return d_fileDescriptor; }

size_t MemMappedFile::fileSize() const { return d_fileSize; }

void* MemMappedFile::mappedRegionStart() const { return d_mappedRegionStart; }
}  // namespace nooblink
