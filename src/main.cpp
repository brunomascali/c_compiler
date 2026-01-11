#include <parser/parser.hpp>
#include <pipeline/pipeline.hpp>
#include <utils/file.hpp>

int main(const int argc, char** argv) {
  if (argc == 1) {
    throw std::invalid_argument("No arguments provided");
  }

  const auto source_code = utils::file_reader::read_all(argv[1]);
  lexer lexer(source_code);
  parser parser(lexer);

  pipeline pipeline(parser);
}
