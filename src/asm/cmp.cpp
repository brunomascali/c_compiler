#include <asm/instruction.hpp>
#include <vector>

namespace x86
{
  std::vector<instruction_t> legalize(const cmp& c) {
    std::vector<instruction_t> instructions;
    const auto &[a, b] = c;

    // Both operands are memory addresses
    if (std::holds_alternative<operand::stack>(a.value) &&
        std::holds_alternative<operand::stack>(b.value)) {
      instructions.emplace_back(mov(a, operand(R10D)));
      instructions.emplace_back(cmp(operand(R10D), b));
      return instructions;
        }

    // Second operand is a constant
    if (std::holds_alternative<operand::immediate>(b.value)) {
      instructions.emplace_back(mov(a, operand(R11D)));
      instructions.emplace_back(cmp(b, operand(R11D)));
      return instructions;
    }

    // Instruction is already legal
    instructions.emplace_back(c);
    return instructions;
  }
}  // namespace x86
