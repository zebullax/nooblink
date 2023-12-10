//
// Created by aurelien cassagnes on 2023/12/10.
//

#ifndef NOOBLINK_ELFFORMAT_H
#define NOOBLINK_ELFFORMAT_H

#include <property.h>

namespace Nooblink {

template <AddressLength Length> struct ElfHeaderLength;

template <> struct ElfHeaderLength<AddressLength::e_32> {
  enum { Value = 52 };
};

template <> struct ElfHeaderLength<AddressLength::e_64> {
  enum { Value = 64 };
};

} // namespace Nooblink

#endif // NOOBLINK_ELFFORMAT_H
