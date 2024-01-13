add_executable(nooblink
        main.cpp
        raw/layout.cpp
        raw/header_constants.cpp
        raw/raw_elf_header_util.cpp
        vocabulary/elf_section.cpp
        raw/raw_section_header_util.cpp
        byte_util.cpp
        vocabulary/elf_header.cpp
        raw/raw_elf_header.cpp
        raw/raw_section_header.cpp
        vocabulary/elf_section_util.cpp
        vocabulary/elf_section_util.h
)
find_package(nlohmann_json 3.11.3 REQUIRED)
target_include_directories(nooblink PUBLIC .)
target_link_libraries(nooblink PRIVATE nlohmann_json::nlohmann_json)