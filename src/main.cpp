// nooblink
#include <elf_format.h>
#include <elf_format_util.h>
// std
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>

int main(int, char **argv) {
  namespace fs = std::filesystem;
  constexpr const size_t k_ElfHeaderLength = NoobLink::Elf64Header::extent;

  fs::path objectFilePath(argv[1]);
  if (!fs::exists(objectFilePath)) {
    std::cerr << "The file " << objectFilePath << " does not exist";
    return EXIT_FAILURE;
  }
  std::ifstream objFile(argv[1], std::ios::binary);

  std::byte raw[k_ElfHeaderLength];
  objFile.read(reinterpret_cast<char*>(raw), k_ElfHeaderLength);

  NoobLink::Elf64Header elf64Header(std::begin(raw), k_ElfHeaderLength);
  NoobLink::ElfFormatUtil::print(std::cout, elf64Header);
  return EXIT_SUCCESS;
}