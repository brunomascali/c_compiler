#ifndef C_COMPILER_AST_WHILE_HPP
#define C_COMPILER_AST_WHILE_HPP

#include <ast/ast_fwd.hpp>

namespace ast {

  struct while_
  {
    expr condition;
    statement body;
  };
}

#endif