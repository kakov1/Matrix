#include "matrix.hpp"
#include "real_numbers.hpp"
#include <cstddef>
#include <fstream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>
#include <vector>

using hwm::Matrix;

template <typename T> class EteTests : public testing::Test {
protected:
  T test(std::size_t test_number) {
    std::ifstream test_file("../../tests/tests/" + std::to_string(test_number) +
                            "test.txt");

    test_file.exceptions(std::ifstream::failbit);

    int size;
    T buf;
    std::vector<T> numbers;

    test_file >> size;

    for (int i = 0; i < size * size; i++) {
      test_file >> buf;
      numbers.push_back(buf);
    }

    Matrix<T> mtrx{size, size, numbers.begin(), numbers.end()};

    return mtrx.determinant();
  }

  T get_answer(int test_number) {
    T answer;

    std::ifstream answer_file("../../tests/tests/" +
                              std::to_string(test_number) + "answer.txt");

    answer_file.exceptions(std::ifstream::failbit);

    answer_file >> answer;

    return answer;
  }
};

template <typename T> class EteTestsFloats : public EteTests<T> {};

using all_types = ::testing::Types<int, long, double, float>;
using float_types = ::testing::Types<double>;

TYPED_TEST_SUITE(EteTests, all_types);
TYPED_TEST_SUITE(EteTestsFloats, float_types);

class InterfaceTests : public testing::Test {
protected:
  Matrix<int> mtrx;
  std::vector<int> buf;

  InterfaceTests() {
    for (int i = 1; i < 10; i++) {
      buf.push_back(i);
    }

    mtrx = Matrix<int>{3, 3, buf.begin(), buf.end()};
  }
};

TEST_F(InterfaceTests, TestConstructors) {
  Matrix<int> mtrx_copy1 = mtrx;
  Matrix<int> mtrx_copy2;
  Matrix<int> mtrx2{100, 100, 1};

  mtrx = mtrx;
  mtrx = std::move(mtrx);

  ASSERT_TRUE(mtrx == mtrx_copy1);
  ASSERT_FALSE(mtrx == mtrx_copy2);
  ASSERT_FALSE(mtrx == mtrx2);

  Matrix<int> mtrx_copy4 = std::move(mtrx_copy1);
  Matrix<int> mtrx_copy5 = std::move(mtrx2);

  ASSERT_TRUE(mtrx == mtrx_copy4);
  ASSERT_FALSE(mtrx == mtrx_copy5);
}

TEST_F(InterfaceTests, TestAssign) {
  Matrix<int> mtrx_copy1;
  Matrix<int> mtrx2{50, 50, 2};
  Matrix<int> mtrx_copy2;

  mtrx_copy1 = mtrx;
  mtrx_copy2 = mtrx2;

  ASSERT_TRUE(mtrx == mtrx_copy1);
  ASSERT_FALSE(mtrx == mtrx_copy2);

  Matrix<int> mtrx_copy3 = std::move(mtrx_copy1);
  Matrix<int> mtrx_copy4 = std::move(mtrx_copy2);

  ASSERT_TRUE(mtrx == mtrx_copy3);
  ASSERT_FALSE(mtrx == mtrx_copy4);
}

TYPED_TEST(EteTestsFloats, test_float_types) {
  for (int i = 14; i <= 20; ++i)
    ASSERT_TRUE(hwm::is_equal_floats(this->test(i), this->get_answer(i)));
}

TYPED_TEST(EteTests, test_all_types) {
  for (int i = 1; i <= 13; ++i)
    ASSERT_TRUE(hwm::is_equal_floats(this->test(i), this->get_answer(i)));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
