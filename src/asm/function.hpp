#ifndef C_COMPILER_FUNCTION_HPP
#define C_COMPILER_FUNCTION_HPP

#include <memory>
#include <string>
#include <vector>
#include <ranges>

#include "instruction.hpp"

namespace x86 {
  struct function_definition {
    std::string name;
    std::vector<std::unique_ptr<instruction>> instructions;

    [[nodiscard]] std::string to_string() const;
  };

  struct program {
    function_definition func_def;
  };
}

template<>
struct std::formatter<x86::function_definition> {
  constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

  auto format(const x86::function_definition& op, std::format_context &ctx) const {
    auto instructions =
      op.instructions
      | std::views::transform(&x86::instruction::to_string)
      | std::views::join_with('\n')
      | std::ranges::to<std::string>();

    return std::format_to(ctx.out(), "    .globl {}\n{}:\n{}", op.name, op.name, instructions);
  }
};

inline std::string x86::function_definition::to_string() const {
  return std::format("{}", *this);
}


#endif //C_COMPILER_FUNCTION_HPP