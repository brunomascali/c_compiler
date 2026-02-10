#ifndef C_COMPILER_AST_FWD_HPP
#define C_COMPILER_AST_FWD_HPP

#include <memory>
#include <variant>

namespace ast
{
  template <typename T>
  using Box = std::unique_ptr<T>;

  struct unary;
  struct binary;
  struct variable;
  struct assignment;
  struct call;

  using expr = std::variant<int, Box<variable>, Box<unary>, Box<binary>, Box<assignment>, Box<call>>;

  struct return_;
  struct if_;
  struct block;
  struct while_;
  struct for_;

  using statement =
    std::variant<Box<return_>, Box<if_>, Box<block>, Box<while_>, Box<for_>, expr>;
}  // namespace ast

#endif  // C_COMPILER_AST_FWD_HPP
