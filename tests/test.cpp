#include "matrix.hpp"
#include "real_numbers.hpp"
#include <fstream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <list>
#include <string>
#include <vector>
#include <iomanip>

const int OPEN_ERROR = -1;

double get_answer(int test_number) {
    double answer;

    std::fstream answer_file("../../tests/tests/" +
                             std::to_string(test_number) + "answer.txt");

    if (answer_file.fail()) {
        throw OPEN_ERROR;
    }

    answer_file >> answer;

    return answer;
}

double test(int test_number) {
    std::fstream test_file("../../tests/tests/" + std::to_string(test_number) +
                           "test.txt");

    if (test_file.fail()) {
        throw OPEN_ERROR;
    }

    std::cin.rdbuf(test_file.rdbuf());

    int size;
    double buf;
    std::vector<double> numbers;

    std::cin >> size;

    for (int i = 0; i < size * size; i++) {
        std::cin >> buf;
        numbers.push_back(buf);
    }

    Matrix::Matrix<double> matrix{size, size, numbers.begin(), numbers.end()};

    return matrix.determinant();
}

TEST(tests, test1) {
    ASSERT_TRUE(Matrix::is_equal_floats(test(1), get_answer(1)));
}

TEST(tests, test2) {
    ASSERT_TRUE(Matrix::is_equal_floats(test(2), get_answer(2)));
}

TEST(tests, test3) {
    ASSERT_TRUE(Matrix::is_equal_floats(test(3), get_answer(3)));
}

TEST(tests, test4) {
    ASSERT_TRUE(Matrix::is_equal_floats(test(4), get_answer(4)));
}

TEST(tests, test5) {
    ASSERT_TRUE(Matrix::is_equal_floats(test(5), get_answer(5)));
}

TEST(tests, test6) {
    ASSERT_TRUE(Matrix::is_equal_floats(test(6), get_answer(6)));
}

TEST(tests, test7) {
    ASSERT_TRUE(Matrix::is_equal_floats(test(7), get_answer(7)));
}

TEST(tests, test8) {
    ASSERT_TRUE(Matrix::is_equal_floats(test(8), get_answer(8)));
}

TEST(tests, test9) {
    ASSERT_TRUE(Matrix::is_equal_floats(test(9), get_answer(9)));
}

TEST(tests, test10) {
    ASSERT_TRUE(Matrix::is_equal_floats(test(10), get_answer(10)));
}

TEST(tests, test11) {
    ASSERT_TRUE(Matrix::is_equal_floats(test(11), get_answer(11)));
}

TEST(tests, test12) {
    ASSERT_TRUE(Matrix::is_equal_floats(test(12), get_answer(12)));
}

TEST(tests, test13) {
    ASSERT_TRUE(Matrix::is_equal_floats(test(13), get_answer(13)));
}

TEST(tests, test14) {
    ASSERT_TRUE(Matrix::is_equal_floats(test(14), get_answer(14)));
}

TEST(tests, test15) {
    ASSERT_TRUE(Matrix::is_equal_floats(test(15), get_answer(15)));
}

TEST(tests, test16) {
    ASSERT_TRUE(Matrix::is_equal_floats(test(16), get_answer(16)));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
