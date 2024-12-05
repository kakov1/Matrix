#pragma once

#include <cmath>
#include <type_traits>
#include <iostream>

namespace hwm {
    template <typename FloatType>
    class Accuracy {
        public:
            static FloatType epsilon() { return 1e-8; }
    };

    template <>
    class Accuracy<long double> {
        public:
            static long double epsilon() { return 1e-15; }
    };

    template <>
    class Accuracy<double> {
        public:
            static double epsilon() { return 1e-8; }
    };

    template <>
    class Accuracy<float> {
        public:
            static double epsilon() { return 1e-5; }
    };

    template <>
    class Accuracy<int> {
        public:
            static double epsilon() { return 0; }
    };

    template <typename FloatType>
    bool is_equal_floats(FloatType a, FloatType b) {
        if (std::is_integral_v<FloatType>)
            return a == b;
        else
            return std::fabs(a - b) < Accuracy<FloatType>::epsilon();
    }

    template <typename FloatType>
    bool is_less(FloatType a, FloatType b) {
        if (std::is_integral_v<FloatType>)
            return a < b;
        else
            return a - b < -Accuracy<FloatType>::epsilon();
    }

    template <typename FloatType>
    bool is_bigger(FloatType a, FloatType b) {
        return a - b > Accuracy<FloatType>::epsilon();
    }

    template <typename FloatType>
    bool is_zero(FloatType a) {
        if (std::is_integral_v<FloatType>)
            return a == 0;
        else
            return std::fabs(a) < Accuracy<FloatType>::epsilon();
    }
}
