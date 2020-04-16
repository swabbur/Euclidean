#include <gtest/gtest.h>
#include <euclidian/Vector.hpp>
#include <cmath>

#define ASSERT_INF(component) ASSERT_TRUE(std::isinf(component)) << "Expected component to be 'inf'"

#define ASSERT_NAN(component) ASSERT_TRUE(std::isnan(component)) << "Expected component to be 'nan'"

#define ASSERT_VECTOR(vector, x, y, z) \
    ASSERT_FLOAT_EQ(vector[0], x); \
    ASSERT_FLOAT_EQ(vector[1], y); \
    ASSERT_FLOAT_EQ(vector[2], z)

TEST(Vector, DefaultConstructor) {

    Vector<3> vector;

    ASSERT_VECTOR(vector, 0.0f, 0.0f, 0.0f);
}

TEST(Vector, Constructor) {

    Vector<3> vector(1.0f, 2.0f, 3.0f);

    ASSERT_VECTOR(vector, 1.0f, 2.0f, 3.0f);
}

TEST(Vector, ImplicitConstructor) {

    Vector<3> vector = { 1.0f, 2.0f, 3.0f };

    ASSERT_VECTOR(vector, 1.0f, 2.0f, 3.0f);
}

TEST(Vector, Indexing) {

    Vector<3> vector;

    for (std::size_t index = 0; index < 3; index++) {
        vector[index] = index;
    }

    ASSERT_VECTOR(vector, 0.0f, 1.0f, 2.0f);
}

TEST(Vector, Negation) {

    Vector<3> vector(1.0f, -2.0f, 3.0f);
    Vector<3> negative = -vector;

    ASSERT_VECTOR(negative, -1.0f, 2.0f, -3.0f);
}

TEST(Vector, Addition) {

    Vector<3> first(1.0f, 2.0f, 3.0f);
    Vector<3> second(4.0f, 5.0f, 6.0f);
    Vector<3> sum = first + second;

    ASSERT_VECTOR(sum, 5.0f, 7.0f, 9.0f);
}

TEST(Vector, Subtraction) {

    Vector<3> first(1.0f, 2.0f, -3.0f);
    Vector<3> second(4.0f, -5.0f, 6.0f);
    Vector<3> difference = first - second;

    ASSERT_VECTOR(difference, -3.0f, 7.0f, -9.0f);
}

TEST(Vector, Multiplication) {

    Vector<3> first(1.0f, 2.0f, -3.0f);
    Vector<3> second(4.0f, -5.0f, 6.0f);
    Vector<3> product = first * second;

    ASSERT_VECTOR(product, 4.0f, -10.0f, -18.0f);
}

TEST(Vector, Division) {

    Vector<3> first(1.0f, 2.0f, -3.0f);
    Vector<3> second(4.0f, -5.0f, 6.0f);
    Vector<3> fraction = first / second;

    ASSERT_VECTOR(fraction, 0.25f, -0.4f, -0.5f);
}

TEST(Vector, DivisionByZero) {

    Vector<3> vector(1.0f, -1.0f, 0.0f);
    Vector<3> zero;
    Vector<3> fraction = vector / zero;

    ASSERT_INF(fraction[0]);
    ASSERT_INF(fraction[1]);
    ASSERT_NAN(fraction[2]);
}

TEST(Vector, ScalarMultiplication) {

    Vector<3> vector(1.0f, 0.0f, -3.0f);
    Vector<3> product = vector * 2.5f;

    ASSERT_VECTOR(product, 2.5f, 0.0f, -7.5f);
}

TEST(Vector, ScalarDivision) {

    Vector<3> vector(1.0f, 2.0f, -3.0f);
    Vector<3> product = vector / 2.0f;

    ASSERT_VECTOR(product, 0.5f, 1.0f, -1.5f);
}

TEST(Vector, ScalarDivisionByZero) {

    Vector<3> vector(1.0f, -1.0f, 0.0f);
    Vector<3> fraction = vector / 0.0f;

    ASSERT_INF(fraction[0]);
    ASSERT_INF(fraction[1]);
    ASSERT_NAN(fraction[2]);
}

TEST(Vector, Iteration) {

    Vector<3> vector(0.0f, 1.0f, 2.0f);

    for (auto & component : vector) {
        component *= 2.0f;
    }

    float expected = 0;
    for (auto component : vector) {
        ASSERT_FLOAT_EQ(component, expected);
        expected += 2.0f;
    }
}