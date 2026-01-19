#ifndef C_COMPILER_CMP_HPP
#define C_COMPILER_CMP_HPP

#include <utility>

#include "operand.hpp"

namespace x86
{
  struct cmp
  {
    cmp(operand a, operand b) : a(std::move(a)), b(std::move(b)) {}

    operand a, b;
  };
  [[nodiscard]] inline std::string to_string(const cmp& c) { return std::format("  cmpl {}, {}", c.a, c.b); }

}  // namespace x86

#endif  // C_COMPILER_CMP_HPP
