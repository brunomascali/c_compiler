#ifndef C_COMPILER_IR_HPP
#define C_COMPILER_IR_HPP

#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "ast/ast.hpp"

namespace ir {
  enum class unary_operator {
    complement, negate
  };

  using immediate = int;
  using identifier = std::string;
  using value = std::variant<immediate, identifier>;

  struct unary_instruction {
    ast::unary::op op;
    value src, dst;

    unary_instruction(const ast::unary::op op, value src, value dst) : op(op), src(std::move(src)), dst(std::move(dst)) {}
  };

  struct return_instruction {
    value val;
  };

  using instruction = std::variant<unary_instruction, return_instruction, value>;
  using context = std::vector<instruction>;

  value from_expr_node(context& ctx, ast::expr exp);

  void from_statement_node(context& ctx, ast::statement stmt);
}

#endif //C_COMPILER_IR_HPP
