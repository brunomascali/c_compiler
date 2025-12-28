#ifndef C_COMPILER_OPERAND_HPP
#define C_COMPILER_OPERAND_HPP

#include <format>
#include <string>
#include <variant>

#include "ast.hpp"

namespace x86 {
  enum class reg { eax };

  // operand ::= imm(int) | register
  struct operand {
    std::variant<int, reg> value;

    explicit operand(int n) : value(n) {}
    explicit operand(reg r) : value(r) {}

    [[nodiscard]] std::string to_string() const;
  };
}

inline x86::operand ast_to_operand(const ast::expr& expr) {
  return std::visit([] (const auto& expr) -> x86::operand {
    using T = std::decay_t<decltype(expr)>;

    if constexpr (std::is_same_v<T, int>) {
      return x86::operand(expr);
    }
    else
      static_assert(false, "non-exhaustive visitor!");
  }, expr);
}

// template<>
// struct std::formatter<x86::operand> {
//   constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }
//
//   auto format(const x86::operand& op, std::format_context &ctx) const {
//     return std::visit([&](auto&& arg) {
//         using T = std::decay_t<decltype(arg)>;
//         if constexpr (std::is_same_v<T, std::string>) {
//             return std::format_to(ctx.out(), "{}", arg);
//         } else if constexpr (std::is_same_v<T, x86::reg>) {
//             return std::format_to(ctx.out(), "eax");
//         }
//     }, op.value);
//   }
// };
//
// inline std::string x86::operand::to_string() const {
//   return std::format("{}", *this);
// }

#endif //C_COMPILER_OPERAND_HPP
