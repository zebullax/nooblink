// File: byte_util.h
// Project: nooblink
//

#ifndef NOOBLINK_BYTE_UTIL_H
#define NOOBLINK_BYTE_UTIL_H

// nooblink
#include <elf_constants.h>
// std
#include <algorithm>
#include <bit>
#include <span>

namespace NoobLink {

struct ByteUtil {
  ByteUtil() = delete;

  // Convert a multi bytes sequence from the source BytesEndianness to the native endianness. Result is undefined if
  // 'BytesEndianness' is 'e_Unknown'
  template <Endianness BytesEndianness, size_t NbBytes>
  static constexpr std::span<std::byte, NbBytes> toNativeEndian(std::span<std::byte, NbBytes> raw);
};

} // namespace NoobLink

template <NoobLink::Endianness SourceEndianness, size_t NbBytes>
constexpr std::span<std::byte, NbBytes> NoobLink::ByteUtil::toNativeEndian(std::span<std::byte, NbBytes> raw) {
  if constexpr (NbBytes < 2) {
    return raw;
  }

  if constexpr (std::endian::native == std::endian::little &&     // NOLINT
                SourceEndianness == Endianness::e_LittleEndian) { // NOLINT
    return raw;
  }
  if constexpr (std::endian::native == std::endian::big && SourceEndianness == Endianness::e_BigEndian) { // NOLINT
    return raw;                                                                                           // NOLINT
  }

  return std::ranges::reverse(raw);
}

#endif // NOOBLINK_BYTE_UTIL_H
