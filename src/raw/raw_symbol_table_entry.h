// -*-C++-*-
//
// File: raw_symbol_table_entry.h
// Project: nooblink
//
// Description: This component provides an alias over a sequence of bytes covering a symbol table entry
//

#ifndef NOOBLINK_RAW_SYMBOL_TABLE_ENTRY_H
#define NOOBLINK_RAW_SYMBOL_TABLE_ENTRY_H

// std
#include <span>
// nooblink
#include <raw/layout.h>

namespace nooblink {

// Alias over sequence of bytes covering an entry in the symbol table
using RawSymbolTableEntry =
    std::span<std::byte, Layout::FieldOffset::SymbolTableEntry::k_Size + Layout::FieldLength::SymbolTableEntry::k_Size>;

}  // namespace nooblink

#endif  // NOOBLINK_RAW_SYMBOL_TABLE_ENTRY_H
