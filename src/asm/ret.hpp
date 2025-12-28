#ifndef C_COMPILER_RET_HPP
#define C_COMPILER_RET_HPP

#include <format>
#include <string>
#include "instruction.hpp"
#include "operand.hpp"
#include "mov.hpp"
#include <ast/ast.hpp>

namespace x86 {
  struct ret : instruction {
    std::string to_string() const {
      return "ret";
    }
  };

  inline std::vector<std::unique_ptr<instruction>> ast_to_asm(const std::unique_ptr<statement_node> &inst) {
    auto src = std::make_unique<operand>(ast_to_operand(inst->exp));
    auto eax = std::make_unique<operand>(reg::eax);

    auto m = std::make_unique<mov>(std::move(src), std::move(eax));
    auto r = std::make_unique<ret>();

    std::vector<std::unique_ptr<instruction> > instructions;
    instructions.emplace_back(std::move(m));
    instructions.emplace_back(std::move(r));

    return instructions;
  }
}

template<>
struct std::formatter<x86::ret> {
  constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

  auto format(const x86::ret &, std::format_context &ctx) const {
    return std::format_to(ctx.out(), "ret");
  }
};

#endif //C_COMPILER_RET_HPP
