// -*-C++-*-
//
// File: byte_util.h
// Project: nooblink
//

#ifndef NOOBLINK_BYTE_UTIL_H
#define NOOBLINK_BYTE_UTIL_H

// std
#include <cstddef>
#include <span>

struct ByteUtil {
  // CLASS METHODS

  // Helper function to reinterpret the specified 'source' span as a specified 'Target'
  template <class Target, size_t NbBytes>
  static Target convertTo(std::span<std::byte, NbBytes> source);
};

template <class Target, size_t NbBytes>
Target ByteUtil::convertTo(std::span<std::byte, NbBytes> source) {
  static_assert(sizeof(Target) == NbBytes);
  auto *head = reinterpret_cast<Target *>(source.data());
  return *head;
}

#endif  // NOOBLINK_BYTE_UTIL_H
