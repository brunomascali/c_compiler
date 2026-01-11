#ifndef C_COMPILER_PIPELINE_HPP
#define C_COMPILER_PIPELINE_HPP

#include <algorithm>
#include <filesystem>
#include <parser/parser.hpp>

namespace fs = std::filesystem;

/*
 lexer <- parser -> ir -> ast
 */

class pipeline {
 public:
  explicit pipeline(parser& p) : m_parser(std::move(p)) {}

  void compile(const fs::path& src_code_path);

 private:
  parser m_parser;
};


#endif  // C_COMPILER_PIPELINE_HPP
