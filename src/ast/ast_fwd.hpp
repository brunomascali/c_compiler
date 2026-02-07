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
  struct return_stmt;
  struct while_stmt;
  struct for_stmt;
  struct declaration;
  struct if_stmt;
  struct block;

  using expr = std::variant<int, Box<variable>, Box<unary>, Box<binary>, Box<assignment>, Box<call>>;

  using statement =
    std::variant<Box<return_stmt>, Box<if_stmt>, Box<block>, Box<while_stmt>, Box<for_stmt>, expr, std::monostate>;
}  // namespace ast

#endif  // C_COMPILER_AST_FWD_HPP
