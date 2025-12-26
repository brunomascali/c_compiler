#ifndef C_COMPILER_LEXER_HPP
#define C_COMPILER_LEXER_HPP

#include <regex>
#include <string>
#include <vector>
#include "token.hpp"

struct token_rule {
  token::token_kind kind;
  std::string pattern;
};

class lexer {
public:
  explicit lexer(const std::string &source) : m_source(source), m_index(0) {
    const std::vector<std::pair<token::token_kind, std::string>> rules = {
      {token::token_kind::int_kw,      "int\\b"},
      {token::token_kind::void_kw,     "void\\b"},
      {token::token_kind::return_kw,   "return\\b"},
      {token::token_kind::identifier,  "[a-zA-Z_][a-zA-Z0-9_]*"},
      {token::token_kind::number,      "[0-9]+"},
      {token::token_kind::paren_open,  "\\("},
      {token::token_kind::paren_close, "\\)"},
      {token::token_kind::brace_open,  "\\{"},
      {token::token_kind::brace_close, "\\}"},
      {token::token_kind::semicolon,   ";"}
    };
    std::string combined_pattern;
    for (const auto&[kind, pattern] : rules) {
      combined_pattern += "(" + pattern + ")|";
      m_kinds.push_back(kind);
    }
    combined_pattern.pop_back();

    m_regex = std::regex(combined_pattern, std::regex::optimize);
  }

  std::vector<token> tokenize();

private:
  std::string m_source;
  std::regex m_regex;
  std::vector<token::token_kind> m_kinds;
  std::size_t m_index;

  void skip_whitespace();
};

#endif //C_COMPILER_LEXER_HPP