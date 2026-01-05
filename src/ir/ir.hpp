#ifndef C_COMPILER_IR_HPP
#define C_COMPILER_IR_HPP

#include <string>
#include <variant>
#include <vector>

#include "ast/ast.hpp"

namespace ir {
  using immediate = int;
  using identifier = std::string;
  using value_t = std::variant<immediate, identifier>;

  struct unary_instruction {
    unary_instruction(const ast::unary::op op, value_t src, value_t dst)
      : op(op), src(std::move(src)), dst(std::move(dst)) {
    }

    ast::unary::op op;
    value_t src, dst;
  };

  struct return_instruction {
    explicit return_instruction(value_t v)
      : value(std::move(v)) {
    }

    value_t value;
  };

  struct start_function {
    explicit start_function(const ast::function &func) : name(func.name) {}

    std::string name;
  };

  struct end_function {
    explicit end_function(const ast::function &func) : name(func.name) {}

    std::string name;
  };

  using instruction = std::variant<unary_instruction, return_instruction, start_function>;

  class ir_generator {
  public:
    ir_generator() = delete;

    explicit ir_generator(const ast::program &root);

    std::vector<instruction> instructions();

  private:
    void from_function_node(const ast::function &func);

    void from_statement_node(const ast::statement &stmt);

    value_t operand_from_expr_node(const ast::expr &expr);


    std::string new_variable();

    std::vector<instruction> m_instructions{};
    std::size_t tmp_variable_suffix{0};
  };
}

#endif //C_COMPILER_IR_HPP
