// -*-C++-*-
//
// nooblink
#include <session/context.h>
#include <vocabulary/object_file.h>
// spdlog
#include <spdlog/spdlog.h>
// std
#include <cstdlib>
#include <sstream>

int main(int, char** argv) {
  nooblink::Context context;
  nooblink::ObjectFile* objectFile = context.loadObjectFile(argv[1]);
  if (!objectFile || objectFile->currentState() != nooblink::ObjectFile::State::e_Loaded) {
    spdlog::info("Error while loading object file...");
    return EXIT_FAILURE;
  }
  // Will deal later wit logging custom type
  std::ostringstream oss;
  oss << *objectFile;
  spdlog::info(oss.str());
  return EXIT_SUCCESS;
}