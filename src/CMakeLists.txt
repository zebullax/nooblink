add_executable(nooblink
        main.cpp
        raw/layout.cpp
        raw/header_constants.cpp
        raw/raw_elf_header_util.cpp
        raw/raw_section_header_util.cpp
        raw/raw_elf_header.cpp
        raw/raw_section_header.cpp
        raw/byte_util.cpp
        vocabulary/section_header_table_entry.cpp
        vocabulary/elf_header.cpp
        vocabulary/object_file.cpp
        io/mem_mapped_file.cpp
        session/context.cpp
        vocabulary/symbol_table_entry.cpp
        raw/raw_symbol_table_entry.cpp
        raw/raw_symbol_table_entry_util.cpp
        utility/conversion.cpp
)
find_package(nlohmann_json 3.11.3 REQUIRED)
find_package(spdlog REQUIRED)
target_include_directories(nooblink PUBLIC .)
target_link_libraries(nooblink PRIVATE nlohmann_json::nlohmann_json spdlog::spdlog)