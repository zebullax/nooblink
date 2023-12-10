// File: address.h
// Project: nooblink

#ifndef NOOBLINK_ADDRESS_H
#define NOOBLINK_ADDRESS_H

// std
#include <cstdint>

namespace Nooblink {

enum class AddressingType { e_32, e_64 };

template <AddressingType AT> struct AddressSize;

template <> struct AddressSize<AddressingType::e_32> {
  static constexpr uint8_t k_Value = 4;
};

template <> struct AddressSize<AddressingType::e_64> {
  static constexpr uint8_t k_Value = 8;
};

} // namespace Nooblink

#endif // NOOBLINK_ADDRESS_H
