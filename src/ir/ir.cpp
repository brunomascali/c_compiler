#include "ir.hpp"

ir_generator::ir_generator(const ast::program& root) {
  for (const auto& function_definition : root.functions) {
    from_function_node(function_definition);
  }
}

std::vector<ir::instruction> ir_generator::instructions() { return m_instructions; }

void ir_generator::from_function_node(const ast::function& func) {
  m_instructions.emplace_back(ir::start_function(func));
  for (const auto& stmt : func.body) {
    from_statement_node(stmt);
  }
}

ir::value_t ir_generator::operand_from_expr_node(const ast::expr& expr) {
  return std::visit(
    [&](auto&& arg)
    {
      using T = std::decay_t<decltype(arg)>;

      if constexpr (std::is_same_v<T, int>) {
        return ir::value_t(arg);
      }
      else if constexpr (std::is_same_v<T, std::unique_ptr<ast::unary>>) {
        auto src = operand_from_expr_node(arg->expression);
        auto dst = ir::value_t(new_variable());
        m_instructions.emplace_back(ir::unary_instruction{arg->operation, src, dst});
        return dst;
      }
      if constexpr (std::is_same_v<T, std::unique_ptr<ast::binary>>) {
        auto lhs = operand_from_expr_node(arg->left);
        auto rhs = operand_from_expr_node(arg->right);
        auto dst = ir::value_t(new_variable());
        m_instructions.emplace_back(ir::binary_instruction(arg->operation, lhs, rhs, dst));
        return dst;
      }
    },
    expr);
}

void ir_generator::from_statement_node(const ast::statement& stmt) {
  std::visit(
    [&](auto&& arg)
    {
      using T = std::decay_t<decltype(arg)>;

      if constexpr (std::is_same_v<T, ast::return_stmt>) {
        auto src = operand_from_expr_node(std::move(arg.expression));
        m_instructions.emplace_back(ir::return_instruction(std::move(src)));
      }
    },
    stmt);
}

std::string ir_generator::new_variable() {
  constexpr auto TEMP_VAR = "TMP";
  return std::format("{}_{}", TEMP_VAR, tmp_variable_suffix++);
}
