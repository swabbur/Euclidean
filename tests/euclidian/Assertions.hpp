#pragma once

#include <euclidian/Matrix.hpp>
#include <euclidian/Vector.hpp>
#include <gtest/gtest.h>
#include <cmath>

void assert_false(bool expression);

void assert_nan(float scalar);

void assert_inf(float scalar);

void assert_scalar(float actual, float expected);

template<std::size_t N>
void assert_vector(Vector<N> const & actual, Vector<N> const & expected) {
    for (std::size_t n = 0; n < N; n++) {
        assert_scalar(actual[n], expected[n]);
    }
}

template<std::size_t N, std::size_t M = N>
void assert_matrix(Matrix<N, M> const & actual, Matrix<N, M> const & expected) {
    for (std::size_t n = 0; n < N; n++) {
        assert_vector(actual[n], expected[n]);
    }
}
