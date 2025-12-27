#ifndef C_COMPILER_MOV_HPP
#define C_COMPILER_MOV_HPP
#include <memory>

#include "instruction.hpp"

namespace x86 {
  struct mov : instruction {

    mov(std::unique_ptr<instruction> s, std::unique_ptr<instruction> t)
      : src(std::move(s)), dst(std::move(t)) {}

    std::unique_ptr<instruction> src;
    std::unique_ptr<instruction> dst;

    [[nodiscard]] std::string to_string() const override {
      return "mov";
    }
  };
}

#endif //C_COMPILER_MOV_HPP