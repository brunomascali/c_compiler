#ifndef C_COMPILER_AST_IF_HPP
#define C_COMPILER_AST_IF_HPP

#include <ast/ast_fwd.hpp>

namespace ast {

  struct if_
  {
    expr condition;
    statement then_branch;
    std::optional<statement> else_branch;
  };
}

#endif