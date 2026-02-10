#ifndef C_COMPILER_AST_PROGRAM_HPP
#define C_COMPILER_AST_PROGRAM_HPP

#include <ast/ast_fwd.hpp>
#include <ast/function.hpp>

namespace ast {
  struct program
  {
    std::vector<function> functions;
  };
}

#endif