TARGET_SOURCES(nooblink
        PUBLIC layout.cpp
        PUBLIC header_constants.cpp
        PUBLIC raw_elf_header_util.cpp
        PUBLIC raw_section_header_util.cpp
        PUBLIC raw_elf_header.cpp
        PUBLIC raw_section_header.cpp
        PUBLIC byte_util.cpp
        PUBLIC raw_symbol_table_entry.cpp
        PUBLIC raw_symbol_table_entry_util.cpp
)

TARGET_SOURCES(nooblink_test
        PRIVATE byte_util.t.cpp)