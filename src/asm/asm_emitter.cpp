#include "asm_emitter.hpp"

std::vector<asm_emitter::instruction> asm_emitter::emit(const ast::program &program) {
  for (const auto& func: program.statements) {
    gen_from_function_ast_node(func);
    for (const auto &stmt: func.body) {
      visit_statement(stmt);
    }
  }

  return m_instructions;
}

void asm_emitter::visit_statement(const ast::statement &statement) {
  std::visit([this] (auto &&arg) {
    using T = std::decay_t<decltype(arg)>;

    if constexpr (std::is_same_v<T, ast::return_stmt>)
      asm_from_return_ast_node(arg);
    else
      static_assert(false, "non-exhaustive visitor!");
  }, statement);
}

void asm_emitter::asm_from_return_ast_node(const ast::return_stmt &statement) {
  const auto src = ast_to_operand(statement.expression);
  const auto dst = x86::operand(x86::reg::eax);
  m_instructions.push_back(x86::mov(src, dst));
  m_instructions.push_back(x86::ret{});
}

void asm_emitter::gen_from_function_ast_node(const ast::function& function) {
  m_instructions.push_back(x86::start_function(function.name));
}