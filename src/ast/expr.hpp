#ifndef C_COMPILER_EXPR_HPP
#define C_COMPILER_EXPR_HPP

#include <ast/ast_fwd.hpp>

namespace ast
{
  struct variable
  {
    std::string identifier;
  };

  struct unary
  {
    enum class op
    {
      not_,
      negate
    };
    op operation;
    expr child;
  };

  struct binary
  {
    enum class op
    {
      add,
      sub,
      mul,
      div,
      rem,
      and_,
      or_,
      eq,
      neq,
      lt,
      gt,
      le,
      ge,
      assign
    };
    op operation;
    expr left;
    expr right;
  };

  struct assignment
  {
    expr lhs;
    expr rhs;
  };
}  // namespace ast

#endif  // C_COMPILER_EXPR_HPP
