#ifndef C_COMPILER_MOV_HPP
#define C_COMPILER_MOV_HPP

#include "operand.hpp"

namespace x86
{
  struct mov
  {
    mov(operand s, operand t) : src(std::move(s)), dst(std::move(t)) {}

    operand src;
    operand dst;
  };
}  // namespace x86

#endif  // C_COMPILER_MOV_HPP
