#include <iostream>

#include "parser.hpp"
#include "gtest/gtest.h"

TEST(PARSER_TESTS, MINIMAL_PROGRAM)
{
  const std::vector tokens {
    token(token::token_kind::int_kw, "int"),
    token(token::token_kind::identifier, "main"),
    token(token::token_kind::paren_open),
    token(token::token_kind::void_kw),
    token(token::token_kind::paren_close),
    token(token::token_kind::brace_open),
    token(token::token_kind::return_kw),
    token(token::token_kind::number, "0"),
    token(token::token_kind::semicolon),
    token(token::token_kind::brace_close)
  };

  auto parser = ::parser(tokens).parse();

}