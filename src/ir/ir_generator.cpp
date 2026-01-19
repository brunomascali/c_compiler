#include "ir_generator.hpp"

namespace ir
{
  ir_generator::ir_generator(const ast::program &root) {
    for (const auto &function_definition : root.functions) {
      from_function_node(function_definition);
    }
  }

  std::vector<instruction> ir_generator::instructions() { return m_instructions; }

  void ir_generator::from_function_node(const ast::function &func) {
    m_instructions.emplace_back(start_function(func));
    for (const auto &item : func.body) {
      from_block_item_node(item);
    }
  }

  void ir_generator::from_block_item_node(const ast::block_item &item) {
    std::visit(
      [&](auto &&arg)
      {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, ast::statement>) {
          from_statement_node(arg);
        }
        else if constexpr (std::is_same_v<T, ast::declaration>) {
          auto src = operand_from_expr_node(arg.expression.value());
          auto dst = value(arg.identifier);
          m_instructions.emplace_back(copy(src, dst));
        }
      },
      item);
  }

  value ir_generator::operand_from_expr_node(const ast::expr &expr) {
    return std::visit(
      [&](auto &&arg)
      {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, int>) {
          return value(arg);
        }
        else if constexpr (std::is_same_v<T, std::unique_ptr<ast::unary>>) {
          auto src = operand_from_expr_node(arg->expression);
          auto dst = value(new_variable());
          m_instructions.emplace_back(unary{arg->operation, src, dst});
          return dst;
        }
        else if constexpr (std::is_same_v<T, std::unique_ptr<ast::binary>>) {
          if (arg->operation == ast::binary::op::and_) {
            auto false_label = new_variable();
            auto result = value(new_variable());
            auto end_label = new_variable();
            auto lhs = operand_from_expr_node(arg->left);
            m_instructions.emplace_back(jump_if_zero(false_label, lhs));
            auto rhs = operand_from_expr_node(arg->right);
            m_instructions.emplace_back(jump_if_zero(false_label, rhs));
            m_instructions.emplace_back(copy(value(1), result));
            m_instructions.emplace_back(jump(end_label));
            m_instructions.emplace_back(label(false_label));
            m_instructions.emplace_back(copy(value(0), result));
            m_instructions.emplace_back(label(end_label));
            return result;
          } else {
            auto lhs = operand_from_expr_node(arg->left);
            auto rhs = operand_from_expr_node(arg->right);
            auto dst = value(new_variable());
            m_instructions.emplace_back(binary(arg->operation, lhs, rhs, dst));
            return dst;
          }
        }
        else if constexpr (std::is_same_v<T, std::unique_ptr<ast::variable>>) {
          return value(arg->identifier);
        }
        else if constexpr (std::is_same_v<T, std::unique_ptr<ast::assignment>>) {
          auto lhs = operand_from_expr_node(arg->lhs);
          auto rhs = operand_from_expr_node(arg->rhs);
          m_instructions.emplace_back(copy(rhs, lhs));
          return lhs;
        }
      },
      expr);
  }

  void ir_generator::from_statement_node(const ast::statement &stmt) {
    std::visit(
      [&](auto &&arg)
      {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, ast::return_stmt>) {
          auto src = operand_from_expr_node(std::move(arg.expression));
          m_instructions.emplace_back(return_(std::move(src)));
        }
      },
      stmt);
  }

  std::string ir_generator::new_variable() {
    constexpr auto TEMP_VAR = "TMP";
    return std::format("{}_{}", TEMP_VAR, tmp_variable_suffix++);
  }
}  // namespace ir
