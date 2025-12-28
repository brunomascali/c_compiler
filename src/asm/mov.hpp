#ifndef C_COMPILER_MOV_HPP
#define C_COMPILER_MOV_HPP

#include <memory>
#include "instruction.hpp"

namespace x86 {
  struct mov : instruction {

    mov(std::unique_ptr<operand> s, std::unique_ptr<operand> t)
      : src(std::move(s)), dst(std::move(t)) {}

    std::unique_ptr<operand> src;
    std::unique_ptr<operand> dst;

    [[nodiscard]] std::string to_string() const override {
      return std::format("mov {} {}", src->to_string(), dst->to_string());
    }
  };
}

#endif //C_COMPILER_MOV_HPP