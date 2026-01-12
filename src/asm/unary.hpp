#ifndef C_COMPILER_X86_UNARY_HPP
#define C_COMPILER_X86_UNARY_HPP

#include <utility>

#include "operand.hpp"

namespace x86 {
  struct unary {
    ast::unary::op unary_operator;
    operand dst;

    unary(const ast::unary::op op, operand dst) : unary_operator(op), dst(std::move(dst)) {
    }

    std::string to_string() {
      switch (unary_operator) {
        case ast::unary::op::complement:
          return std::format("  notl {}", dst);
        case ast::unary::op::negate:
          return std::format("  negl {}", dst);
      }
    }
  };
}

#endif //C_COMPILER_X86_UNARY_HPP
