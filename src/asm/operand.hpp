#ifndef C_COMPILER_OPERAND_HPP
#define C_COMPILER_OPERAND_HPP
#include <format>
#include <memory>
#include <string>
#include <variant>

#include <ast/ast.hpp>

namespace x86 {
  enum class reg { eax };

  // operand ::= imm(int) | register
  struct operand {
    std::variant<std::string, reg> value;

    explicit operand(std::string s) : value(std::move(s)) {}
    explicit operand(reg r) : value(r) {}

    std::string to_string() const;
  };
}

inline x86::operand ast_to_operand(const std::unique_ptr<expr_node>& inst) {
  return {x86::operand(inst->value)};
}

template<>
struct std::formatter<x86::operand> {
  constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

  auto format(const x86::operand& op, std::format_context &ctx) const {
    return std::visit([&](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, std::string>) {
            return std::format_to(ctx.out(), "{}", arg);
        } else if constexpr (std::is_same_v<T, x86::reg>) {
            return std::format_to(ctx.out(), "eax");
        }
    }, op.value);
  }
};

inline std::string x86::operand::to_string() const {
  return std::format("{}", *this);
}

#endif //C_COMPILER_OPERAND_HPP
