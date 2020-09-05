#pragma once

#include "Matrix.hpp"
#include "Vector.hpp"

#include <cmath>
#include <numeric>
#include <optional>

template<std::size_t M, std::size_t N>
Matrix<N, M> transpose(Matrix<M, N> const & matrix) {
    Matrix<N, M> transposed;
    for (std::size_t m = 0; m < M; m++) {
        for (std::size_t n = 0; n < N; n++) {
            transposed[n][m] = matrix[m][n];
        }
    }
    return transposed;
}

template<std::size_t N>
float dot(Vector<N> const & a, Vector<N> const & b) {
    return std::inner_product(
            std::begin(a),
            std::end(a),
            std::begin(b),
            0.0f);
}

template<std::size_t M, std::size_t N>
Vector<M> dot(Matrix<M, N> const & matrix, Vector<N> const & vector) {
    Vector<M> product;
    for (std::size_t m = 0; m < M; m++) {
        product[m] = dot(matrix[m], vector);
    }
    return product;
}

template<std::size_t M, std::size_t N, std::size_t P>
Matrix<M, P> dot(Matrix<M, N> const & first, Matrix<N, P> const & second) {
    Matrix<P, N> transposed = transpose(second);
    Matrix<M, P> product;
    for (std::size_t m = 0; m < M; m++) {
        for (std::size_t p = 0; p < P; p++) {
            product[m][p] = dot(first[m], transposed[p]);
        }
    }
    return product;
}

Vector<3> cross(Vector<3> const & a, Vector<3> const & b) {
    Vector<3> product;
    product[0] = (a[1] * b[2]) - (a[2] * b[1]);
    product[1] = (a[2] * b[0]) - (a[0] * b[2]);
    product[2] = (a[0] * b[1]) - (a[1] * b[0]);
    return product;
}

template<std::size_t N>
float length(Vector<N> const & vector) {
    return std::sqrt(dot(vector, vector));
}

template<std::size_t M, std::size_t N>
Matrix<M - 1, N - 1> sub(Matrix<M, N> const & matrix, std::size_t i, std::size_t j) {

    Matrix<M - 1, N - 1> sub_matrix;

    for (std::size_t m = 0; m < i; m++) {

        for (std::size_t n = 0; n < j; n++) {
            sub_matrix[m][n] = matrix[m][n];
        }

        for (std::size_t n = j + 1; n < N; n++) {
            sub_matrix[m][n - 1] = matrix[m][n];
        }
    }

    for (std::size_t m = i + 1; m < M; m++) {

        for (std::size_t n = 0; n < j; n++) {
            sub_matrix[m - 1][n] = matrix[m][n];
        }

        for (std::size_t n = j + 1; n < N; n++) {
            sub_matrix[m - 1][n - 1] = matrix[m][n];
        }
    }

    return sub_matrix;
}

template<std::size_t N>
float determinant(Matrix<N> const & matrix) {

    if constexpr (N == 1) {
        return matrix[0][0];
    }

    if constexpr (N == 2) {
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
    }

    if constexpr (N > 2) {
        float det = 0.0f;
        for (std::size_t n = 0; n < N; n++) {
            det += matrix[0][n] * determinant(sub(matrix, 0, n));
        }
        return det;
    }
}

template<std::size_t N>
std::optional<Matrix<N>> inverse(Matrix<N> const & matrix) {

    if constexpr (N == 1) {

        if (matrix[0][0] == 0.0f) {
            return std::nullopt;
        }

        return { 1.0f / matrix[0][0] };
    }

    if constexpr (N == 2) {

        float det = determinant(matrix);
        if (det == 0.0f) {
            return std::nullopt;
        }

         return {{
             matrix[1][1] / det, -matrix[0][1] / det,
             -matrix[1][0] / det, matrix[0][0] / det
         }};
    }

    if constexpr (N > 2) {

        Matrix<N> inverse;
        for (std::size_t m = 0; m < N; m++) {
            for (std::size_t n = 0; n < N; n++) {
                inverse[m][n] = determinant(sub(matrix, m, n));
            }
        }

        for (std::size_t m = 0; m < N; m++) {
            for (std::size_t n = 0; n < N; n++) {
                std::size_t i = m * N + n;
                if (i % 2 == 1) {
                    inverse[m][n] *= -1.0f;
                }
            }
        }

        float det = 0.0f;
        for (std::size_t n = 0; n < N; n++) {
            det += matrix[0][n] * inverse[0][n];
        }

        inverse = transpose(inverse);

        return inverse / det;
    }
}
