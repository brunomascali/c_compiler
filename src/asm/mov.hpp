#ifndef C_COMPILER_MOV_HPP
#define C_COMPILER_MOV_HPP

#include <asm/bit_width.hpp>
#include <asm/operand.hpp>

namespace x86
{
  struct mov
  {
    mov(operand s, operand t, const bit_width b = bit_width::dword) : src(std::move(s)), dst(std::move(t)), width(b) {}

    operand src, dst;
    bit_width width;

    [[nodiscard]] std::string emit() const;
  };
}  // namespace x86

#endif  // C_COMPILER_MOV_HPP
