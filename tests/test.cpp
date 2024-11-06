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

template <typename FloatType>
double test(int test_number) {
    std::fstream test_file("../../tests/tests/" + std::to_string(test_number) +
                           "test.txt");

    if (test_file.fail()) {
        throw OPEN_ERROR;
    }

    std::cin.rdbuf(test_file.rdbuf());

    int size;
    FloatType buf;
    std::vector<FloatType> numbers;

    std::cin >> size;

    for (int i = 0; i < size * size; i++) {
        std::cin >> buf;
        numbers.push_back(buf);
    }

    Matrix::Matrix<FloatType> matrix{size, size, numbers.begin(),
                                     numbers.end()};

    return matrix.determinant();
}

TEST(tests, test1) {
    ASSERT_TRUE(Matrix::is_equal_floats(test<int>(1), get_answer(1)));
}

TEST(tests, test2) {
    ASSERT_TRUE(Matrix::is_equal_floats(test<int>(2), get_answer(2)));
}

TEST(tests, test3) {
    ASSERT_TRUE(Matrix::is_equal_floats(test<int>(3), get_answer(3)));
}

TEST(tests, test4) {
    ASSERT_TRUE(Matrix::is_equal_floats(test<int>(4), get_answer(4)));
}

TEST(tests, test5) {
    ASSERT_TRUE(Matrix::is_equal_floats(test<int>(5), get_answer(5)));
}

TEST(tests, test6) {
    ASSERT_TRUE(Matrix::is_equal_floats(test<int>(6), get_answer(6)));
}

TEST(tests, test7) {
    ASSERT_TRUE(Matrix::is_equal_floats(test<int>(7), get_answer(7)));
}

TEST(tests, test8) {
    ASSERT_TRUE(Matrix::is_equal_floats(test<int>(8), get_answer(8)));
}

TEST(tests, test9) {
    ASSERT_TRUE(Matrix::is_equal_floats(test<double>(9), get_answer(9)));
}

TEST(tests, test10) {
    ASSERT_TRUE(Matrix::is_equal_floats(test<double>(10), get_answer(10)));
}

TEST(tests, test11) {
    ASSERT_TRUE(Matrix::is_equal_floats(test<double>(11), get_answer(11)));
}

TEST(tests, test12) {
    ASSERT_TRUE(Matrix::is_equal_floats(test<double>(12), get_answer(12)));
}

TEST(tests, test13) {
    ASSERT_TRUE(Matrix::is_equal_floats(test<double>(13), get_answer(13)));
}

TEST(tests, test14) {
    ASSERT_TRUE(Matrix::is_equal_floats(test<double>(14), get_answer(14)));
}

TEST(tests, test15) {
    ASSERT_TRUE(Matrix::is_equal_floats(test<double>(15), get_answer(15)));
}

TEST(tests, test16) {
    ASSERT_TRUE(Matrix::is_equal_floats(test<int>(16), get_answer(16)));
}

TEST(tests, test17) {
    ASSERT_TRUE(Matrix::is_equal_floats(test<int>(17), get_answer(17)));
}

TEST(tests, test18) {
    ASSERT_TRUE(Matrix::is_equal_floats(test<int>(18), get_answer(18)));
}

TEST(tests, test19) {
    ASSERT_TRUE(Matrix::is_equal_floats(test<int>(19), get_answer(19)));
}

TEST(tests, test20) {
    ASSERT_TRUE(Matrix::is_equal_floats(test<int>(20), get_answer(20)));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
