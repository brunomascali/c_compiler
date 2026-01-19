#include <asm/instruction.hpp>
#include <vector>

namespace x86
{
  std::vector<instruction_t> legalize(const mov& m) {
    if (const auto& [src, dst, _] = m;
        std::holds_alternative<operand::stack>(src.value) and std::holds_alternative<operand::stack>(dst.value)) {
      return {mov(src, operand(R10D)), mov(operand(R10D), dst)};
    }

    return {m};
  }
}  // namespace x86
