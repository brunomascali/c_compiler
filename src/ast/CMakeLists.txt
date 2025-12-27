file(GLOB ALL_SOURCES "*.cpp" "*.hpp")

add_library(ast_lib ${ALL_SOURCES})

set_target_properties(ast_lib PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(ast_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})