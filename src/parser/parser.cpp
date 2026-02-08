#include "parser.hpp"

#include "ir/ir_generator.hpp"

using tk = token::token_kind;

ast::program parser::parse(std::vector<token> &tokens) {
  m_tokens = std::move(tokens);
  ast::program program{};
  while (m_idx < m_tokens.size()) {
    program.functions.push_back(parse_function());
  }
  return program;
}

ast::program parser::parse_program() {
  std::vector<ast::function> functions;
  functions.emplace_back(parse_function());
  return ast::program(std::move(functions));
}

ast::function parser::parse_function() {
  consume(token::token_kind::int_kw, "Expected 'int' return type");

  const auto identifier = consume_and_extract_lexeme(token::token_kind::identifier, "Expected function name");

  consume(token::token_kind::paren_open, "Expected '(' after function name");
  consume(token::token_kind::void_kw, "Expected 'void' in parameter list");
  consume(token::token_kind::paren_close, "Expected ')' after parameter list");

  auto block = parse_block();

  return ast::function{identifier, std::move(block)};
}

ast::block parser::parse_block() {
  consume(tk::brace_open, "Expected '{' at the start of the block");
  ast::block block{};
  while (current_token().kind() != token::token_kind::brace_close) {
    block.items.emplace_back(parse_block_item());
  }
  consume(token::token_kind::brace_close, "Expected '}' at end of the block");
  return block;
}

ast::block_item parser::parse_block_item() {
  if (current_token_kind() == tk::int_kw) {
    return std::make_unique<ast::declaration>(parse_declaration());
  }

  return std::make_unique<ast::statement>(parse_statement());
}

ast::declaration parser::parse_declaration() {
  consume(tk::int_kw, "Expected 'int' type specifier");

  const auto identifier = consume_and_extract_lexeme(tk::identifier, "Expected variable name");

  std::optional<ast::expr> e = std::nullopt;

  if (current_token().kind() == tk::equal) {
    advance();
    e = parse_expr();
  }

  consume(tk::semicolon, "Expected ';' after declaration");

  return ast::declaration(identifier, std::move(e));
}

ast::statement parser::parse_statement() {
  switch (current_token_kind()) {
    case tk::if_kw:
      return std::make_unique<ast::if_stmt>(parse_if());
    case tk::return_kw:
      return std::make_unique<ast::return_stmt>(parse_return());
    case tk::while_kw:
      return std::make_unique<ast::while_stmt>(parse_while());
    case tk::for_kw:
      return std::make_unique<ast::for_stmt>(parse_for());
    case tk::brace_open:
      return std::make_unique<ast::block>(parse_block());
    default:
      auto e = parse_expr();
      consume(tk::semicolon, "Expected semicolon after expr");
      return e;
  }
}

ast::return_stmt parser::parse_return() {
  consume(tk::return_kw, "Expected 'return' keyword");
  auto expr = parse_expr();
  consume(tk::semicolon, "Expected ';' after return statement");

  return ast::return_stmt(std::move(expr));
}

ast::while_stmt parser::parse_while() {
  consume(tk::while_kw, "Expected 'while' keyword");

  consume(tk::paren_open, "Expected '(' after 'while'");
  auto cond = parse_expr();
  consume(tk::paren_close, "Expected ')' after while condition");

  consume(tk::brace_open, "Expected '{' to start while-loop body");
  auto body = parse_statement();
  consume(tk::brace_close, "Expected '}' after while-loop body");

  return ast::while_stmt(std::move(cond), std::move(body));
}

ast::for_stmt parser::parse_for() {
  consume(tk::for_kw, "Expected 'for'");
  consume(tk::paren_open, "Expected '(' after 'for'");
  auto decl = parse_declaration();
  auto cond = parse_expr();
  consume(tk::semicolon, "Expected ';' after 'for' break condition");
  auto post = parse_expr();
  consume(tk::paren_close, "Expected ')' after 'for'");
  consume(tk::brace_open, "Expected '{' to start while-loop body");
  auto body = parse_statement();
  consume(tk::brace_close, "Expected '}' after while-loop body");

  return ast::for_stmt(std::move(decl), std::move(cond), std::move(post), std::move(body));
}

ast::if_stmt parser::parse_if() {
  consume(tk::if_kw, "Expected 'if'");

  consume(tk::paren_open, "Expected '(' after 'if'");
  auto cond = parse_expr();
  consume(tk::paren_close, "Expected ')' after condition");

  consume(tk::brace_open, "Expected '{' to start if-body");
  auto then = parse_statement();
  consume(tk::brace_close, "Expected '}' after if-body");

  return ast::if_stmt(std::move(cond), std::move(then));
}

ast::expr parser::parse_expr(int min_prec) {
  ast::expr left = parse_factor();

  while (true) {
    const auto op_kind = current_token_kind();
    auto op_opt = ast::binop_from_token_kind(op_kind);

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
  // literal
  if (current_token_kind() == tk::number) {
    const auto number = consume_and_extract_lexeme(tk::number, "Expected number");
    return {std::stoi(number)};
  }

  // unary
  if (const auto opt = ast::unop_from_token_kind(current_token_kind()); opt.has_value()) {
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
    // function call
    if (current_token_kind() == tk::paren_open) {
      consume(tk::paren_open, "Expected '('");
      consume(tk::paren_close, "Expected ')'");
      return std::make_unique<ast::call>(expr->identifier);
    }
    return expr;
  }

  throw std::runtime_error("Malformed factor");
}

void parser::consume(const token::token_kind kind, std::string_view error_msg) {
  if (current_token().kind() != kind) {
    throw std::runtime_error(error_msg.data());
  }

  advance();
}

std::string parser::consume_and_extract_lexeme(const token::token_kind kind, std::string_view error_msg) {
  if (current_token().kind() != kind) {
    throw std::runtime_error(error_msg.data());
  }
  auto lexeme = current_token().lexeme();
  advance();
  return lexeme;
}

void parser::expect_or_fail(const token::token_kind kind) const {
  if (const auto token = current_token(); token.kind() != kind) {
    throw std::runtime_error(std::format("expected '{}' found '{}'", kind, token));
  }
}

void parser::expect_or_fail(const token::token_kind kind, std::string_view msg) const {
  if (const auto token = current_token(); token.kind() != kind) {
    throw std::runtime_error(msg.data());
  }
}
