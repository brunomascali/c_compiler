#ifndef C_COMPILER_AST_DECLARATION_HPP
#define C_COMPILER_AST_DECLARATION_HPP

#include <ast/ast_fwd.hpp>

namespace ast {

  struct declaration
  {
    std::string identifier;
    std::optional<expr> init;
  };
}

#endif