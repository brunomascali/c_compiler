#ifndef C_COMPILER_CMP_HPP
#define C_COMPILER_CMP_HPP

#include "operand.hpp"

namespace x86 {
struct cmp {
  cmp(operand a, operand b) : a(a), b(b) {}

  operand a, b;
};
} // namespace x86

#endif // C_COMPILER_CMP_HPP
