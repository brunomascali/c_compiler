#ifndef C_COMPILER_AST_HPP
#define C_COMPILER_AST_HPP

#include <ast/ast_fwd.hpp>
#include <ast/statement.hpp>
#include <lexer/token.hpp>
#include <string>
#include <vector>

namespace ast
{
  struct function;

  struct program
  {
    std::vector<function> functions;
  };

  struct function
  {
    std::string name;
    block body;
  };


}  // namespace ast





#endif  // C_COMPILER_AST_HPP
