#include <print>
#include <filesystem>
#include <utils/file.hpp>
#include <lexer/lexer.hpp>

int main(const int argc, char** argv) {
    if (argc == 1) {
        throw std::invalid_argument("No arguments provided");
    }

    const auto source_code = utils::file::read(argv[1]);
    const auto tokens = lexer(source_code).tokenize();

    std::println("found {} tokens", tokens.size());

    for (const auto& token : tokens) {
        std::print("'{}' ", token.lexeme());
    }
    return 0;
}