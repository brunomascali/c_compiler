file(GLOB ALL_SOURCES "*.cpp" "*.hpp")

add_library(asm_lib ${ALL_SOURCES}
        binary.hpp
        cdq.hpp)

set_target_properties(asm_lib PROPERTIES LINKER_LANGUAGE CXX)