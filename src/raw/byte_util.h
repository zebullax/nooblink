// -*-C++-*-
//
// File: byte_util.h
// Project: nooblink
//

#ifndef NOOBLINK_BYTE_UTIL_H
#define NOOBLINK_BYTE_UTIL_H

// std
#include <cstddef>
#include <iterator>
#include <span>

struct ByteUtil {
  // CLASS METHODS

  // Helper function to reinterpret the specified 'source' span as a specified 'Target'
  template <class Target, size_t NbBytes>
  static Target convertTo(std::span<std::byte, NbBytes> source);

  // Factory returning a function that offset argument by an optionally specified 'offset', the address parameter is
  // modified and point to the rectified value
  [[maybe_unused]] static decltype(auto) buildOffset(size_t offset = 0) {
    return [offset](std::byte *unadjustedAddress) { return std::advance(unadjustedAddress, offset); };
  }
};

template <class Target, size_t NbBytes>
Target ByteUtil::convertTo(std::span<std::byte, NbBytes> source) {
  static_assert(sizeof(Target) == NbBytes);
  auto *head = reinterpret_cast<Target *>(source.data());
  return *head;
}

#endif  // NOOBLINK_BYTE_UTIL_H
