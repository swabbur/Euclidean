#include "Assertions.h"

TEST(Matrix, Identity) {

    Matrix<2, 2> matrix = Matrix<2, 2>::identity();

    assert_matrix(matrix, {1.0f, 0.0f, 0.0f, 1.0f});
}

TEST(Matrix, DefaultConstructor) {

    Matrix<2, 2> matrix;

    assert_matrix(matrix, {0.0f, 0.0f, 0.0f, 0.0f});
}

TEST(Matrix, Constructor) {

    Matrix<2, 2> matrix(1.0f, 2.0f, 3.0f, 4.0f);

    assert_matrix(matrix, {1.0f, 2.0f, 3.0f, 4.0f});
}

TEST(Matrix, ImplicitConstructor) {

    Matrix<2, 2> matrix = { 1.0f, 2.0f, 3.0f, 4.0f };

    assert_matrix(matrix, {1.0f, 2.0f, 3.0f, 4.0f});
}