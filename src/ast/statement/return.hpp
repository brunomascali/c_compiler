#ifndef C_COMPILER_AST_RETURN_HPP
#define C_COMPILER_AST_RETURN_HPP

#include <ast/ast_fwd.hpp>

namespace ast {
  struct return_
  {
    expr value;
  };
}

#endif