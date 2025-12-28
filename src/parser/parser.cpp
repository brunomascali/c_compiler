#include "parser.hpp"

ast::program parser::parse() {
  return parse_program();
}

ast::program parser::parse_program() {
  return ast::program({parse_function()});
}

ast::function parser::parse_function() {
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
  ast::statement body = parse_statement();
  expect_or_fail(token::token_kind::brace_close);
  advance();

  return ast::function(identifier, {body});
}

ast::statement parser::parse_statement() {
  expect_or_fail(token::token_kind::return_kw);
  advance();
  const auto expr = parse_number();
  advance();

  return ast::return_stmt(expr);
}

ast::expr parser::parse_number() {
  expect_or_fail(token::token_kind::number);
  const std::string number = current_token().lexeme();
  advance();

  return std::stoi(number);
}

void parser::expect_or_fail(const token::token_kind kind) const {
  if (const auto token = current_token(); token.kind() != kind) {
    throw std::runtime_error(std::format("expected '{}' found '{}'", kind, token));
  }
}
