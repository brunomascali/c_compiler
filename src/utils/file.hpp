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
    };
}

#endif //C_COMPILER_FILE_H