#ifndef C_COMPILER_PIPELINE_HPP
#define C_COMPILER_PIPELINE_HPP

#include <filesystem>
#include <ir/ir_generator.hpp>
#include <lexer/lexer.hpp>
#include <parser/parser.hpp>
#include <asm/passes/legalizer.hpp>

class pipeline {
 public:
  pipeline() = default;
  pipeline(lexer lexer, parser parser, ir_generator ir_generator) :
      m_lexer(std::move(lexer)), m_parser(std::move(parser)), m_ir_generator(std::move(ir_generator)) {};

  void run(const std::filesystem::path& src_file, const std::filesystem::path& dst_file);

 private:
  lexer m_lexer{};
  parser m_parser{};
  ir_generator m_ir_generator{};
  x86::legalizer m_legalizer{};
};

#endif  // C_COMPILER_PIPELINE_HPP
