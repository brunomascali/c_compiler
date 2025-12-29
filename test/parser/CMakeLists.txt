add_executable(parser_tests test_parser.cpp)

target_link_libraries(parser_tests
        PRIVATE
        parser_lib
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(parser_tests)