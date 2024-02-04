// -*-C++-*-
//
// File: raw_symbol_table_entry_util.cpp
// Project: nooblink
//

#include <raw/raw_symbol_table_entry_util.h>
// nooblink
#include <raw/byte_util.h>

namespace nooblink {

// Macro to cast the specified 'FIELD_NAME' from the symbol table entry to the specified 'TARGET_TYPE'
#define RETURN_CAST_FIELD(TARGET_TYPE, FIELD_NAME)                                                        \
  std::span field = rawSymbolTableEntry.subspan<Layout::FieldOffset::SymbolTableEntry::k_##FIELD_NAME,    \
                                                Layout::FieldLength::SymbolTableEntry::k_##FIELD_NAME>(); \
  return ByteUtil::convertTo<TARGET_TYPE>(field);

uint32_t RawSymbolTableEntryUtil::nameIndex(RawSymbolTableEntry rawSymbolTableEntry){
    RETURN_CAST_FIELD(uint32_t, NameIndex)}

uint64_t RawSymbolTableEntryUtil::value(RawSymbolTableEntry rawSymbolTableEntry){RETURN_CAST_FIELD(uint64_t, Value)}

uint64_t RawSymbolTableEntryUtil::size(RawSymbolTableEntry rawSymbolTableEntry){RETURN_CAST_FIELD(uint64_t, Size)}

uint16_t RawSymbolTableEntryUtil::sectionHeaderIndex(RawSymbolTableEntry rawSymbolTableEntry){
    RETURN_CAST_FIELD(uint16_t, Shndx)}

uint8_t RawSymbolTableEntryUtil::info(RawSymbolTableEntry rawSymbolTableEntry){RETURN_CAST_FIELD(uint8_t, Info)}

uint8_t RawSymbolTableEntryUtil::other(RawSymbolTableEntry rawSymbolTableEntry) {
  RETURN_CAST_FIELD(uint8_t, Other)
}

#undef RETURN_CAST_FIELD

}  // namespace nooblink