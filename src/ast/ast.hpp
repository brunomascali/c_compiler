#ifndef C_COMPILER_AST_HPP
#define C_COMPILER_AST_HPP

#include <lexer/token.hpp>
#include <memory>
#include <optional>
#include <string>
#include <variant>
#include <vector>

#include "ast.hpp"

namespace x86 {
struct instruction;
}

namespace ast {
struct unary;
struct binary;

using expr = std::variant<int, std::unique_ptr<unary>, std::unique_ptr<binary>>;

struct unary {
  enum class op { complement, negate };

  op operation;
  expr expression;

  unary(const op o, expr e) : operation(o), expression(std::move(e)) {}
};

struct binary {
  enum class op { add, sub, mul, div, rem, and_, or_, eq, neq, lt, gt, le, ge };

  op operation;
  expr left;
  expr right;

  binary(const op o, expr l, expr r)
      : operation(o), left(std::move(l)), right(std::move(r)) {}
};

struct return_stmt {
  expr expression;
};

using statement = std::variant<return_stmt>;

struct function {
  std::string name;
  std::vector<statement> body;

  function(std::string n, std::vector<statement> b)
      : name(std::move(n)), body(std::move(b)) {}
};

struct program {
  std::vector<function> functions;

  explicit program(std::vector<function> f) : functions(std::move(f)) {}
};
} // namespace ast

constexpr std::optional<ast::unary::op>
try_unop_from_token_kind(const token::token_kind k) {
  using tk = token::token_kind;
  using unop = ast::unary::op;
  static std::vector<std::tuple<tk, unop>> unary_operators = {
      {tk::tilde, unop::negate},
      {tk::hyphen, unop::complement},
      {tk::negation, unop::negate}};

  for (const auto &[token_kind, unary_operator] : unary_operators) {
    if (token_kind == k)
      return unary_operator;
  }

  return std::nullopt;
}

constexpr std::optional<ast::binary::op>
try_binop_from_token_kind(const token::token_kind k) {
  using tk = token::token_kind;
  using binop = ast::binary::op;
  static std::vector<std::tuple<tk, binop>> binary_operators = {
      {tk::plus, binop::add},        {tk::hyphen, binop::sub},
      {tk::asterisk, binop::mul},    {tk::slash, binop::div},
      {tk::percent, binop::rem},     {tk::double_ampersand, binop::and_},
      {tk::double_pipe, binop::or_}, {tk::double_eq, binop::eq},
      {tk::neq, binop::neq},         {tk::lt, binop::lt},
      {tk::gt, binop::gt},           {tk::le, binop::le},
      {tk::ge, binop::le},
  };

  for (const auto &[token_kind, binary_operator] : binary_operators) {
    if (token_kind == k)
      return binary_operator;
  }

  return std::nullopt;
}

#endif // C_COMPILER_AST_HPP
