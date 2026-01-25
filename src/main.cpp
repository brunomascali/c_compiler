#include <asm/stack_frame.hpp>
#include <filesystem>
#include <lexer/lexer.hpp>
#include <parser/parser.hpp>
#include <print>
#include <ranges>
#include <utils/file.hpp>

#include "asm/asm_emitter.hpp"
#include "ast_printer.hpp"
#include "ir/ir_generator.hpp"
#include "ir_printer.hpp"

int main(const int argc, char** argv) {
  if (argc == 1) {
    throw std::invalid_argument("No arguments provided");
  }

  const auto source_code = utils::file_reader::read_all(argv[1]);
  const auto tokens = lexer(source_code).tokenize();
  std::println("found {} tokens", tokens.size());
  for (const auto& token : tokens) std::println("{}", token);

  const auto ast = parser(tokens).parse();
  print_node(ast);

  const auto ir_instructions = ir::generator::generate(ast);
  ir::print(ir_instructions);

  auto asm_emitter = x86::asm_emitter();
  utils::file_writer writer("out.s");

  for (const auto& ir_function : ir_instructions.functions) {
    for (const auto& ir_instruction : ir_function.instructions) {
      for (const auto& instruction : asm_emitter.emit(ir_instruction)) {
        writer.write_line(x86::to_string(instruction));
      }
    }
  }

  writer.write_line(".section .note.GNU-stack,\"\",@progbits\n");

  return 0;
}
