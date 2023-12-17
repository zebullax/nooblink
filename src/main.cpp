// std
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>

int main(int argc, char **argv) {
  namespace fs = std::filesystem;

  fs::path objectFilePath(argv[1]);
  if (!fs::exists(objectFilePath)) {
    std::cerr << "The file " << objectFilePath << " does not exist";
    return EXIT_FAILURE;
  }
  std::ifstream objFile(argv[1]);
  return EXIT_SUCCESS;
}