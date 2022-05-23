#pragma once

#include "../Tensor.hpp"
#include "Covector.hpp"
#include "Vector.hpp"

template<Field Component, Size ROWS, Size COLUMNS = ROWS>
using LinearMap = Tensor<Component, Dimension<Variance::CONTRAVARIANT, ROWS>, Dimension<Variance::COVARIANT, COLUMNS>>;

template<Field Component, Size ROWS, Size COLUMNS = ROWS>
using Matrix = LinearMap<Component, ROWS, COLUMNS>;

// matrix-matrix -> matrix
// matrix-vector -> vector
// covector-matrix -> covector
// vector-covector -> matrix
// covector-vector -> scalar

template<typename Field, Size N, Size M, Size P>
constexpr auto matrix_product(Matrix<Field, N, M> const & lhs, Matrix<Field, M, P> const & rhs) {
    Matrix<Field, N, P> product;
    for (Index n = 0; n < N; n++) {
        for (Index m = 0; m < M; m++) {
            for (Index p = 0; p < P; p++) {
                product.at(n, p) += lhs.at(n, m) * rhs.at(m, p);
            }
        }
    }
    return product;
}

template<typename Field, Size N, Size M>
constexpr auto matrix_product(Matrix<Field, N, M> const & lhs, Vector<Field, M> const & rhs) {
    Vector<Field, N> product;
    for (Index n = 0; n < N; n++) {
        for (Index m = 0; m < M; m++) {
            product.at(n) += lhs.at(n, m) * rhs.at(m);
        }
    }
    return product;
}
