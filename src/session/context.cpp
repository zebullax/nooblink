// -*-C++-*-
//
// File: context.cpp
// Project: nooblink
//

#include <session/context.h>

namespace nooblink {

Context::Impl* Context::instance() {
  static auto instance = std::make_unique<Impl>();
  return instance.get();
}

}  // namespace nooblink