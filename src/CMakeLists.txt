add_executable(nooblink
        main.cpp
        format/raw_description.cpp
        format/header_constants.cpp
        format/raw_header_util.cpp
        format/elf_section.cpp
        format/raw_section_util.cpp
        byte_util.cpp
        format/elf_header.cpp
)
find_package(nlohmann_json 3.11.3 REQUIRED)
target_include_directories(nooblink PUBLIC .)
target_link_libraries(nooblink PRIVATE nlohmann_json::nlohmann_json)