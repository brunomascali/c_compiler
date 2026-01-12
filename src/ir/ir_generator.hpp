#ifndef C_COMPILER_IR_HPP
#define C_COMPILER_IR_HPP

#include <string>
#include <variant>
#include <vector>

#include <ast/ast.hpp>
#include <ir/binary.hpp>
#include <ir/function.hpp>
#include <ir/return.hpp>
#include <ir/unary.hpp>

namespace ir {

using instruction = std::variant<unary, binary, return_, start_function>;

class ir_generator {
public:
  ir_generator() = delete;

  explicit ir_generator(const ast::program &root);

  std::vector<instruction> instructions();

private:
  void from_function_node(const ast::function &func);

  void from_statement_node(const ast::statement &stmt);

  value operand_from_expr_node(const ast::expr &expr);

  std::string new_variable();

  std::vector<instruction> m_instructions{};
  std::size_t tmp_variable_suffix{0};
};
} // namespace ir

#endif // C_COMPILER_IR_HPP
