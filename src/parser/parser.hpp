#ifndef C_COMPILER_PARSER_HPP
#define C_COMPILER_PARSER_HPP

#include <vector>
#include <format>
#include <memory>

#include "../lexer/token.hpp"
#include "../ast/ast.hpp"

class parser {
public:
  explicit parser(std::vector<token> tokens) : m_tokens(std::move(tokens)), m_idx(0) {
  }

  std::unique_ptr<ast_node> parse();

private:
  std::vector<token> m_tokens;
  std::size_t m_idx;

  std::unique_ptr<program_node> parse_program();

  std::unique_ptr<function_node> parse_function();

  std::unique_ptr<statement_node> parse_statement();

  std::unique_ptr<expr_node> parse_number();

  std::vector<token> tokens() const { return m_tokens; }

  std::size_t index() const { return m_idx; }

  void advance() { m_idx++; }

  token current_token() const { return m_tokens.at(m_idx); }

  void expect_or_fail(token::token_kind kind) const;
};


#endif //C_COMPILER_PARSER_HPP