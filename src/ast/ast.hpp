#ifndef C_COMPILER_AST_HPP
#define C_COMPILER_AST_HPP

#include <string>
#include <variant>
#include <memory>
#include <vector>
#include <optional>
#include <lexer/token.hpp>

namespace x86 {
  struct instruction;
}

namespace ast {
  struct unary;
  struct binary;

  using expr = std::variant<int, unary>;

  struct unary {
    enum class op { complement, negate };

    op operation;
    std::unique_ptr<expr> exp;

    unary(const op operation, expr e) : operation(operation), exp(std::make_unique<expr>(std::move(e))) {
    }
  };

  struct binary {
    expr left;
    std::string op;
    expr right;
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
    std::vector<function> statements;

    explicit program(std::vector<function> f) : statements(std::move(f)) {}
  };
}

constexpr std::optional<ast::unary::op> try_unop_from_token_kind(const token::token_kind k) {
  using tk = token::token_kind;
  using unop = ast::unary::op;
  static std::vector<std::tuple<tk, unop>> unary_operators = {
    {tk::tilde, unop::negate},
    {tk::hyphen, unop::complement}
  };

  for (const auto &[token_kind, unary_operator] : unary_operators) {
    if (token_kind == k) return unary_operator;
  }

  return std::nullopt;
}

#endif //C_COMPILER_AST_HPP
