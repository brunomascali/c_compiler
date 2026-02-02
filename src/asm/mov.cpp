#include <asm/mov.hpp>
#include <format>
#include <string>

namespace x86
{
  std::string mov::emit() const { return std::format("  mov{} {}, {}", to_string(width), src, dst); }
}

// std::vector<instruction_t> legalize(const mov& m) {
//   if (const auto& [src, dst, _] = m;
//       std::holds_alternative<operand::stack>(src.value) and std::holds_alternative<operand::stack>(dst.value)) {
//     return {mov(src, operand(R10D)), mov(operand(R10D), dst)};
//   }
//
//   return {m};
// }
