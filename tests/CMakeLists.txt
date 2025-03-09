add_executable(test_matrix test.cpp)
enable_testing()
include(GoogleTest)

target_include_directories(test_matrix PUBLIC ../inc/)
target_link_libraries(test_matrix GTest::gtest)

gtest_discover_tests(test_matrix)
