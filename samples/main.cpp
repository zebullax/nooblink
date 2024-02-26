// -*-C++-*-
//
// File: main.cpp
// Project: nooblink
//
// Description: Describe me
//

// nooblink
#include <cstdlib>
// std
#include "./test.h"

int UndefinedCst;
bool thisFunctionIsntDefined(int i);

int main(int argc, char**) {
  Test t(argc);
  thisFunctionIsntDefined(UndefinedCst);
  return t.i() ? EXIT_SUCCESS : EXIT_FAILURE;
}
