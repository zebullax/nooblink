// -*-C++-*-
//
// nooblink
#include <io/mem_mapped_file.h>
#include <raw/raw_elf_header.h>
#include <vocabulary/elf_header.h>
#include <vocabulary/object_file.h>
// spdlog
#include <spdlog/spdlog.h>
// std
#include <cstdlib>
#include <sstream>

int main(int, char **argv) {
  nooblink::ObjectFile objectFile;
  if (objectFile.load((argv[1])) != nooblink::ObjectFile::State::e_Loaded) {
    spdlog::info("Error while loading object file...");
    return EXIT_FAILURE;
  }
  // Will deal later wit logging custom type
  std::ostringstream oss;
  oss << objectFile;
  spdlog::info(oss.str());
  return EXIT_SUCCESS;
}