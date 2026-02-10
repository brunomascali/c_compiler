#ifndef C_COMPILER_AST_FOR_HPP
#define C_COMPILER_AST_FOR_HPP

#include <ast/ast_fwd.hpp>
#include <ast/statement/declaration.hpp>

namespace ast {

  struct for_
  {
    declaration init;
    expr condition;
    expr post;
    statement body;
  };
}

#endif