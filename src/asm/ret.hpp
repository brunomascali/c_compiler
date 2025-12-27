#ifndef C_COMPILER_RET_HPP
#define C_COMPILER_RET_HPP

#include <format>
#include <string>
#include "instruction.hpp"

namespace x86 {
  struct ret : instruction {
    std::string to_string() const {
      return "ret";
    }
  };
}

template<>
struct std::formatter<x86::ret> {
  constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

  auto format(const x86::ret&, std::format_context &ctx) const {
    return std::format_to(ctx.out(), "ret");
  }
};

#endif //C_COMPILER_RET_HPP
