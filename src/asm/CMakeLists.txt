file(GLOB_RECURSE ALL_SOURCES
        CONFIGURE_DEPENDS
        "*.cpp"
        "*.hpp"
)

add_library(asm_lib STATIC ${ALL_SOURCES})

target_include_directories(asm_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})