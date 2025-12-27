add_executable(lexer_tests test_lexer.cpp)

target_link_libraries(lexer_tests
        PRIVATE
        lexer_lib
        utils_lib
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lexer_tests)