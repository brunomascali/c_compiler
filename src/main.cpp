#include <print>
#include <filesystem>
#include <utils/file.hpp>
#include <lexer/lexer.hpp>
#include <parser/parser.hpp>

#include "asm/asm_emitter.hpp"
#include "ir/ir.hpp"

int main(const int argc, char** argv) {
    if (argc == 1) {
        throw std::invalid_argument("No arguments provided");
    }

    const auto source_code = utils::file::read(argv[1]);
    const auto tokens = lexer(source_code).tokenize();

    std::println("found {} tokens", tokens.size());
    for (const auto& token : tokens) std::println("{}", token);

    auto ast = parser(tokens).parse();

    const auto asm_instructions = asm_emitter().emit(ast);

    for (const auto& instruction : asm_emitter().emit(ast)) {
        std::println("{}", instructions_visitor(instruction));
    }

    std::vector<ir::instruction> ctx;
    ir::from_statement_node(ctx, std::move(ast.statements.back().body.back()));

    return 0;
}
