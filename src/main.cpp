#include <pipeline/pipeline.hpp>

int main(const int argc, char** argv) {
  if (argc == 1) {
    throw std::invalid_argument("No arguments provided");
  }

  pipeline().run(argv[1], "out.s");
  return 0;
}