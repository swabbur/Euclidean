#include <euclidian/Functions.hpp>
#include "Assertions.hpp"

TEST(Functions, Transpose) {

    Matrix<2, 3> matrix = {
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f
    };

    assert_matrix(transpose(matrix), {
        1.0f, 4.0f,
        2.0f, 5.0f,
        3.0f, 6.0f
    });
}

TEST(Functions, DotVector) {

    Vector<3> a = { 1.0f, 2.0f, 3.0f };
    Vector<3> b = { 4.0f, 5.0f, 6.0f };
    float product = dot(a, b);

    assert_scalar(product, 32.0f);
}

TEST(Functions, DotMatrixVector) {

    Matrix<2, 3> matrix = {
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f
    };

    Vector<3> vector = { 7.0f, 8.0f, 9.0f };

    assert_vector(dot(matrix, vector), { 50.0f, 122.0f });
}

TEST(Functions, DotMatrix) {

    Matrix<2, 3> a = {
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f
    };

    Matrix<3, 2> b = {
            1.0f, 2.0f,
            3.0f, 4.0f,
            5.0f, 6.0f
    };

    assert_matrix(dot(a, b), {
        22.0f, 28.0f,
        49.0f, 64.0f,
    });
}

TEST(Functions, Cross) {

    Vector<3> a = { 1.0f, 2.0f, 3.0f };
    Vector<3> b = { 4.0f, 5.0f, 6.0f };

    assert_vector(cross(a, b), { -3.0f, 6.0f, -3.0f });
}

TEST(Functions, Length) {

    Vector<3> vector = { 0.0f, 3.0f, -4.0f };

    assert_scalar(length(vector), 5.0f);
}

TEST(Functions, Sub) {

    Matrix<2, 3> matrix = {
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f
    };

    assert_matrix(sub(matrix, 0, 0), { 5.0f, 6.0f });
    assert_matrix(sub(matrix, 0, 1), { 4.0f, 6.0f });
    assert_matrix(sub(matrix, 0, 2), { 4.0f, 5.0f });
    assert_matrix(sub(matrix, 1, 0), { 2.0f, 3.0f });
    assert_matrix(sub(matrix, 1, 1), { 1.0f, 3.0f });
    assert_matrix(sub(matrix, 1, 2), { 1.0f, 2.0f });
}

TEST(Functions, Determinant1) {

    Matrix<1> matrix = { 4.0f };

    assert_scalar(determinant(matrix), 4.0f);
}

TEST(Functions, Determinant2) {

    Matrix<2> matrix = {
            1.0f, 2.0f,
            3.0f, 4.0f
    };

    assert_scalar(determinant(matrix), -2.0f);
}

TEST(Functions, Determinant3) {

    Matrix<3> matrix {
        1.0f, -2.0f, 4.0f,
        0.0f, 2.0f, -4.0f,
        0.0f, 0.0f, 4.0f
    };

    assert_scalar(determinant(matrix), 8.0f);
}

TEST(Functions, Inverse1) {

    Matrix<1> matrix = { 4.0f };

    assert_matrix(inverse(matrix).value(), { 0.25f });
}

TEST(Functions, Inverse2) {

    Matrix<2> matrix = {
            1.0f, 2.0f,
            3.0f, 4.0f
    };

    assert_matrix(inverse(matrix).value(), {
        -2.0f, 1.0f,
        1.5f, -0.5f
    });
}

TEST(Functions, Inverse3) {

    Matrix<3> matrix {
            1.0f, -2.0f, 4.0f,
            0.0f, 2.0f, -4.0f,
            0.0f, 0.0f, 4.0f
    };

    assert_matrix(inverse(matrix).value(), {
        1.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.5f,
        0.0f, 0.0f, 0.25f
    });
}

TEST(Functions, InverseReflection) {

    Matrix<3> matrix {
            1.0f, -2.0f, 4.0f,
            0.0f, 2.0f, -4.0f,
            0.0f, 0.0f, 4.0f
    };

    assert_matrix(inverse(inverse(matrix).value()).value(), matrix);
}

TEST(Functions, InverseFailure) {

    Matrix<2> matrix = {
            0.0f, 0.0f,
            0.0f, 0.0f
    };

    assert_false(inverse(matrix).has_value());
}