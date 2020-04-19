#include "Assertions.h"

void assert_nan(float scalar) {
    ASSERT_TRUE(std::isnan(scalar)) << "Expected component to be 'inf'";
}

void assert_inf(float scalar) {
    ASSERT_TRUE(std::isinf(scalar)) << "Expected component to be 'inf'";
}

void assert_scalar(float actual, float expected) {
    ASSERT_FLOAT_EQ(actual, expected);
}
