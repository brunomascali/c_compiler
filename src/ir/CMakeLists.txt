file(GLOB ALL_SOURCES "*.cpp" "*.hpp")

add_library(ir_lib ${ALL_SOURCES}
        return.hpp
        function.hpp)
target_include_directories(ir_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})