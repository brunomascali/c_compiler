#include "lexer.hpp"

#include <regex>

std::vector<token> lexer::tokenize() {
  std::vector<token> tokens;
  const auto begin = std::sregex_iterator(m_source.begin(), m_source.end(), m_regex);
  const auto end = std::sregex_iterator();

  for (auto i = begin; i != end; ++i) {
    std::smatch match = *i;

    for (size_t j = 1; j < match.size(); ++j) {
      if (match[j].matched) {
        tokens.emplace_back(m_kinds[j - 1], match.str());
        break;
      }
    }
  }
  return tokens;
}