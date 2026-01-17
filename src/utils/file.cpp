#include <fstream>

#include "file.hpp"

std::string utils::file_reader::read_all(const fs::path &filepath) {
  if (!fs::exists(filepath)) {
    throw std::invalid_argument(std::format("File does not exist: {}", filepath.string()));
  }
  const auto size = fs::file_size(filepath);
  std::string content(size, '\0');
  std::ifstream in(filepath);
  in.read(std::addressof(content[0]), static_cast<long>(size));

  return content;
}

void utils::file_writer::write_line(const std::string_view line) {
  if (m_stream.is_open()) m_stream << line << '\n';
}
