file(GLOB ALL_SOURCES "*.cpp")

add_library(utils_lib ${ALL_SOURCES})
target_include_directories(utils_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})