add_subdirectory(utils)
add_subdirectory(lexer)

add_executable(c_compiler main.cpp)
target_link_libraries(c_compiler PRIVATE utils_lib)
target_link_libraries(c_compiler PRIVATE lexer_lib)
