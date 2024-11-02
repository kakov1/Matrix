add_executable(test test.cpp)
enable_testing()
include(GoogleTest)

target_include_directories(test PUBLIC ../inc/)
target_link_libraries(test gtest::gtest)

gtest_discover_tests(test)