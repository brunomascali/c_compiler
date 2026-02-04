file(GLOB ALL_SOURCES "*.cpp" "*.hpp")

add_library(parser_lib ${ALL_SOURCES})
target_include_directories(parser_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})