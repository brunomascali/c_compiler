#include "pipeline.hpp"

#include <print>

#include "asm/asm_emitter.hpp"
#include "ast/ast_printer.hpp"
#include "ir/ir_printer.hpp"
#include "utils/file.hpp"

void pipeline::run(const std::filesystem::path& src_file, const std::filesystem::path& dst_file) {
  const auto source_code = utils::file_reader::read_all(src_file);
  auto tokens = m_lexer.tokenize(source_code);
  std::println("found {} tokens", tokens.size());
  for (const auto& token : tokens) std::println("{}", token);

  const auto ast = m_parser.parse(tokens);
  print_node(ast);

  const auto ir_instructions = ir_generator::generate(ast);
  ir::print(ir_instructions);

  auto asm_emitter = x86::asm_emitter();
  utils::file_writer writer(dst_file);

  for (const auto& ir_function : ir_instructions.functions) {
    for (const auto& ir_instruction : ir_function.instructions) {
      for (auto& instruction : asm_emitter.emit(ir_instruction)) {
        for (const auto& legalized_instruction : m_legalizer.run(instruction))
        writer.write_line(legalized_instruction.emit());
      }
    }
  }
  writer.write_line(".section .note.GNU-stack,\"\",@progbits\n");
}
