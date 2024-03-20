// -*-C++-*-
//
// File: raw_relocation_entry.h
// Project: nooblink
//
// Description: This component provides alias over a sequence of bytes covering a raw relocation entry
//

#ifndef NOOBLINK_RAW_RELOCATION_ENTRY_H
#define NOOBLINK_RAW_RELOCATION_ENTRY_H

// nooblink
#include <raw/layout.h>
// std
#include <span>

namespace nooblink {

// Alias over sequence of bytes covering a relocation entry
using RawRelocationEntry =
    std::span<std::byte, Layout::FieldOffset::RelocationEntry::k_Info + Layout::FieldLength::RelocationEntry::k_Info>;

// Alias over sequence of bytes covering a relocation entry with addend
using RawRelocationEntryWithAddend = std::span<std::byte, Layout::FieldOffset::RelocationEntryWithAddend::k_Info +
                                                              Layout::FieldLength::RelocationEntryWithAddend::k_Info>;

}  // namespace nooblink

#endif  // NOOBLINK_RAW_RELOCATION_ENTRY_H
