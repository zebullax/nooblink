// -*-C++-*-
//
// File: raw_elf_header.h
// Project: nooblink
//

#ifndef NOOBLINK_RAW_ELF_HEADER_H
#define NOOBLINK_RAW_ELF_HEADER_H

// nooblink
#include "raw/layout.h"
// std
#include <span>

namespace NoobLink {

// Alias over sequence of bytes covering the Elf header
using RawElfHeader = std::span<std::byte, Layout::FieldOffset::Header::k_SectionNameIndex +
                                              Layout::FieldLength::Header::k_SectionNameIndex>;
}  // namespace NoobLink

#endif  // NOOBLINK_RAW_ELF_HEADER_H
