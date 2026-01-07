#include "parser.hpp"

ast::program parser::parse() {
  return parse_program();
}

ast::program parser::parse_program() {
  std::vector<ast::function> functions;
  functions.emplace_back(parse_function());
  return ast::program(std::move(functions));
}

ast::function parser::parse_function() {
  std::vector<ast::statement> statements;
  expect_or_fail(token::token_kind::int_kw);
  advance();

  expect_or_fail(token::token_kind::identifier);
  const auto identifier = current_token().lexeme();
  advance();

  expect_or_fail(token::token_kind::paren_open);
  advance();
  expect_or_fail(token::token_kind::void_kw);
  advance();
  expect_or_fail(token::token_kind::paren_close);
  advance();

  expect_or_fail(token::token_kind::brace_open);
  advance();
  statements.emplace_back(parse_statement());
  expect_or_fail(token::token_kind::brace_close);
  advance();

  return ast::function{ identifier, std::move(statements) };
}

ast::statement parser::parse_statement() {
  using tk = token::token_kind;
  expect_or_fail(tk::return_kw);
  advance();
  auto expr = parse_expr();
  expect_or_fail(tk::semicolon);
  advance();

  return ast::return_stmt(std::move(expr));
}

ast::expr parser::parse_expr() {
  using tk = token::token_kind;
  ast::expr left = parse_factor();

  // todo: compute this once
  while (try_binop_from_token_kind(current_token_kind()).has_value()) {
    const auto binary_operator = try_binop_from_token_kind(current_token_kind()).value();
    advance();
    auto right = parse_factor();
    left = std::make_unique<ast::binary>(binary_operator, std::move(left), std::move(right));
  }
  if (current_token_kind() == tk::number) {
    const std::string number = current_token().lexeme();
    advance();
    return std::stoi(number);
  }

  return left;
}

ast::expr parser::parse_factor() {
  using tk = token::token_kind;

  if (current_token_kind() == tk::number) {
    const std::string number = current_token().lexeme();
    advance();
    return std::stoi(number);
  }

  if (const auto opt = try_unop_from_token_kind(current_token_kind()); opt.has_value()) {
    const auto unary_operator = opt.value();
    advance();
    auto operand = parse_expr();
    return std::make_unique<ast::unary>(unary_operator, std::move(operand));
  }

  if (current_token_kind() == tk::paren_open) {
    advance();
    auto expr = parse_expr();
    expect_or_fail(tk::paren_close);
    advance();
    return expr;
  }

  throw std::logic_error("Malformed factor");
}

void parser::expect_or_fail(const token::token_kind kind) const {
  if (const auto token = current_token(); token.kind() != kind) {
    throw std::runtime_error(std::format("expected '{}' found '{}'", kind, token));
  }
}
