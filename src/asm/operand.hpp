#ifndef C_COMPILER_OPERAND_HPP
#define C_COMPILER_OPERAND_HPP

#include <format>
#include <string>
#include <variant>

#include "ast/ast.hpp"

namespace x86 {
  enum class reg {
    // Standard General Purpose
    rax, rbx, rcx, rdx,
    // Index Registers
    rsi, rdi,
    // Stack and Base Pointers
    rbp, rsp,
    // Numbered Registers
    r8, r9, r10, r11,
    r12, r13, r14, r15
  };

  enum class bit_width {
    BYTE, WORD, DWORD, QWORD
  };

  struct sized_register {
    reg id;
    bit_width width;
  };

  // operand ::= imm(int) | register
  struct operand {
    using immediate = int;
    std::variant<immediate, sized_register> value;

    explicit operand(int n) : value(n) {
    }

    explicit operand(sized_register r) : value(r) {
    }

    [[nodiscard]] std::string to_string() const;
  };
}

inline x86::operand ast_to_operand(const ast::expr &expr) {
  return std::visit([](const auto &expr) -> x86::operand {
    using T = std::decay_t<decltype(expr)>;

    if constexpr (std::is_same_v<T, int>) {
      return x86::operand(expr);
    } else
      static_assert(false, "non-exhaustive visitor!");
  }, expr);
}

constexpr std::string_view to_string(const x86::sized_register &register_) {
  const auto &[r, bit_width] = register_;
  using reg = x86::reg;
  if (bit_width == x86::bit_width::DWORD) {
    switch (r) {
      case reg::rax: return "eax";
      case reg::rbx: return "ebx";
      case reg::rcx: return "ecx";
      case reg::rdx: return "edx";
      case reg::rsi: return "esi";
      case reg::rdi: return "edi";
      case reg::rbp: return "ebp";
      case reg::rsp: return "esp";
      case reg::r8: return "r8d";
      case reg::r9: return "r9d";
      case reg::r10: return "r10d";
      case reg::r11: return "r11d";
      case reg::r12: return "r12d";
      case reg::r13: return "r13d";
      case reg::r14: return "r14d";
      case reg::r15: return "r15d";
      default: return "unknown";
    }
  }
  switch (r) {
    case reg::rax: return "rax";
    case reg::rbx: return "rbx";
    case reg::rcx: return "rcx";
    case reg::rdx: return "rdx";
    case reg::rsi: return "rsi";
    case reg::rdi: return "rdi";
    case reg::rbp: return "rbp";
    case reg::rsp: return "rsp";
    case reg::r8: return "r8";
    case reg::r9: return "r9";
    case reg::r10: return "r10";
    case reg::r11: return "r11";
    case reg::r12: return "r12";
    case reg::r13: return "r13";
    case reg::r14: return "r14";
    case reg::r15: return "r15";
    default: return "unknown";
  }
}

template<>
struct std::formatter<x86::operand> {
  int bit_width = 64;

  constexpr auto parse(std::format_parse_context &ctx) {
    auto it = ctx.begin();
    if (it != ctx.end() && *it != '}') {
      if (*it == '3') {
        bit_width = 32;
        it += 2;
      } else if (*it == '6') {
        bit_width = 64;
        it += 2;
      }
    }
    return it;
    return ctx.begin();
  }

  auto format(const x86::operand &op, std::format_context &ctx) const {
    return std::visit([&](auto &&arg) {
      using T = std::decay_t<decltype(arg)>;
      if constexpr (std::is_same_v<T, int>) {
        return std::format_to(ctx.out(), "${}", arg);
      } else if constexpr (std::is_same_v<T, x86::sized_register>) {
        return std::format_to(ctx.out(), "%{}", ::to_string(arg));
      }
    }, op.value);
  }
};

inline std::string x86::operand::to_string() const {
  return std::format("{}", *this);
}

namespace x86 {
  constexpr auto EAX = sized_register{reg::rax, bit_width::DWORD};
}

#endif //C_COMPILER_OPERAND_HPP
