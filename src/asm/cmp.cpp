#include <vector>
#include <asm/cmp.hpp>
#include <asm/mov.hpp>

namespace x86
{
  std::string cmp::emit() const {
    {
      return std::format("  cmp{} {}, {}", to_string(width), a, b);
    }
  }

  // std::vector<instruction> cmp::legalize() {
  //   std::vector<instruction> instructions;
  //
  //   // Both operands are memory addresses
  //   if (std::holds_alternative<operand::stack>(a.value) && std::holds_alternative<operand::stack>(b.value)) {
  //     instructions.emplace_back(mov(a, operand(R10D)));
  //     instructions.emplace_back(cmp(operand(R10D), b, width));
  //     return instructions;
  //   }
  //
  //   // Second operand is a constant
  //   if (std::holds_alternative<operand::immediate>(b.value)) {
  //     instructions.emplace_back(mov(b, operand(R11D)));
  //     instructions.emplace_back(cmp(a, operand(R11D), width));
  //     return instructions;
  //   }
  //
  //   // Instruction is already legal
  //   instructions.emplace_back(cmp(a, b, width));
  //   return instructions;
  // }
}  // namespace x86
