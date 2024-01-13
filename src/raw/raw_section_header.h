// -*-C++-*-
//
// File: raw_section_header.h
// Project: nooblink
//

#ifndef NOOBLINK_RAW_SECTION_HEADER_H
#define NOOBLINK_RAW_SECTION_HEADER_H

// nooblink
#include "raw/layout.h"
// std
#include <span>

namespace NoobLink {

// Alias over sequence of bytes covering a section header in the section table
using RawSectionHeader =
    std::span<std::byte, Layout::FieldOffset::Section::k_EntrySize + Layout::FieldLength::Section::k_EntrySize>;

}  // namespace NoobLink
#endif  // NOOBLINK_RAW_SECTION_HEADER_H
