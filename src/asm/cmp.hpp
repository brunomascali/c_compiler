#ifndef C_COMPILER_CMP_HPP
#define C_COMPILER_CMP_HPP

#include <utility>

#include "operand.hpp"
#include <asm/bit_width.hpp>

namespace x86
{
  struct cmp
  {
    cmp(operand a, operand b, const bit_width bw) : a(std::move(a)), b(std::move(b)), width(bw) {}

    operand a, b;
    bit_width width;
  };
  [[nodiscard]] inline std::string to_string(const cmp& c) { return std::format("  cmp{} {}, {}", to_string(c.width), c.a, c.b); }

}  // namespace x86

#endif  // C_COMPILER_CMP_HPP
