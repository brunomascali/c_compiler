#ifndef C_COMPILER_FUNCTION_HPP
#define C_COMPILER_FUNCTION_HPP

#include <memory>
#include <string>

namespace x86 {
  struct start_function {
    std::string name;

    explicit start_function(std::string n) : name(std::move(n)) {}

    [[nodiscard]] std::string to_string() const;
  };
}

// template<>
// struct std::formatter<x86::function_definition> {
//   constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }
//
//   auto format(const x86::function_definition& op, std::format_context &ctx) const {
//     auto instructions =
//       op.instructions
//       | std::views::transform(&x86::instruction::to_string)
//       | std::views::join_with('\n')
//       | std::ranges::to<std::string>();
//
//     return std::format_to(ctx.out(), "    .globl {}\n{}:\n{}", op.name, op.name, instructions);
//   }
// };
//
// inline std::string x86::function_definition::to_string() const {
//   return std::format("{}", *this);
// }


#endif //C_COMPILER_FUNCTION_HPP