#include <asm/binary.hpp>

#include "instruction.hpp"

namespace x86
{
  std::vector<instruction_t> legalize(const binary& c) {
    std::vector<instruction_t> instructions;
    const auto &[op, arg1, arg2] = c;

    // Both operands are memory addresses
    if (std::holds_alternative<operand::stack>(arg1.value) &&
        std::holds_alternative<operand::stack>(arg2.value)) {
      instructions.emplace_back(mov(arg1, operand(R10D)));
      instructions.emplace_back(cmp(operand(R10D), arg2));
      return instructions;
        }

    // Second operand is a constant
    if (std::holds_alternative<operand::immediate>(arg2.value)) {
      instructions.emplace_back(mov(arg1, operand(R11D)));
      instructions.emplace_back(cmp(arg2, operand(R11D)));
      return instructions;
    }

    // Instruction is already legal
    instructions.emplace_back(c);
    return instructions;
  }


  std::string to_string(const binary& b) {
    switch (b.binary_operator) {
      case ast::binary::op::add:
        return std::format("  addl {}, {}", b.arg1, b.arg2);
      case ast::binary::op::sub:
        return std::format("  subl {}, {}", b.arg1, b.arg2);
      case ast::binary::op::mul:
        return std::format("  imull {}, {}", b.arg1, b.arg2);
      case ast::binary::op::div:
      case ast::binary::op::rem:
        return std::format("  idivl {}", b.arg2);
    }

    return "BINARY NOT IMPLEMENTED";
  }
}
