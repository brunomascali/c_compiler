file(GLOB ALL_SOURCES "*.cpp" "*.hpp")

add_library(asm_lib ${ALL_SOURCES})

set_target_properties(asm_lib PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(asm_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})