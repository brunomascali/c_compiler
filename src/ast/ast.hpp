#ifndef C_COMPILER_AST_HPP
#define C_COMPILER_AST_HPP

#include <ast/expr.hpp>
#include <ast/statement.hpp>
#include <lexer/token.hpp>
#include <optional>
#include <string>
#include <vector>

#include "ast.hpp"

namespace ast
{
  struct function;

  struct program
  {
    std::vector<function> functions;
  };

  struct function
  {
    std::string name;
    block body;
  };


}  // namespace ast

constexpr std::optional<ast::unary::op> unop_from_token_kind(const token::token_kind k) {
  using tk = token::token_kind;
  using unop = ast::unary::op;
  static std::vector<std::tuple<tk, unop>> unary_operators = {
    {tk::tilde, unop::negate}, {tk::hyphen, unop::not_}, {tk::negation, unop::negate}};

  for (const auto &[token_kind, unary_operator] : unary_operators) {
    if (token_kind == k) return unary_operator;
  }

  return std::nullopt;
}

constexpr std::optional<ast::binary::op> binop_from_token_kind(const token::token_kind k) {
  using tk = token::token_kind;
  using binop = ast::binary::op;
  static std::vector<std::tuple<tk, binop>> binary_operators = {
    {tk::plus, binop::add},        {tk::hyphen, binop::sub},   {tk::asterisk, binop::mul},
    {tk::slash, binop::div},       {tk::percent, binop::rem},  {tk::double_ampersand, binop::and_},
    {tk::double_pipe, binop::or_}, {tk::double_eq, binop::eq}, {tk::neq, binop::neq},
    {tk::lt, binop::lt},           {tk::gt, binop::gt},        {tk::le, binop::le},
    {tk::ge, binop::ge},           {tk::equal, binop::assign},
  };

  for (const auto &[token_kind, binary_operator] : binary_operators) {
    if (token_kind == k) return binary_operator;
  }

  return std::nullopt;
}

#endif  // C_COMPILER_AST_HPP
