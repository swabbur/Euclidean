#pragma once

#include "Matrix.hpp"
#include "Vector.hpp"

#include <cmath>

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
    Matrix<P, N> transposed = second.transpose();
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
    product[1] = (a[0] * b[2]) - (a[2] * b[0]);
    product[2] = (a[0] * b[1]) - (a[1] * b[0]);
    return product;
}

template<std::size_t N>
float length(Vector<N> const & vector) {
    return std::sqrt(dot(vector, vector));
}

