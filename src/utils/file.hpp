#ifndef C_COMPILER_FILE_H
#define C_COMPILER_FILE_H

#include <string>
#include <string_view>
#include <filesystem>

namespace utils {
    namespace fs = std::filesystem;
    class file {
    public:
        static std::string read(const fs::path& filepath);
        static bool write(const fs::path &filepath, std::string_view content);
    };
}

#endif //C_COMPILER_FILE_H