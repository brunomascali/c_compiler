#include "ir_printer.hpp"

#include <ast/ast_printer.hpp>
#include <format>
#include <iostream>
#include <print>

namespace ir
{

  template <class... Ts>
  struct overloaded : Ts...
  {
    using Ts::operator()...;
  };
  template <class... Ts>
  overloaded(Ts...) -> overloaded<Ts...>;

  void print(const program& p) {
    for (const auto& func : p.functions) {
      print(func);
      std::cout << "\n";
    }
  }

  void print(const function& f) {
    for (const auto& ins : f.instructions) {
      std::cout << "    ";
      print(ins);
    }
  }

  std::string to_string(const value& v) {
    return std::visit(
      overloaded{[](const int imm) { return std::to_string(imm); }, [](const std::string& id) { return id; }}, v);
  }

  void print(const instruction& ins) {
    std::visit(
      overloaded{
        [](const unary& u) { std::cout << std::format("{} = negate {}\n", to_string(u.dst), to_string(u.src)); },
        [](const binary& b)
        {
          std::cout << std::format("{} = {} {}, {}\n", to_string(b.dst), op_to_string(b.op), to_string(b.arg1),
                                   to_string(b.arg2));
        },
        [](const return_& r) { std::cout << std::format("ret {}\n", to_string(r.val)); },
        [](const copy& c) { std::cout << std::format("{} = {}\n", to_string(c.dst), to_string(c.src)); },
        [](const jump& j) { std::cout << std::format("jmp {}\n", j.target); },
        [](const jump_if_zero& j) { std::cout << std::format("jz {}, {}\n", to_string(j.condition), j.target); },
        [](const jump_if_not_zero& j) { std::cout << std::format("jnz {}, {}\n", to_string(j.condition), j.target); },
        [](const label& l) { std::cout << "\b\b\b\b" << l.name << ":\n"; },
        [](const begin_scope&) { std::cout << "\b\b\b\b" << "begin_scope\n"; },
        [](const end_scope&) { std::cout << "\b\b\b\b" << "end_scope\n"; },
        [](const symbol& s) { std::cout << "symbol " << s.name << "\n"; },
        [](const function& f) { std::cout << "\b\b\b\bfunction " << f.name << "():\n"; },
        [](const call& c)
        {
          if (c.dst) {
            std::println("{} = call {}", c.dst.value(), c.name);
          } else {
            std::println("call {}", c.name);
          }
        },
        [](const auto&) { std::cout << "unknown instruction\n"; }},
      ins);
  }

}  // namespace ir
