#include "Assertions.hpp"

TEST(Matrix, Identity) {

    Matrix<2, 2> matrix = Matrix<2, 2>::identity();

    assert_matrix(matrix, {
        1.0f, 0.0f,
        0.0f, 1.0f
    });
}

TEST(Matrix, DefaultConstructor) {

    Matrix<2, 2> matrix;

    assert_scalar(matrix[0][0], 0.0f);
    assert_scalar(matrix[0][1], 0.0f);
    assert_scalar(matrix[1][0], 0.0f);
    assert_scalar(matrix[1][1], 0.0f);
}

TEST(Matrix, ExplicitConstructor) {

    Matrix<2, 2> matrix(1.0f, 2.0f, 3.0f, 4.0f);

    assert_scalar(matrix[0][0], 1.0f);
    assert_scalar(matrix[0][1], 2.0f);
    assert_scalar(matrix[1][0], 3.0f);
    assert_scalar(matrix[1][1], 4.0f);
}

TEST(Matrix, ImplicitConstructor) {

    Matrix<2, 2> matrix = {
            1.0f, 2.0f,
            3.0f, 4.0f
    };

    assert_scalar(matrix[0][0], 1.0f);
    assert_scalar(matrix[0][1], 2.0f);
    assert_scalar(matrix[1][0], 3.0f);
    assert_scalar(matrix[1][1], 4.0f);
}

TEST(Matrix, Assignment) {

    Matrix<2, 2> first;
    Matrix<2, 2> second(1.0f, 2.0f, 3.0f, 4.0f);
    first = second;

    assert_matrix(first, second);
}


TEST(Matrix, Indexing) {

    Matrix<2, 2> matrix;

    for (std::size_t m = 0; m < 2; m++) {
        for (std::size_t n = 0; n < 2; n++) {
            matrix[m][n] = (2.0f * m) + n + 1;
        }
    }

    assert_matrix(matrix, {
            1.0f, 2.0f,
            3.0f, 4.0f
    });
}

TEST(Matrix, Negation) {

    Matrix<2, 2> matrix(-1.0f, 0.0f, 0.0f, 1.0f);
    Matrix<2, 2> negative = -matrix;

    assert_matrix(negative, { 1.0f, 0.0f, 0.0f, -1.0f });
}

TEST(Matrix, Addition) {

    Matrix<2, 2> first(1.0f, -3.0f, 5.0f, -7.0f);
    Matrix<2, 2> second(2.0f, 4.0f, -6.0f, -8.0f);
    Matrix<2, 2> sum = first + second;

    assert_matrix(sum, { 3.0f, 1.0f, -1.0f, -15.0f });
}

TEST(Matrix, Subtraction) {

    Matrix<2, 2> first(1.0f, -3.0f, 5.0f, -7.0f);
    Matrix<2, 2> second(2.0f, 4.0f, -6.0f, -8.0f);
    Matrix<2, 2> difference = first - second;

    assert_matrix(difference, { -1.0f, -7.0f, 11.0f, 1.0f });
}

TEST(Matrix, Multiplication) {

    Matrix<2, 2> first(1.0f, -3.0f, 5.0f, -7.0f);
    Matrix<2, 2> second(2.0f, 4.0f, -6.0f, -8.0f);
    Matrix<2, 2> product = first * second;

    assert_matrix(product, { 2.0f, -12.0f, -30.0f, 56.0f });
}

TEST(Matrix, Division) {

    Matrix<2, 2> first(1.0f, -3.0f, 5.0f, -7.0f);
    Matrix<2, 2> second(2.0f, 4.0f, -6.0f, -8.0f);
    Matrix<2, 2> fraction = first / second;

    assert_matrix(fraction, { 0.5f, -0.75f, -(5.0f / 6.0f), 0.875f });
}

TEST(Matrix, DivisionByZero) {

    Matrix<2, 2> matrix(-1.0f, 0.0f, 0.0f, 1.0f);
    Matrix<2, 2> zero;
    Matrix<2, 2> fraction = matrix / zero;

    assert_inf(fraction[0][0]);
    assert_nan(fraction[0][1]);
    assert_nan(fraction[1][0]);
    assert_inf(fraction[1][1]);
}

TEST(Matrix, ScalarMultiplicationNegative) {

    Matrix<2, 2> matrix(-1.0f, 0.0f, 0.0f, 1.0f);
    Matrix<2, 2> product = matrix * -2.0f;

    assert_matrix(product, {2.0f, 0.0f, 0.0f, -2.0f});
}

TEST(Matrix, ScalarMultiplicationZero) {

    Matrix<2, 2> matrix(-1.0f, 0.0f, 0.0f, 1.0f);
    Matrix<2, 2> product = matrix * 0.0f;

    assert_matrix(product, {0.0f, 0.0f, 0.0f, 0.0f});
}

TEST(Matrix, ScalarMultiplicationPositive) {

    Matrix<2, 2> matrix(-1.0f, 0.0f, 0.0f, 1.0f);
    Matrix<2, 2> product = matrix * 2.0f;

    assert_matrix(product, {-2.0f, 0.0f, 0.0f, 2.0f});
}

TEST(Matrix, ScalarDivisionNegative) {

    Matrix<2, 2> matrix(-1.0f, 0.0f, 0.0f, 1.0f);
    Matrix<2, 2> product = matrix / -2.0f;

    assert_matrix(product, {0.5f, 0.0f, 0.0f, -0.5f});
}

TEST(Matrix, ScalarDivisionZero) {

    Matrix<2, 2> matrix(-1.0f, 0.0f, 0.0f, 1.0f);
    Matrix<2, 2> fraction = matrix / 0.0f;

    assert_inf(fraction[0][0]);
    assert_nan(fraction[0][1]);
    assert_nan(fraction[1][0]);
    assert_inf(fraction[1][1]);
}

TEST(Matrix, ScalarDivisionPositive) {

    Matrix<2, 2> matrix(-1.0f, 0.0f, 0.0f, 1.0f);
    Matrix<2, 2> product = matrix / 2.0f;

    assert_matrix(product, {-0.5f, 0.0f, 0.0f, 0.5f});
}

TEST(Matrix, Iteration) {

    Matrix<2, 2> matrix(1.0f, 2.0f, 3.0f, 4.0f);

    for (auto & row : matrix) {
        for (auto & component : row) {
            component *= 2.0f;
        }
    }

    assert_matrix(matrix, {2.0f, 4.0f, 6.0f, 8.0f});
}
