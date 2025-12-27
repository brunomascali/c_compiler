file(GLOB ALL_SOURCES "*.cpp")

add_library(lexer_lib ${ALL_SOURCES})
target_include_directories(lexer_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})