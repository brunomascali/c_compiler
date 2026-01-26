#ifndef C_COMPILER_PARSER_HPP
#define C_COMPILER_PARSER_HPP

#include <generator>

#include "ast/ast.hpp"
#include "lexer/lexer.hpp"
#include "lexer/token.hpp"

class parser {
 public:
  explicit parser(std::vector<token> tokens) : m_tokens(std::move(tokens)), m_idx(0) {}

  ast::program parse();

 private:
  std::vector<token> m_tokens;
  std::size_t m_idx;

  ast::program parse_program();

  ast::function parse_function();

  ast::block_item parse_block_item();

  ast::declaration parse_declaration();

  ast::statement parse_statement();

  ast::return_stmt parse_return();

  ast::while_stmt parse_while();

  ast::if_stmt parse_if();

  ast::expr parse_expr(int min_prec = 0);

  ast::expr parse_factor();

  void advance() { m_idx++; }

  [[nodiscard]] token current_token() const { return m_tokens.at(m_idx); }

  [[nodiscard]] token::token_kind current_token_kind() const { return m_tokens.at(m_idx).kind(); }

  [[nodiscard]] token peek() const { return m_tokens.at(m_idx + 1); }

  void expect_or_fail(token::token_kind kind) const;
};


#endif  // C_COMPILER_PARSER_HPP
