#include "Assertions.h"

TEST(Vector, DefaultConstructor) {

    Vector<3> vector;

    assert_vector(vector, {0.0f, 0.0f, 0.0f});
}

TEST(Vector, Constructor) {

    Vector<3> vector(1.0f, 2.0f, 3.0f);

    assert_vector(vector, {1.0f, 2.0f, 3.0f});
}

TEST(Vector, ImplicitConstructor) {

    Vector<3> vector = { 1.0f, 2.0f, 3.0f };

    assert_scalar(vector[0], 1.0f);
    assert_scalar(vector[1], 2.0f);
    assert_scalar(vector[2], 3.0f);
}

TEST(Vector, Indexing) {

    Vector<3> vector;

    for (std::size_t index = 0; index < 3; index++) {
        vector[index] = index;
    }

    assert_vector(vector, {0.0f, 1.0f, 2.0f});
}

TEST(Vector, Negation) {

    Vector<3> vector(1.0f, -2.0f, 3.0f);
    Vector<3> negative = -vector;

    assert_vector(negative, {-1.0f, 2.0f, -3.0f});
}

TEST(Vector, Addition) {

    Vector<3> first(1.0f, 2.0f, 3.0f);
    Vector<3> second(4.0f, 5.0f, 6.0f);
    Vector<3> sum = first + second;

    assert_vector(sum, {5.0f, 7.0f, 9.0f});
}

TEST(Vector, Subtraction) {

    Vector<3> first(1.0f, 2.0f, -3.0f);
    Vector<3> second(4.0f, -5.0f, 6.0f);
    Vector<3> difference = first - second;

    assert_vector(difference, {-3.0f, 7.0f, -9.0f});
}

TEST(Vector, Multiplication) {

    Vector<3> first(1.0f, 2.0f, -3.0f);
    Vector<3> second(4.0f, -5.0f, 6.0f);
    Vector<3> product = first * second;

    assert_vector(product, {4.0f, -10.0f, -18.0f});
}

TEST(Vector, Division) {

    Vector<3> first(1.0f, 2.0f, -3.0f);
    Vector<3> second(4.0f, -5.0f, 6.0f);
    Vector<3> fraction = first / second;

    assert_vector(fraction, {0.25f, -0.4f, -0.5f});
}

TEST(Vector, DivisionByZero) {

    Vector<3> vector(1.0f, -1.0f, 0.0f);
    Vector<3> zero;
    Vector<3> fraction = vector / zero;

    assert_inf(fraction[0]);
    assert_inf(fraction[1]);
    assert_nan(fraction[2]);
}

TEST(Vector, ScalarMultiplication) {

    Vector<3> vector(1.0f, 0.0f, -3.0f);
    Vector<3> product = vector * 2.5f;

    assert_vector(product, {2.5f, 0.0f, -7.5f});
}

TEST(Vector, ScalarDivision) {

    Vector<3> vector(1.0f, 2.0f, -3.0f);
    Vector<3> product = vector / 2.0f;

    assert_vector(product, {0.5f, 1.0f, -1.5f});
}

TEST(Vector, ScalarDivisionByZero) {

    Vector<3> vector(1.0f, -1.0f, 0.0f);
    Vector<3> fraction = vector / 0.0f;

    assert_inf(fraction[0]);
    assert_inf(fraction[1]);
    assert_nan(fraction[2]);
}

TEST(Vector, Iteration) {

    Vector<3> vector(0.0f, 1.0f, 2.0f);

    for (auto & component : vector) {
        component *= 2.0f;
    }

    assert_vector(vector, {0.0f, 2.0f, 4.0f});
}