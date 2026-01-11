#ifndef C_COMPILER_LEXER_HPP
#define C_COMPILER_LEXER_HPP

#include <generator>
#include <regex>
#include <string>
#include <utility>
#include <vector>

#include "token.hpp"

struct token_rule
{
  token::token_kind kind;
  std::string pattern;
};

class lexer {
 public:
  explicit lexer(std::string source) : m_source(std::move(source)), m_index(0) {
    const std::vector<std::pair<token::token_kind, std::string> > rules = {
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
      {token::token_kind::hyphen, "-"},
      {token::token_kind::plus, "\\+"},
      {token::token_kind::asterisk, "\\*"},
      {token::token_kind::slash, "\\/"},
      {token::token_kind::percent, "%"},
    };
    std::string combined_pattern;
    for (const auto &[kind, pattern] : rules) {
      combined_pattern += "(" + pattern + ")|";
      m_kinds.push_back(kind);
    }
    combined_pattern.pop_back();

    m_regex = std::regex(combined_pattern, std::regex::optimize);
  }

  std::generator<token> foo() {
    const auto begin = std::sregex_iterator(m_source.begin(), m_source.end(), m_regex);
    const auto end = std::sregex_iterator();

    for (auto i = begin; i != end; ++i) {
      std::smatch match = *i;

      for (size_t j = 1; j < match.size(); ++j) {
        if (match[j].matched) {
          co_yield token(m_kinds[j - 1], match.str());
          // tokens.emplace_back(m_kinds[j - 1], match.str());
          break;
        }
      }
    }
  }

  // struct Iterator
  // {
  //   using iterator_category = std::forward_iterator_tag;
  //   using difference_type   = std::ptrdiff_t;
  //   using value_type        = token;
  //   using pointer           = value_type*;
  //   using reference         = value_type&;
  //
  //   explicit Iterator(const pointer ptr) : m_ptr(ptr) {}
  //
  //   reference operator*() const { return *m_ptr; }
  //   pointer operator->() const { return m_ptr; }
  //
  //   Iterator& operator++() { m_ptr++; return *this; }
  //   Iterator operator++(int) { const Iterator tmp = *this; ++(*this); return tmp; }
  //
  //   friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
  //   friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };
  //
  // private:
  //   pointer m_ptr;
  // };


  std::generator<token> tokenize_lazy();

 private:
  std::string m_source;
  std::regex m_regex;
  std::vector<token::token_kind> m_kinds;
  std::size_t m_index;
};

#endif  // C_COMPILER_LEXER_HPP
