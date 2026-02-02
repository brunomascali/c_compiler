#ifndef C_COMPILER_X86_BINARY_H
#define C_COMPILER_X86_BINARY_H

#include <asm/operand.hpp>
#include <string>

namespace x86
{
  class instruction;

  struct binary
  {
    binary(const ast::binary::op op, operand a, operand b) :
        binary_operator(op), arg1(std::move(a)), arg2(std::move(b)) {}

    [[nodiscard]] std::string emit() const;

    ast::binary::op binary_operator;
    operand arg1, arg2;
  };

  // [[nodiscard]] std::string to_string(const binary& b);
}  // namespace x86
#endif
