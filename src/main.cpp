#include <print>
#include <filesystem>
#include <utils/file.hpp>
#include <lexer/lexer.hpp>
#include "parser/parser.hpp"

int main(const int argc, char** argv) {
    if (argc == 1) {
        throw std::invalid_argument("No arguments provided");
    }

    const auto source_code = utils::file::read(argv[1]);
    const auto tokens = lexer(source_code).tokenize();

    std::println("found {} tokens", tokens.size());
    for (const auto& token : tokens) std::println("{}", token);

    const auto parser = ::parser(tokens).parse();
    return 0;
}
