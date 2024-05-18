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
#include <filesystem>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

namespace po = boost::program_options;
using namespace std::string_literals;

int main(int argc, char** argv) {
  po::options_description cmdLineOptions("Command line options");
  cmdLineOptions.add_options()("object-file,O", po::value<std::vector<std::string>>(), "Object files to link together")(
      "verbose,V", "Print debug level messages");
  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, cmdLineOptions), vm);
  po::notify(vm);

  if (vm.count("verbose")) {
    spdlog::set_level(spdlog::level::debug);
  }
  if (!vm.count("object-file")) {
    spdlog::error("At least one object file must be specified using -O / --object-file");
    return EXIT_FAILURE;
  }

  nooblink::Context context;
  std::vector<std::string> objectFiles = vm["object-file"].as<std::vector<std::string>>();
  auto filePaths =
      objectFiles | std::views::transform([](const std::string& name) { return std::filesystem::absolute(name); });
  for (const auto& filePath : filePaths) {
    spdlog::debug("Loading object file "s + filePath.string());
    nooblink::ObjectFile* objectFile = context.loadObjectFile(filePath);
    if (!objectFile || objectFile->currentState() != nooblink::ObjectFile::State::e_Loaded) {
      spdlog::error("Error while loading object file...");
      return EXIT_FAILURE;
    }
    // Will deal later with logging custom type
    std::ostringstream oss;
    oss << *objectFile << std::endl;
    spdlog::info(oss.str());
  }

  for (auto&& filePath : filePaths) {
    auto undefinedSymbols = context.undefinedSymbols(filePath);
    if (undefinedSymbols.empty()) {
      spdlog::debug("No undefined symbols found in '"s + filePath.string() + "'");
    } else {
      spdlog::info("Undefined symbols found in '"s + filePath.string() + "'");
      for (const auto& [index, symbols] : undefinedSymbols) {
        // O(#file) * O(#section) * O(#undef)...
        for (const auto& symbol : symbols) {
          spdlog::debug(symbol.json());
        }
      }
    }
  }
  return EXIT_SUCCESS;
}