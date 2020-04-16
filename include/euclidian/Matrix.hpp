#pragma once

#include "Vector.hpp"

template<std::size_t M, std::size_t N = M>
class Matrix {

    union {
        std::array<float, M * N> elements;
        std::array<Vector<N>, M> rows;
    };

public:

    static Matrix<M, N> random();

    static Matrix<M, N> identity();

    template<typename ... Arguments>
    explicit Matrix(Arguments ... arguments);

    [[nodiscard]] Vector<N> const & operator [] (std::size_t index) const;

    Vector<N> & operator [] (std::size_t index);

    [[nodiscard]] Matrix<M, N> operator - () const;

    [[nodiscard]] Matrix<M, N> operator + (Matrix<M, N> const & matrix) const;

    [[nodiscard]] Matrix<M, N> operator - (Matrix<M, N> const & matrix) const;

    [[nodiscard]] Matrix<M, N> operator * (Matrix<M, N> const & matrix) const;

    [[nodiscard]] Matrix<M, N> operator / (Matrix<M, N> const & matrix) const;

    [[nodiscard]] Matrix<M, N> operator * (float scalar) const;

    [[nodiscard]] Matrix<M, N> operator / (float scalar) const;

    Matrix<M, N> & operator += (Matrix<M, N> const & matrix);

    Matrix<M, N> & operator -= (Matrix<M, N> const & matrix);

    Matrix<M, N> & operator *= (Matrix<M, N> const & matrix);

    Matrix<M, N> & operator /= (Matrix<M, N> const & matrix);

    Matrix<M, N> & operator *= (float scalar);

    Matrix<M, N> & operator /= (float scalar);

    [[nodiscard]] Vector<N> const & begin() const;

    [[nodiscard]] Vector<N> const & end() const;

    Vector<N> & begin();

    Vector<N> & end();
};

template<std::size_t M, std::size_t N>
Matrix<M, N> Matrix<M, N>::random() {

    static std::random_device device;
    static std::default_random_engine engine(device());
    static std::uniform_real_distribution<float> distribution;

    Matrix<M, N> matrix;
    for (std::size_t m = 0; m < M; m++) {
        for (std::size_t n = 0; n < N; n++) {
            matrix[m][n] = distribution(engine);
        }
    }
    return matrix;
}

template<std::size_t M, std::size_t N>
Matrix<M, N> Matrix<M, N>::identity() {
    Matrix<M, N> matrix;
    for (std::size_t i = 0; i < M && i < N; i++) {
        matrix[i][i] = 1.0f;
    }
    return matrix;
}

template<std::size_t M, std::size_t N>
template<typename ... Arguments>
Matrix<M, N>::Matrix(Arguments ... arguments): elements{ arguments ...} {
    static_assert(sizeof ... (Arguments) == 0 || sizeof ... (Arguments) == M * N, "Incorrect number of elements");
}

template<std::size_t M, std::size_t N>
Vector<N> const & Matrix<M, N>::operator [] (std::size_t index) const {
    return rows[index];
}

template<std::size_t M, std::size_t N>
Vector<N> & Matrix<M, N>::operator [] (std::size_t index) {
    return rows[index];
}

template<std::size_t M, std::size_t N>
Matrix<M, N> Matrix<M, N>::operator - () const {
    Matrix<M, N> negative;
    std::transform(
            std::begin(elements), std::end(elements),
            std::begin(negative.elements),
            std::negate<>());
    return negative;
}

template<std::size_t M, std::size_t N>
Matrix<M, N> Matrix<M, N>::operator + (Matrix<M, N> const & matrix) const {
    Matrix<M, N> sum;
    std::transform(
            std::begin(elements),
            std::end(elements),
            std::begin(matrix.elements),
            std::begin(sum.elements),
            std::plus<>());
    return sum;
}

template<std::size_t M, std::size_t N>
Matrix<M, N> Matrix<M, N>::operator - (Matrix<M, N> const & matrix) const {
    Matrix<M, N> difference;
    std::transform(
            std::begin(elements),
            std::end(elements),
            std::begin(matrix.elements),
            std::begin(difference.elements),
            std::minus<>());
    return difference;
}

template<std::size_t M, std::size_t N>
Matrix<M, N> Matrix<M, N>::operator * (Matrix<M, N> const & matrix) const {
    Matrix<M, N> product;
    std::transform(
            std::begin(elements),
            std::end(elements),
            std::begin(matrix.elements),
            std::begin(product.elements),
            std::multiplies<>());
    return product;
}

template<std::size_t M, std::size_t N>
Matrix<M, N> Matrix<M, N>::operator / (Matrix<M, N> const & matrix) const {
    Matrix<M, N> fraction;
    std::transform(
            std::begin(elements),
            std::end(elements),
            std::begin(matrix.elements),
            std::begin(fraction.elements),
            std::divides<>());
    return fraction;
}

template<std::size_t M, std::size_t N>
Matrix<M, N> Matrix<M, N>::operator * (float scalar) const {
    Matrix<M, N> product;
    std::transform(
            std::begin(elements),
            std::end(elements),
            std::begin(product.elements),
            [&scalar](float element) {
                return element * scalar;
            });
    return product;
}

template<std::size_t M, std::size_t N>
Matrix<M, N> Matrix<M, N>::operator / (float scalar) const {
    Matrix<M, N> fraction;
    std::transform(
            std::begin(elements),
            std::end(elements),
            std::begin(fraction.elements),
            [&scalar](float element) {
                return element / scalar;
            });
    return fraction;
}

template<std::size_t M, std::size_t N>
Matrix<M, N> & Matrix<M, N>::operator += (Matrix<M, N> const & matrix) {
    std::transform(
            std::begin(elements),
            std::end(elements),
            std::begin(matrix.elements),
            std::begin(elements),
            std::plus<>());
    return *this;
}

template<std::size_t M, std::size_t N>
Matrix<M, N> & Matrix<M, N>::operator -= (Matrix<M, N> const & matrix) {
    std::transform(
            std::begin(elements),
            std::end(elements),
            std::begin(matrix.elements),
            std::begin(elements),
            std::minus<>());
    return *this;
}

template<std::size_t M, std::size_t N>
Matrix<M, N> & Matrix<M, N>::operator *= (Matrix<M, N> const & matrix) {
    std::transform(
            std::begin(elements),
            std::end(elements),
            std::begin(matrix.elements),
            std::begin(elements),
            std::multiplies<>());
    return *this;
}

template<std::size_t M, std::size_t N>
Matrix<M, N> & Matrix<M, N>::operator /= (Matrix<M, N> const & matrix) {
    std::transform(
            std::begin(elements),
            std::end(elements),
            std::begin(matrix.elements),
            std::begin(elements),
            std::divides<>());
    return *this;
}

template<std::size_t M, std::size_t N>
Matrix<M, N> & Matrix<M, N>::operator *= (float scalar) {
    std::transform(
            std::begin(elements),
            std::end(elements),
            std::begin(elements),
            [&scalar](float element) {
                return element * scalar;
            });
    return *this;
}

template<std::size_t M, std::size_t N>
Matrix<M, N> & Matrix<M, N>::operator /= (float scalar) {
    std::transform(
            std::begin(elements),
            std::end(elements),
            std::begin(elements),
            [&scalar](float element) {
                return element / scalar;
            });
    return *this;
}

template<std::size_t M, std::size_t N>
Vector<N> const & Matrix<M, N>::begin() const {
    return std::begin(rows);
}

template<std::size_t M, std::size_t N>
Vector<N> const & Matrix<M, N>::end() const {
    return std::end(rows);
}

template<std::size_t M, std::size_t N>
Vector<N> & Matrix<M, N>::begin() {
    return std::begin(rows);
}

template<std::size_t M, std::size_t N>
Vector<N> & Matrix<M, N>::end() {
    return std::end(rows);
}
