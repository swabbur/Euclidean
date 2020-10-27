#include "Assertions.hpp"

TEST(Vector, Alias) {
    Vector<3> vector;
}

TEST(Vector, Zeros) {

    Vector<3> vector = Vector<3>::zeros();

    assert_scalar(vector[0], 0.0f);
    assert_scalar(vector[1], 0.0f);
    assert_scalar(vector[2], 0.0f);
}

TEST(Vector, Ones) {

    Vector<3> vector = Vector<3>::ones();

    assert_scalar(vector[0], 1.0f);
    assert_scalar(vector[1], 1.0f);
    assert_scalar(vector[2], 1.0f);
}

TEST(Vector, DefaultConstructor) {

    Vector<3> vector;

    assert_scalar(vector[0], 0.0f);
    assert_scalar(vector[1], 0.0f);
    assert_scalar(vector[2], 0.0f);
}

TEST(Vector, ExplicitConstructor) {

    Vector<3> vector(1.0f, 2.0f, 3.0f);

    assert_scalar(vector[0], 1.0f);
    assert_scalar(vector[1], 2.0f);
    assert_scalar(vector[2], 3.0f);
}

TEST(Vector, ImplicitConstructor) {

    Vector<3> vector = { 1.0f, 2.0f, 3.0f };

    assert_scalar(vector[0], 1.0f);
    assert_scalar(vector[1], 2.0f);
    assert_scalar(vector[2], 3.0f);
}

TEST(Vector, Composition) {

    Vector<5> vector(1.0f, 2.0f, Vector<2>(3.0f, 4.0f), 5.0f);

    assert_vector(vector, { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f });
}

TEST(Vector, Assignment) {

    Vector<3> first;
    Vector<3> second(1.0f, 2.0f, 3.0f);
    first = second;

    assert_vector(first, second);
}

TEST(Vector, Indexing) {

    Vector<3> vector;

    for (std::size_t index = 0; index < 3; index++) {
        vector[index] = index;
    }

    assert_vector(vector, { 0.0f, 1.0f, 2.0f });
}

TEST(Vector, Negation) {

    Vector<3> vector(-1.0f, 0.0f, 1.0f);
    Vector<3> negative = -vector;

    assert_vector(negative, { 1.0f, 0.0f, -1.0f });
}

TEST(Vector, Addition) {

    Vector<4> first(1.0f, -3.0f, 5.0f, -7.0f);
    Vector<4> second(2.0f, 4.0f, -6.0f, -8.0f);
    Vector<4> sum = first + second;

    assert_vector(sum, { 3.0f, 1.0f, -1.0f, -15.0f });
}

TEST(Vector, Subtraction) {

    Vector<4> first(1.0f, -3.0f, 5.0f, -7.0f);
    Vector<4> second(2.0f, 4.0f, -6.0f, -8.0f);
    Vector<4> difference = first - second;

    assert_vector(difference, { -1.0f, -7.0f, 11.0f, 1.0f });
}

TEST(Vector, Multiplication) {

    Vector<4> first(1.0f, -3.0f, 5.0f, -7.0f);
    Vector<4> second(2.0f, 4.0f, -6.0f, -8.0f);
    Vector<4> product = first * second;

    assert_vector(product, { 2.0f, -12.0f, -30.0f, 56.0f });
}

TEST(Vector, Division) {

    Vector<4> first(1.0f, -3.0f, 5.0f, -7.0f);
    Vector<4> second(2.0f, 4.0f, -6.0f, -8.0f);
    Vector<4> fraction = first / second;

    assert_vector(fraction, { 0.5f, -0.75f, -(5.0f / 6.0f), 0.875f });
}

TEST(Vector, DivisionByZero) {

    Vector<3> vector(-1.0f, 0.0f, 1.0f);
    Vector<3> zero;
    Vector<3> fraction = vector / zero;

    assert_inf(fraction[0]);
    assert_nan(fraction[1]);
    assert_inf(fraction[2]);
}

TEST(Vector, ScalarMultiplicationNegative) {

    Vector<3> vector(-1.0f, 0.0f, 1.0f);
    Vector<3> product = vector * -2.0f;

    assert_vector(product, {2.0f, 0.0f, -2.0f});
}

TEST(Vector, ScalarMultiplicationZero) {

    Vector<3> vector(-1.0f, 0.0f, 1.0f);
    Vector<3> product = vector * 0.0f;

    assert_vector(product, {0.0f, 0.0f, 0.0f});
}

TEST(Vector, ScalarMultiplicationPositive) {

    Vector<3> vector(-1.0f, 0.0f, 1.0f);
    Vector<3> product = vector * 2.0f;

    assert_vector(product, {-2.0f, 0.0f, 2.0f});
}

TEST(Vector, ScalarDivisionNegative) {

    Vector<3> vector(-1.0f, 0.0f, 1.0f);
    Vector<3> product = vector / -2.0f;

    assert_vector(product, {0.5f, 0.0f, -0.5f});
}

TEST(Vector, ScalarDivisionZero) {

    Vector<3> vector(-1.0f, 0.0f, 1.0f);
    Vector<3> fraction = vector / 0.0f;

    assert_inf(fraction[0]);
    assert_nan(fraction[1]);
    assert_inf(fraction[2]);
}

TEST(Vector, ScalarDivisionPositive) {

    Vector<3> vector(-1.0f, 0.0f, 1.0f);
    Vector<3> product = vector / 2.0f;

    assert_vector(product, {-0.5f, 0.0f, 0.5f});
}

TEST(Vector, Iteration) {

    Vector<3> vector(1.0f, 2.0f, 3.0f);

    for (auto & component : vector) {
        component *= 2.0f;
    }

    assert_vector(vector, {2.0f, 4.0f, 6.0f});
}
