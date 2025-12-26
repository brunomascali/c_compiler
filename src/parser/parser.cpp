#include "parser.hpp"

std::unique_ptr<ast_node> parser::parse() {
  return parse_program();
}

std::unique_ptr<program_node> parser::parse_program() {
  return std::make_unique<program_node>(parse_function());
}

std::unique_ptr<function_node> parser::parse_function() {
  expect_or_fail(token::token_kind::int_kw);
  advance();

  expect_or_fail(token::token_kind::identifier);
  auto identifier = current_token().lexeme();
  advance();

  expect_or_fail(token::token_kind::paren_open);
  advance();
  expect_or_fail(token::token_kind::void_kw);
  advance();
  expect_or_fail(token::token_kind::paren_close);
  advance();

  expect_or_fail(token::token_kind::brace_open);
  advance();
  std::unique_ptr<statement_node> body = parse_statement();
  expect_or_fail(token::token_kind::brace_close);
  advance();

  return std::make_unique<function_node>(identifier, std::move(body));
}

std::unique_ptr<statement_node> parser::parse_statement() {
  expect_or_fail(token::token_kind::return_kw);
  advance();
  auto expr = parse_number();
  advance();

  return std::make_unique<statement_node>(std::move(expr));
}

std::unique_ptr<expr_node> parser::parse_number() {
  expect_or_fail(token::token_kind::number);
  std::string number = current_token().lexeme();
  advance();

  return std::make_unique<expr_node>(number);
}

void parser::expect_or_fail(const token::token_kind kind) const {
  if (const auto token = current_token(); token.kind() != kind) {
    throw std::runtime_error(std::format("expected '{}' found '{}'", kind, token));
  }
}
