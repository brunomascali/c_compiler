#ifndef C_COMPILER_MOV_HPP
#define C_COMPILER_MOV_HPP

#include "operand.hpp"

namespace x86 {
  struct mov {
    mov(const operand s, const operand t)
      : src(s), dst(t) {
    }

    operand src;
    operand dst;
  };
}

#endif //C_COMPILER_MOV_HPP
