// -*-C++-*-
//
// File: context.h
// Project: nooblink
//
// Description: This component provides context for the linking session that needs to be maintained during the process
// FIXME Vocab types may need this but then this component likely will also use some vocab types, so there is likely
// FIXME some issue...

#ifndef NOOBLINK_CONTEXT_H
#define NOOBLINK_CONTEXT_H

// std
#include <memory>

namespace nooblink {

class Context {
 private:
  struct Impl {
    size_t offset;
  };

 public:
  Context() = delete;
  static Impl* instance();
};

}  // namespace nooblink

#endif  // NOOBLINK_CONTEXT_H
