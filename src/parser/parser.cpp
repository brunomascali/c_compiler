#include "parser.hpp"

#include "ir/ir_generator.hpp"

ast::program parser::parse() { return parse_program(); }

ast::program parser::parse_program() {
  std::vector<ast::function> functions;
  functions.emplace_back(parse_function());
  return ast::program(std::move(functions));
}

ast::function parser::parse_function() {
  ast::block block;
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

  while (current_token().kind() != token::token_kind::brace_close) {
    block.items.emplace_back(parse_block_item());
  }
  advance();

  return ast::function{identifier, std::move(block)};
}

ast::block_item parser::parse_block_item() {
  using tk = token::token_kind;
  if (current_token_kind() == tk::int_kw) {
    return std::make_unique<ast::declaration>(parse_declaration());
  }

  return std::make_unique<ast::statement>(parse_statement());
}

ast::statement parser::parse_statement() {
  using tk = token::token_kind;
  if (current_token_kind() == tk::if_kw) {
    return std::make_unique<ast::if_stmt>(parse_if());
  }
  if (current_token_kind() == tk::return_kw) {
    return std::make_unique<ast::return_stmt>(parse_return());
  }
  if (current_token_kind() == tk::while_kw) {
    return std::make_unique<ast::while_stmt>(parse_while());
  }
  if (current_token_kind() == tk::brace_open) {
    advance();
    auto block = std::make_unique<ast::block>();
    while (current_token_kind() != tk::brace_close) {
      block->items.emplace_back(parse_block_item());
    }
    advance();
    return block;
  }

  auto e = parse_expr();
  expect_or_fail(tk::semicolon);
  advance();
  return e;
}

ast::return_stmt parser::parse_return() {
  using tk = token::token_kind;
  expect_or_fail(tk::return_kw);
  advance();
  auto expr = parse_expr();
  expect_or_fail(tk::semicolon);
  advance();

  return ast::return_stmt(std::move(expr));
}

ast::while_stmt parser::parse_while() {
  using tk = token::token_kind;
  expect_or_fail(tk::while_kw);
  advance();
  expect_or_fail(tk::paren_open);
  advance();
  auto cond = parse_expr();
  expect_or_fail(tk::paren_close);
  advance();
  auto body = parse_statement();

  return ast::while_stmt(std::move(cond), std::move(body));
}

ast::if_stmt parser::parse_if() {
  using tk = token::token_kind;
  expect_or_fail(tk::if_kw);
  advance();
  expect_or_fail(tk::paren_open);
  advance();
  auto cond = parse_expr();
  expect_or_fail(tk::paren_close);
  advance();
  expect_or_fail(tk::brace_open);
  advance();
  auto then = parse_statement();
  expect_or_fail(tk::brace_close);
  advance();

  return ast::if_stmt(std::move(cond), std::move(then));
}

ast::declaration parser::parse_declaration() {
  using tk = token::token_kind;

  expect_or_fail(tk::int_kw);
  advance();

  expect_or_fail(tk::identifier);
  const auto identifier = current_token().lexeme();
  advance();

  std::optional<ast::expr> e = std::nullopt;

  if (current_token().kind() == tk::equal) {
    advance();

    e = parse_expr();
  }
  expect_or_fail(tk::semicolon);
  advance();

  return ast::declaration(identifier, std::move(e));
}

ast::expr parser::parse_expr(int min_prec) {
  ast::expr left = parse_factor();

  while (true) {
    const auto op_kind = current_token_kind();
    auto op_opt = binop_from_token_kind(op_kind);

    if (!op_opt.has_value()) break;

    auto prec_opt = precedence(op_kind);
    if (!prec_opt.has_value() || prec_opt.value() < min_prec) break;

    const int current_prec = prec_opt.value();
    advance();

    const int next_min_prec = (op_kind == token::token_kind::equal) ? current_prec : current_prec + 1;

    auto right = parse_expr(next_min_prec);

    if (op_kind == token::token_kind::equal) {
      left = std::make_unique<ast::assignment>(std::move(left), std::move(right));
    }
    else {
      left = std::make_unique<ast::binary>(op_opt.value(), std::move(left), std::move(right));
    }
  }

  return left;
}

ast::expr parser::parse_factor() {
  using tk = token::token_kind;

  // literal
  if (current_token_kind() == tk::number) {
    const std::string number = current_token().lexeme();
    advance();
    return {std::stoi(number)};
  }

  // unary
  if (const auto opt = unop_from_token_kind(current_token_kind()); opt.has_value()) {
    const auto unary_operator = opt.value();
    advance();
    auto operand = parse_expr();
    return std::make_unique<ast::unary>(unary_operator, std::move(operand));
  }

  // ( <expr> )
  if (current_token_kind() == tk::paren_open) {
    advance();
    auto expr = parse_expr();
    expect_or_fail(tk::paren_close);
    advance();
    return expr;
  }

  // identifier
  if (current_token().kind() == tk::identifier) {
    auto expr = std::make_unique<ast::variable>(current_token().lexeme());
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
