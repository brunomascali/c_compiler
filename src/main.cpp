#include <filesystem>
#include <ranges>
#include <utils/file.hpp>
#include <lexer/lexer.hpp>
#include <parser/parser.hpp>
#include <print>

#include "asm/asm_emitter.hpp"
#include "ir/ir_generator.hpp"

int main(const int argc, char** argv) {
    if (argc == 1) {
        throw std::invalid_argument("No arguments provided");
    }

    const auto source_code = utils::file::read(argv[1]);
    const auto tokens = lexer(source_code).tokenize();
    const auto ast = parser(tokens).parse();

    std::println("found {} tokens", tokens.size());
    for (const auto& token : tokens) std::println("{}", token);

    const auto ir_instructions = ir::ir_generator(ast).instructions();

    auto ctx = x86::codegen_context();
    auto asm_emitter = x86::asm_emitter(ctx);
    const auto asm_instructions =
        ir_instructions
        | std::ranges::views::transform([&](const auto& ir) {
                return asm_emitter.emit(ir);
            })
        | std::ranges::views::join
        | std::ranges::to<std::vector<x86::instruction_t>>();

    std::string result;
    for (const auto& inst : asm_instructions) {
        result += x86::to_string(inst);
        result += '\n';
    }
    result += ".section .note.GNU-stack,\"\",@progbits\n";

    if (not utils::file::write("out.s", result)) {
        throw std::runtime_error("Could not write to file");
    }

    return 0;
}
