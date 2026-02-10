#ifndef C_COMPILER_AST_FUNCTION_HPP
#define C_COMPILER_AST_FUNCTION_HPP

#include <ast/ast_fwd.hpp>
#include <ast/statement/block.hpp>

namespace ast {
  struct function
  {
    std::string name;
    block body;
  };
}

#endif