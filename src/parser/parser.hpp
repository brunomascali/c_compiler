#ifndef C_COMPILER_PARSER_HPP
#define C_COMPILER_PARSER_HPP

#include "lexer/token.hpp"
#include <ast/ast_fwd.hpp>
#include <ast/program.hpp>
#include <ast/function.hpp>
#include <ast/expr/assignment.hpp>
#include <ast/expr/binary.hpp>
#include <ast/expr/unary.hpp>
#include <ast/expr/call.hpp>
#include <ast/expr/variable.hpp>

#include <ast/statement/block_item.hpp>
#include <ast/statement/block.hpp>
#include <ast/statement/declaration.hpp>
#include <ast/statement/for.hpp>
#include <ast/statement/if.hpp>
#include <ast/statement/return.hpp>
#include <ast/statement/while.hpp>

class parser
{
public:
  parser() {}

  ast::program parse(std::vector<token> &tokens);

private:
  std::vector<token> m_tokens{};
  std::size_t m_idx{0};

  ast::program parse_program();

  ast::function parse_function();

  ast::block parse_block();

  ast::block_item parse_block_item();

  ast::declaration parse_declaration();

  ast::statement parse_statement();

  ast::return_ parse_return();

  ast::while_ parse_while();

  ast::for_ parse_for();

  ast::if_ parse_if();

  ast::expr parse_expr(int min_prec = 0);

  ast::expr parse_factor();

  void advance() { m_idx++; }

  [[nodiscard]] token current_token() const { return m_tokens.at(m_idx); }

  [[nodiscard]] token::token_kind current_token_kind() const { return m_tokens.at(m_idx).kind(); }

  void consume(token::token_kind kind, std::string_view error_msg);

  std::string consume_and_extract_lexeme(token::token_kind kind, std::string_view error_msg);

  void expect_or_fail(token::token_kind kind) const;

  void expect_or_fail(token::token_kind kind, std::string_view msg) const;
};


#endif  // C_COMPILER_PARSER_HPP
