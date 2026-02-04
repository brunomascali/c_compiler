#include <asm/mov.hpp>
#include <format>
#include <string>

#include "instruction.hpp"

namespace x86
{
  std::string mov::emit() const { return std::format("  mov{} {}, {}", to_string(width), src, dst); }

  bool mov::is_legal() const {
    return not (std::holds_alternative<operand::stack>(src.value) and std::holds_alternative<operand::stack>(dst.value));
  }

  std::vector<instruction> mov::legalize() {
    std::vector<instruction> ret;

    ret.emplace_back(mov{src, operand(R10D)});
    ret.emplace_back(mov{operand(R10D), dst});

    return ret;
  }
}

// std::vector<instruction_t> legalize(const mov& m) {
//   if (const auto& [src, dst, _] = m;
//       std::holds_alternative<operand::stack>(src.value) and std::holds_alternative<operand::stack>(dst.value)) {
//     return {mov(src, operand(R10D)), mov(operand(R10D), dst)};
//   }
//
//   return {m};
// }
