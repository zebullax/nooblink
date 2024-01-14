// -*-C++-*-
//
// nooblink
#include "raw/raw_elf_header.h"
#include "vocabulary/elf_header.h"
#include "vocabulary/elf_header_util.h"
// std
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>
// C
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

namespace {
// RAII class dealing with memory mapping a file
class MMapFile {
 private:
  int d_fileDescriptor;
  size_t d_fileSize;
  void *d_mappedRegionStart;

 public:
  // Create this object mapping the specified 'filename' to memory. The behavior is undefined if the file does not exist
  explicit MMapFile(const std::string &filename) : d_fileDescriptor{}, d_fileSize{}, d_mappedRegionStart{} {
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

  ~MMapFile() {
    munmap(d_mappedRegionStart, d_fileSize);
    close(d_fileDescriptor);
  }

  int getFileDescriptor() const { return d_fileDescriptor; }

  size_t getFileSize() const { return d_fileSize; }

  void *getMappedRegionStart() const { return d_mappedRegionStart; }
};
}  // namespace

int main(int, char **argv) {
  namespace fs = std::filesystem;
  constexpr const size_t k_ElfHeaderLength = NoobLink::RawElfHeader::extent;

  MMapFile file(argv[1]);
  std::byte *objFileStart = reinterpret_cast<std::byte *>(file.getMappedRegionStart());

  // Demo starts here
  NoobLink::RawElfHeader rawElfHeader(objFileStart, k_ElfHeaderLength);
  NoobLink::ElfHeader elfHeader(rawElfHeader);
  std::cout << "=== Elf header ===" << '\n' << elfHeader << std::endl;
  for (auto &&sectionHeader : NoobLink::ElfHeaderUtil::extractSections(elfHeader, objFileStart)) {
    std::cout << "=== Section table header ===" << '\n' << sectionHeader << std::endl;
  }

  return EXIT_SUCCESS;
}