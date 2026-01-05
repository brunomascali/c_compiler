#include "ir.hpp"

namespace ir {
  ir_generator::ir_generator(const ast::program &root) {
    for (const auto &function_definition: root.functions) {
      from_function_node(function_definition);
    }
  }

  std::vector<instruction> ir_generator::instructions() {
    return m_instructions;
  }

  void ir_generator::from_function_node(const ast::function &func) {
    m_instructions.emplace_back(start_function(func));
    for (const auto &stmt: func.body) {
      from_statement_node(stmt);
    }
  }

  value_t ir_generator::operand_from_expr_node(const ast::expr &expr) {
    return std::visit([&](auto &&arg) {
      using T = std::decay_t<decltype(arg)>;

      if constexpr (std::is_same_v<T, int>) {
        return value_t(arg);
      }
      if constexpr (std::is_same_v<T, ast::unary>) {
        auto src = operand_from_expr_node(std::move(*arg.exp));
        auto dst = value_t(new_variable());
        m_instructions.emplace_back(unary_instruction{arg.operation, src, dst});
        return dst;
      }
    }, expr);
  }

  void ir_generator::from_statement_node(const ast::statement& stmt) {
    std::visit([&](auto &&arg) {
      using T = std::decay_t<decltype(arg)>;

      if constexpr (std::is_same_v<T, ast::return_stmt>) {
        auto src = operand_from_expr_node(std::move(arg.expression));
        m_instructions.emplace_back(return_instruction(std::move(src)));
      }
    }, stmt);
  }

  std::string ir_generator::new_variable() {
    constexpr auto TEMP_VAR = "TMP";
    return std::format("{}_{}", TEMP_VAR, tmp_variable_suffix++);
  }
}
