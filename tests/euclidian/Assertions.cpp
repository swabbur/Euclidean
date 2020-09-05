#include "Assertions.hpp"

void assert_false(bool expression) {
    ASSERT_FALSE(expression) << "Expected expression to be false";
}

void assert_nan(float scalar) {
    ASSERT_TRUE(std::isnan(scalar)) << "Expected component to be 'nan'";
}

void assert_inf(float scalar) {
    ASSERT_TRUE(std::isinf(scalar)) << "Expected component to be 'inf'";
}

void assert_scalar(float actual, float expected) {
    ASSERT_FLOAT_EQ(actual, expected);
}
