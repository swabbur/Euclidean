#include <gtest/gtest.h>
#include <euclidian/Matrix.hpp>

#define ASSERT_MATRIX_2(matrix, a, b, c, d) \
    ASSERT_FLOAT_EQ(matrix[0][0], a); \
    ASSERT_FLOAT_EQ(matrix[0][1], b); \
    ASSERT_FLOAT_EQ(matrix[1][0], c); \
    ASSERT_FLOAT_EQ(matrix[1][1], d)

TEST(Matrix, Identity) {

    Matrix<2, 2> matrix = Matrix<2, 2>::identity();

    ASSERT_MATRIX_2(matrix, 1.0f, 0.0f, 0.0f, 1.0f);
}

TEST(Matrix, DefaultConstructor) {

    Matrix<2, 2> matrix;

    ASSERT_MATRIX_2(matrix, 0.0f, 0.0f, 0.0f, 0.0f);
}

TEST(Matrix, Constructor) {

    Matrix<2, 2> matrix(1.0f, 2.0f, 3.0f, 4.0f);

    ASSERT_MATRIX_2(matrix, 1.0f, 2.0f, 3.0f, 4.0f);
}

TEST(Matrix, ImplicitConstructor) {

    Matrix<2, 2> matrix = { 1.0f, 2.0f, 3.0f, 4.0f };

    ASSERT_MATRIX_2(matrix, 1.0f, 2.0f, 3.0f, 4.0f);
}