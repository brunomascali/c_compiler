#ifndef C_COMPILER_RETURN_HPP
#define C_COMPILER_RETURN_HPP

#include <ir/defs.hpp>

namespace ir {
struct return_ {
  explicit return_(value v) : val(std::move(v)) {}

  value val;
};
}

#endif // C_COMPILER_RETURN_HPP
