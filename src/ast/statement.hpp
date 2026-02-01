#ifndef C_COMPILER_STATEMENT_HPP
#define C_COMPILER_STATEMENT_HPP

#include <ast/ast_fwd.hpp>
#include <vector>

namespace ast
{
  struct return_stmt
  {
    expr value;
  };

  struct declaration
  {
    std::string identifier;
    std::optional<expr> init;
  };

  struct if_stmt
  {
    expr condition;
    statement then_branch;
    std::optional<statement> else_branch;
  };

  struct while_stmt
  {
    expr condition;
    statement body;
  };

  struct for_stmt
  {
    declaration init;
    expr condition;
    expr post;
    statement body;
  };

  struct block_item : std::variant<Box<statement>, Box<declaration>>
  {
    using variant::variant;
  };

  struct block
  {
    std::vector<block_item> items;
  };

  struct compound_stmt
  {
    block block_;
  };

}  // namespace ast

#endif  // C_COMPILER_STATEMENT_HPP
