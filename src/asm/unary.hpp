#ifndef C_COMPILER_X86_UNARY_HPP
#define C_COMPILER_X86_UNARY_HPP

#include <utility>

#include "operand.hpp"

namespace x86
{
  struct unary
  {
    ast::unary::op unary_operator;
    operand dst;

    unary(const ast::unary::op op, operand dst) : unary_operator(op), dst(std::move(dst)) {}
  };

  [[nodiscard]] inline std::string to_string(const unary& r) {
    switch (r.unary_operator) {
      case ast::unary::op::not_:
        return std::format("  notl {}", r.dst);
      case ast::unary::op::negate:
        return std::format("  negl {}", r.dst);
    }
  }

}  // namespace x86

#endif  // C_COMPILER_X86_UNARY_HPP
