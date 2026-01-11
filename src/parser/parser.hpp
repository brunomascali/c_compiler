#ifndef C_COMPILER_PARSER_HPP
#define C_COMPILER_PARSER_HPP

#include <generator>

#include "ast/ast.hpp"
#include "lexer/lexer.hpp"
#include "lexer/token.hpp"

class parser {
 public:
  explicit parser(lexer& l) : m_token_stream(l.tokenize_lazy()), m_it(m_token_stream.begin()) {}

  ast::program parse();

 private:
  std::generator<token> m_token_stream;
  using token_stream_iterator = std::ranges::iterator_t<std::generator<token>>;
  token_stream_iterator m_it;

  ast::program parse_program();

  ast::function parse_function();

  ast::statement parse_statement();

  ast::expr parse_expr();

  ast::expr parse_factor();

  void advance() { ++m_it; }

  [[nodiscard]] token current_token() const { return *m_it; }

  [[nodiscard]] token::token_kind current_token_kind() const { return (*m_it).kind(); }

  void expect_or_fail(token::token_kind kind) const;
};


#endif  // C_COMPILER_PARSER_HPP
