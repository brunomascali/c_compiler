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

constexpr std::optional<ast::unary::op> unop_from_token_kind(token::token_kind k) {
  using tk = token::token_kind;
  using unop = ast::unary::op;

  switch (k) {
    case tk::tilde:    return unop::negate;
    case tk::hyphen:   return unop::not_;
    case tk::negation: return unop::negate;
    default:           return std::nullopt;
  }
}

constexpr std::optional<ast::binary::op> binop_from_token_kind(token::token_kind k) {
  using tk = token::token_kind;
  using binop = ast::binary::op;

  switch (k) {
    case tk::plus:             return binop::add;
    case tk::hyphen:           return binop::sub;
    case tk::asterisk:         return binop::mul;
    case tk::slash:            return binop::div;
    case tk::percent:          return binop::rem;
    case tk::double_ampersand: return binop::and_;
    case tk::double_pipe:      return binop::or_;
    case tk::double_eq:        return binop::eq;
    case tk::neq:              return binop::neq;
    case tk::lt:               return binop::lt;
    case tk::gt:               return binop::gt;
    case tk::le:               return binop::le;
    case tk::ge:               return binop::ge;
    case tk::equal:            return binop::assign;
    default:                   return std::nullopt;
  }
}

#endif  // C_COMPILER_AST_HPP
