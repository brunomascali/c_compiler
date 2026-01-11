#include "pipeline.hpp"

#include "asm/asm_emitter.hpp"
#include "ir/ir.hpp"
#include "utils/file.hpp"

void pipeline::compile(const fs::path& src_code_path) {
  const auto source_code = utils::file_reader::read_all(src_code_path);
  const auto ast = m_parser.parse();
  const auto ir_instructions = ir_generator(ast).instructions();
  auto asm_emitter = x86::asm_emitter();

  utils::file_writer writer("out.s");

  for (const auto& ir_instruction : ir_instructions) {
    for (const auto asm_instructions = asm_emitter.emit(ir_instruction);
         const auto& asm_instruction : asm_instructions) {
      writer.write_line(x86::to_string(asm_instruction));
    }
  }
}
