#ifndef C_COMPILER_MOV_HPP
#define C_COMPILER_MOV_HPP

#include <asm/bit_width.hpp>

#include "operand.hpp"

namespace x86
{
  struct mov
  {
    mov(operand s, operand t, const bit_width b = bit_width::dword) : src(std::move(s)), dst(std::move(t)), width(b) {}

    operand src;
    operand dst;
    bit_width width;
  };

  [[nodiscard]] inline std::string to_string(const mov& m) {
    return std::format("  mov{} {}, {}", to_string(m.width), m.src, m.dst);
  }
}  // namespace x86

#endif  // C_COMPILER_MOV_HPP
