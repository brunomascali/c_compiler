#ifndef C_COMPILER_FILE_H
#define C_COMPILER_FILE_H

#include <filesystem>
#include <fstream>
#include <string>
#include <string_view>

namespace utils
{
  namespace fs = std::filesystem;

  class file_reader {
   public:
    static std::string read_all(const fs::path& filepath);
  };

  class file_writer {
   public:
    explicit file_writer(const fs::path& filepath) : m_stream(filepath) {
      if (!m_stream.is_open()) throw std::invalid_argument("Error opening file " + filepath.string());
    }

    void write_line(std::string_view line);

   private:
    std::ofstream m_stream;
  };
}  // namespace utils

#endif  // C_COMPILER_FILE_H
