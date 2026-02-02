#include <asm/binary.hpp>
#include <utility>

namespace x86
{
  // std::vector<instruction_t> legalize(const binary& c) {
  //   std::vector<instruction_t> instructions;
  //   const auto &[op, arg1, arg2] = c;
  //
  //   // Both operands are memory addresses
  //   if (std::holds_alternative<operand::stack>(arg1.value) &&
  //       std::holds_alternative<operand::stack>(arg2.value)) {
  //     instructions.emplace_back(mov(arg1, operand(R10D)));
  //     instructions.emplace_back(cmp(operand(R10D), arg2, bit_width::byte));
  //     return instructions;
  //       }
  //
  //   // Second operand is a constant
  //   if (std::holds_alternative<operand::immediate>(arg2.value)) {
  //     instructions.emplace_back(mov(arg1, operand(R11D)));
  //     instructions.emplace_back(cmp(arg2, operand(R11D), bit_width::byte));
  //     return instructions;
  //   }
  //
  //   // Instruction is already legal
  //   instructions.emplace_back(c);
  //   return instructions;
  // }


  std::string binary::emit() const {
    switch (binary_operator) {
      case ast::binary::op::add:
        return std::format("  addl {}, {}", arg1, arg2);
      case ast::binary::op::sub:
        return std::format("  subl {}, {}", arg1, arg2);
      case ast::binary::op::mul:
        return std::format("  imull {}, {}", arg1, arg2);
      case ast::binary::op::div:
      case ast::binary::op::rem:
        return std::format("  idivl {}", arg2);
      default:
        std::unreachable();
    }

    return "BINARY NOT IMPLEMENTED";
  }
}  // namespace x86
