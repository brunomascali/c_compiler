#ifndef C_COMPILER_LEGALIZER_HPP
#define C_COMPILER_LEGALIZER_HPP

#include <vector>

#include "asm/instruction.hpp"

namespace x86
{
  class legalizer {
   public:
    static std::vector<instruction> run(instruction& input);
  };
}  // namespace x86

#endif  // C_COMPILER_LEGALIZER_HPP
