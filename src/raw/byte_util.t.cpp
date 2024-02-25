// -*-C++-*-
//
// File: byte_util.cpp
// Project: nooblink
//

#include <raw/byte_util.h>
// std
#include <span>
// gtest
#include <gtest/gtest.h>

namespace nooblink {

TEST(ByteUtil, ConvertShouldReturnExpectedStuff) {
  std::byte raw[4] = {std::byte(0x01), std::byte(0x02), std::byte(0x03), std::byte(0x04)};
  std::span<std::byte, 4> source(raw, raw + 4);
  EXPECT_EQ(0x04030201, ByteUtil::convertTo<uint32_t>(source));
}

}  // namespace nooblink
