#ifndef C_COMPILER_BINARY_HPP
#define C_COMPILER_BINARY_HPP

#include <lexer/token.hpp>
#include <optional>
#include "ast/ast_fwd.hpp"

namespace ast
{
  struct binary
  {
    enum class op
    {
      add,
      sub,
      mul,
      div,
      rem,
      and_,
      or_,
      eq,
      neq,
      lt,
      gt,
      le,
      ge,
      assign
    };
    op operation;
    expr left;
    expr right;
  };

  [[nodiscard]] inline bool is_comparison(const binary::op op) {
    using binop = binary::op;
    constexpr std::array comparison_operators = {binop::eq, binop::neq, binop::lt, binop::gt, binop::le, binop::ge};

    return std::ranges::find(comparison_operators, op) != comparison_operators.end();
  }

  constexpr std::optional<ast::binary::op> binop_from_token_kind(token::token_kind k) {
    using tk = token::token_kind;
    using binop = ast::binary::op;

    switch (k) {
      case tk::plus:
        return binop::add;
      case tk::hyphen:
        return binop::sub;
      case tk::asterisk:
        return binop::mul;
      case tk::slash:
        return binop::div;
      case tk::percent:
        return binop::rem;
      case tk::double_ampersand:
        return binop::and_;
      case tk::double_pipe:
        return binop::or_;
      case tk::double_eq:
        return binop::eq;
      case tk::neq:
        return binop::neq;
      case tk::lt:
        return binop::lt;
      case tk::gt:
        return binop::gt;
      case tk::le:
        return binop::le;
      case tk::ge:
        return binop::ge;
      case tk::equal:
        return binop::assign;
      default:
        return std::nullopt;
    }
  }
}  // namespace ast

#endif  // C_COMPILER_BINARY_HPP
