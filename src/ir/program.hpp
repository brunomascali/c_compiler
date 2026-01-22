#ifndef C_COMPILER_PROGRAM_HPP
#define C_COMPILER_PROGRAM_HPP

#include <vector>
#include <ir/function.hpp>

namespace ir
{
  struct program
  {
    std::vector<function> functions;
  };
}

#endif  // C_COMPILER_PROGRAM_HPP
