// -*-C++-*-
//
// nooblink
#include <session/context.h>
#include <vocabulary/object_file.h>
// spdlog
#include <spdlog/spdlog.h>
// boost
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
// std
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>

namespace po = boost::program_options;
int main(int argc, char** argv) {
  po::options_description cmdLineOptions("Command line options");
  cmdLineOptions.add_options()("object-file,O", po::value<std::vector<std::string>>());
  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, cmdLineOptions), vm);
  po::notify(vm);

  nooblink::Context context;
  if (!vm.count("object-file")) {
    spdlog::info("At least one object file must be specified using -O / --object-file");
    return EXIT_FAILURE;
  }
  for (auto&& objFile : vm["object-file"].as<std::vector<std::string>>()) {
    nooblink::ObjectFile* objectFile = context.loadObjectFile(objFile);
    if (!objectFile || objectFile->currentState() != nooblink::ObjectFile::State::e_Loaded) {
      spdlog::info("Error while loading object file...");
      return EXIT_FAILURE;
    }
    // Will deal later wit logging custom type
    std::ostringstream oss;
    oss << *objectFile << std::endl;
    spdlog::info(oss.str());
  }
  return EXIT_SUCCESS;
}