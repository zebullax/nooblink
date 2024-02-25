// -*-C++-*-
//
// File: conversion.h
// Project: nooblink
//
// Description: This component provides general purpose utilities related to conversion
//

#ifndef NOOBLINK_CONVERSION_H
#define NOOBLINK_CONVERSION_H

// std
#include <sstream>
#include <string>

namespace nooblink {

class Conversion {
 public:
  // CREATORS

  Conversion() = delete;

  // CLASS METHODS

  // Return a string representation of the specified 'raw'
  static std::string toString(auto raw);
};

// =======================================================================
//                          INLINE DEFINITIONS
// =======================================================================

std::string Conversion::toString(auto raw) {
  std::ostringstream oss;
  oss << raw;
  return oss.str();
}

}  // namespace nooblink
#endif  // NOOBLINK_CONVERSION_H
