add_executable(nooblink main.cpp elf_format.cpp elf_format_util.cpp elf_constants.cpp byte_util.cpp)
find_package(nlohmann_json 3.11.3 REQUIRED)
target_include_directories(nooblink PUBLIC .)
target_link_libraries(nooblink PRIVATE nlohmann_json::nlohmann_json)