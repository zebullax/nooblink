// -*-C++-*-
//
// File: raw_relocation_entry_util.h
// Project: nooblink
//
// Description: This component provides utility to deal with the raw representation of a relocation entry
//

#ifndef NOOBLINK_RAW_RELOCATION_ENTRY_UTIL_H
#define NOOBLINK_RAW_RELOCATION_ENTRY_UTIL_H

// nooblink
#include <raw/byte_util.h>
#include <raw/layout.h>
#include <raw/raw_relocation_entry.h>
// std
#include <concepts>
#include <cstdint>

namespace nooblink {

struct RawRelocationEntryUtil {
  RawRelocationEntryUtil() = delete;

  // Extract the offset field from a specified raw 'relocation' that is either a RawRelocationEntry or a
  // RawRelocationEntryWithAddend
  template <class T>
  requires std::same_as<RawRelocationEntry, std::remove_cvref_t<T>> ||
           std::same_as<RawRelocationEntryWithAddend, std::remove_cvref_t<T>>
  static uint64_t offset(T&& relocation);

  // Extract the info field from a specified raw 'relocation' that is either a RawRelocationEntry or a
  // RawRelocationEntryWithAddend
  template <class T>
  requires std::same_as<RawRelocationEntry, std::remove_cvref_t<T>> ||
           std::same_as<RawRelocationEntryWithAddend, std::remove_cvref_t<T>>
  static uint64_t info(T&& relocation);

  // Extract the addend field from the specified raw 'relocation'
  static uint64_t addend(RawRelocationEntryWithAddend relocation);
};

// =======================================================================
//                          INLINE DEFINITIONS
// =======================================================================

template <class T>
requires std::same_as<RawRelocationEntry, std::remove_cvref_t<T>> ||
         std::same_as<RawRelocationEntryWithAddend, std::remove_cvref_t<T>>
uint64_t RawRelocationEntryUtil::offset(T&& relocation) {
  std::span field = relocation.template subspan<Layout::FieldOffset::RelocationEntry::k_Offset,
                                                Layout::FieldLength::RelocationEntry::k_Offset>();
  return ByteUtil::convertTo<uint64_t>(field);
}

template <class T>
requires std::same_as<RawRelocationEntry, std::remove_cvref_t<T>> ||
         std::same_as<RawRelocationEntryWithAddend, std::remove_cvref_t<T>>
uint64_t RawRelocationEntryUtil::info(T&& relocation) {
  auto field = relocation.template subspan<Layout::FieldOffset::RelocationEntry::k_Info,
                                           Layout::FieldLength::RelocationEntry::k_Info>();
  return ByteUtil::convertTo<uint64_t>(field);
}

}  // namespace nooblink

#endif  // NOOBLINK_RAW_RELOCATION_ENTRY_UTIL_H
