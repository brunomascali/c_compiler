#ifndef C_COMPILER_MOV_HPP
#define C_COMPILER_MOV_HPP

#include "operand.hpp"
#include <asm/bit_width.hpp>

namespace x86 {
  struct mov {
    mov(operand s, operand t, const bit_width b = bit_width::dword)
      : src(std::move(s)), dst(std::move(t)), width(b) {
    }

    [[nodiscard]] std::string string() const {
      return std::format("  mov{} {}, {}", to_string(width), src, dst);
    }

    operand src;
    operand dst;
    bit_width width;
  };
}

#endif //C_COMPILER_MOV_HPP
