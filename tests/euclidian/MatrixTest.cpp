#include "Assertions.h"

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

    Matrix<2, 2> matrix = {
            -1.0f, 0.0f,
            0.0f, 1.0f
    };

    Matrix<2, 2> negated = -matrix;

    assert_matrix(negated, {
        1.0f, 0.0f,
        0.0f, -1.0f
    });
}
