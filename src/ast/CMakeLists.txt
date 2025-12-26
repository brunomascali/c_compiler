file(GLOB ALL_SOURCES "*.cpp" "*.hpp")

add_library(ast_lib ${ALL_SOURCES})

set_target_properties(ast_lib PROPERTIES LINKER_LANGUAGE CXX)