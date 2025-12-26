#include <print>
#include <filesystem>
#include <utils/file.hpp>

int main(const int argc, char** argv) {
    if (argc == 1) {
        throw std::invalid_argument("No arguments provided");
    }

    auto content = utils::file::read(argv[1]);
    std::println("{}", content);
    return 0;
}