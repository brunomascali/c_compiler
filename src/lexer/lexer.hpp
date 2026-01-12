#ifndef C_COMPILER_LEXER_HPP
#define C_COMPILER_LEXER_HPP

#include "token.hpp"
#include <regex>
#include <string>
#include <utility>
#include <vector>

struct token_rule {
  token::token_kind kind;
  std::string pattern;
};

class lexer {
public:
  explicit lexer(std::string source) : m_source(std::move(source)), m_index(0) {
    const std::vector<std::pair<token::token_kind, std::string>> rules = {
        {token::token_kind::int_kw, "int\\b"},
        {token::token_kind::void_kw, "void\\b"},
        {token::token_kind::return_kw, "return\\b"},
        {token::token_kind::identifier, "[a-zA-Z_][a-zA-Z0-9_]*"},
        {token::token_kind::number, "[0-9]+"},
        {token::token_kind::paren_open, "\\("},
        {token::token_kind::paren_close, "\\)"},
        {token::token_kind::brace_open, "\\{"},
        {token::token_kind::brace_close, "\\}"},
        {token::token_kind::semicolon, ";"},
        {token::token_kind::neq, "!="},
        {token::token_kind::lt, "<"},
        {token::token_kind::gt, ">"},
        {token::token_kind::le, "<="},
        {token::token_kind::ge, ">="},
        {token::token_kind::hyphen, "-"},
        {token::token_kind::plus, "\\+"},
        {token::token_kind::asterisk, "\\*"},
        {token::token_kind::slash, "\\/"},
        {token::token_kind::percent, "%"},
        {token::token_kind::negation, "!"},
        {token::token_kind::double_ampersand, "&&"},
        {token::token_kind::double_pipe, "\\|\\|"},
        {token::token_kind::double_eq, "=="},

    };
    std::string combined_pattern;
    for (const auto &[kind, pattern] : rules) {
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
};

#endif // C_COMPILER_LEXER_HPP
