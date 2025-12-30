file(GLOB ALL_SOURCES "*.cpp")

add_library(ir_lib ${ALL_SOURCES})
target_include_directories(ir_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})