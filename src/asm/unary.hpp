#ifndef C_COMPILER_X86_UNARY_HPP
#define C_COMPILER_X86_UNARY_HPP

#include "operand.hpp"

namespace x86
{
  struct unary
  {
    unary(const ast::unary::op op, operand dst) : unary_operator(op), dst(std::move(dst)) {}

    [[nodiscard]] std::string emit() const;

    ast::unary::op unary_operator;
    operand dst;
  };
}  // namespace x86

#endif  // C_COMPILER_X86_UNARY_HPP
