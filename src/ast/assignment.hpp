#ifndef C_COMPILER_ASSIGNMENT_HPP
#define C_COMPILER_ASSIGNMENT_HPP

#include <ast/ast_fwd.hpp>

namespace ast
{
  struct assignment
  {
    expr lhs;
    expr rhs;
  };
}

#endif //C_COMPILER_ASSIGNMENT_HPP
