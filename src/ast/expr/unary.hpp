#ifndef C_COMPILER_UNARY_HPP
#define C_COMPILER_UNARY_HPP

#include <ast/ast_fwd.hpp>
#include <lexer/lexer.hpp>
#include <optional>

namespace ast
{
  struct unary
  {
    enum class op
    {
      not_,
      negate,
      pre_increment
    };
    op operation;
    expr child;
  };

  constexpr std::optional<unary::op> unop_from_token_kind(token::token_kind k) {
    using tk = token::token_kind;
    using unop = unary::op;

    switch (k) {
      case tk::tilde:
        return unop::negate;
      case tk::hyphen:
        return unop::not_;
      case tk::negation:
        return unop::negate;
      default:
        return std::nullopt;
    }
  }
}  // namespace ast

#endif  // C_COMPILER_UNARY_HPP
