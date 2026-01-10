#ifndef C_COMPILER_BINARY_H
#define C_COMPILER_BINARY_H

#include <utility>

#include "operand.hpp"

namespace x86
{
  struct binary
  {
    ast::binary::op binary_operator;
    operand arg1, arg2;

    binary(const ast::binary::op op, operand a, operand b) : binary_operator(op), arg1(std::move(a)),
                                                             arg2(std::move(b))
    {
    }

    std::string to_string()
    {
      switch (binary_operator)
      {
      case ast::binary::op::add:
        return std::format("  addl {}, {}", arg1, arg2);
      case ast::binary::op::sub:
        return std::format("  subl {}, {}", arg1, arg2);
      case ast::binary::op::mul:
        return std::format("  imull {}, {}", arg1, arg2);
      case ast::binary::op::div:
      case ast::binary::op::rem:
        return std::format("  idivl {}", arg2);
      }

      return "BINARY NOT IMPLEMENTED";
    }
  };
}

#endif //C_COMPILER_BINARY_H
