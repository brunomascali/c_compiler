#ifndef C_COMPILER_PARSER_HPP
#define C_COMPILER_PARSER_HPP

#include <vector>
#include <memory>

#include "ast/ast.hpp"
#include "lexer/token.hpp"

class parser {
public:
  explicit parser(std::vector<token> tokens) : m_tokens(std::move(tokens)), m_idx(0) {
  }

  ast::program parse();

private:
  std::vector<token> m_tokens;
  std::size_t m_idx;

  ast::program parse_program();

  ast::function parse_function();

  ast::statement parse_statement();

  ast::expr parse_expr();

  ast::expr parse_factor();

  [[nodiscard]] std::vector<token> tokens() const { return m_tokens; }

  [[nodiscard]] std::size_t index() const { return m_idx; }

  void advance() { m_idx++; }

  [[nodiscard]] token current_token() const { return m_tokens.at(m_idx); }

  [[nodiscard]] token::token_kind current_token_kind() const { return m_tokens.at(m_idx).kind(); }

  void expect_or_fail(token::token_kind kind) const;
};


#endif //C_COMPILER_PARSER_HPP