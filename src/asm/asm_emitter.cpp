#include "asm_emitter.hpp"

std::vector<asm_emitter::instruction> asm_emitter::emit(const ast::program &program) {
  for (const auto &func: program.statements) {
    gen_from_function_ast_node(func);
    for (const auto &stmt: func.body) {
      visit_statement(stmt);
    }
  }

  return m_instructions;
}

void asm_emitter::visit_statement(const ast::statement &statement) {
  std::visit([this](auto &&arg) {
    using T = std::decay_t<decltype(arg)>;

    if constexpr (std::is_same_v<T, ast::return_stmt>)
      asm_from_return_ast_node(arg);
    else
      static_assert(false, "non-exhaustive visitor!");
  }, statement);
}

void asm_emitter::asm_from_return_ast_node(const ast::return_stmt &statement) {
  using namespace x86;
  const auto src = ast_to_operand(statement.expression);
  const auto dst = operand(EAX);
  m_instructions.emplace_back(mov(src, dst));
  m_instructions.emplace_back(ret{});
}

void asm_emitter::gen_from_function_ast_node(const ast::function &function) {
  m_instructions.emplace_back(x86::start_function(function.name));
}

std::string instructions_visitor(asm_emitter::instruction instruction) {
  static constexpr std::string_view prologue =
        "\n  pushq %rbp"
        "\n  movq %rsp, %rbp"
        "\n  subq $8, %rsp";

  return std::visit([](auto &&arg) -> std::string {
    using T = std::decay_t<decltype(arg)>;

    if constexpr (std::is_same_v<T, x86::start_function>) {
      return std::format("  .globl {}\n{}:{}", arg.name, arg.name, prologue);
    } else if constexpr (std::is_same_v<T, x86::mov>) {
      return std::format("  mov {}, {}", arg.src, arg.dst);
    } else if constexpr (std::is_same_v<T, x86::ret>) {
      return "  ret";
    } else {
      static_assert(false, "non-exhaustive visitor!");
      return "";
    }
  }, instruction);
}