#include "file.hpp"

#include <fstream>

std::string utils::file::read(const fs::path &filepath) {
  if (!fs::exists(filepath)) {
    throw std::invalid_argument(std::format("File does not exist: {}", filepath.string()));
  }
  const auto size = fs::file_size(filepath);
  std::string content(size, '\0');
  std::ifstream in(filepath);
  in.read(std::addressof(content[0]), static_cast<long>(size));

  return content;
}

bool utils::file::write(const fs::path &filepath, const std::string_view content) {
  std::ofstream out(filepath);
  out << content;
  out.close();
  return true;
}
