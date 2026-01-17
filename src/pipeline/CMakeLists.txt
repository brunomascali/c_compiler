file(GLOB ALL_SOURCES "*.cpp")

add_library(pipeline_lib ${ALL_SOURCES})
target_include_directories(pipeline_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})