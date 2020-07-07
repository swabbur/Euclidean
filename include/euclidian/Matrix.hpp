#pragma once

#include "Vector.hpp"

template<std::size_t M, std::size_t N = M>
class Matrix {

    union {
        std::array<float, M * N> elements;
        std::array<Vector<N>, M> rows;
    };

    [[nodiscard]] Matrix<M, N> map(std::function<float(float)> const & function) const;

    [[nodiscard]] Matrix<M, N> map(float scalar, std::function<float(float, float)> const & function) const;

    [[nodiscard]] Matrix<M, N> map(Matrix<M, N> const & matrix, std::function<float(float, float)> const & function) const;

    Matrix<M, N> & apply(float scalar, std::function<float(float, float)> const & function) const;

    Matrix<M, N> & apply(Matrix<M, N> const & matrix, std::function<float(float, float)> const & function) const;

public:

    static Matrix<M, N> identity();

    template<typename ... Arguments>
    Matrix(Arguments ... arguments);

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

    Vector<N> * begin();

    Vector<N> * end();
};

template<std::size_t M, std::size_t N>
Matrix<M, N> Matrix<M, N>::map(std::function<float(float)> const & function) const {
    Matrix<M, N> result;
    std::transform(
            std::begin(elements),
            std::end(elements),
            std::begin(result.elements),
            function);
    return result;
}

template<std::size_t M, std::size_t N>
Matrix<M, N> Matrix<M, N>::map(float scalar, std::function<float(float, float)> const & function) const {
    Matrix<M, N> result;
    std::transform(
            std::begin(elements),
            std::end(elements),
            std::begin(result.elements),
            [scalar, &function](float element) {
                return function(element, scalar);
            });
    return result;
}

template<std::size_t M, std::size_t N>
Matrix<M, N> Matrix<M, N>::map(Matrix<M, N> const & matrix, std::function<float(float, float)> const & function) const {
    Matrix<M, N> result;
    std::transform(
            std::begin(elements),
            std::end(elements),
            std::begin(matrix.elements),
            std::begin(result.elements),
            function);
    return result;
}

template<std::size_t M, std::size_t N>
Matrix<M, N> & Matrix<M, N>::apply(float scalar, std::function<float(float, float)> const & function) const {
    std::transform(
            std::begin(elements),
            std::end(elements),
            std::begin(elements),
            [scalar, &function](float element) {
                return function(element, scalar);
            });
    return *this;
}

template<std::size_t M, std::size_t N>
Matrix<M, N> & Matrix<M, N>::apply(Matrix<M, N> const & matrix, std::function<float(float, float)> const & function) const {
    std::transform(
            std::begin(elements),
            std::end(elements),
            std::begin(matrix.elements),
            std::begin(elements),
            function);
    return *this;
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
    std::size_t const COUNT = sizeof ... (Arguments);
    static_assert(COUNT == 0 || COUNT == M * N, "Incorrect number of elements");
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
    return map(std::negate<>());
}

template<std::size_t M, std::size_t N>
Matrix<M, N> Matrix<M, N>::operator + (Matrix<M, N> const & matrix) const {
    return map(matrix, std::plus<>());
}

template<std::size_t M, std::size_t N>
Matrix<M, N> Matrix<M, N>::operator - (Matrix<M, N> const & matrix) const {
    return map(matrix, std::minus<>());
}

template<std::size_t M, std::size_t N>
Matrix<M, N> Matrix<M, N>::operator * (Matrix<M, N> const & matrix) const {
    return map(matrix, std::multiplies<>());
}

template<std::size_t M, std::size_t N>
Matrix<M, N> Matrix<M, N>::operator / (Matrix<M, N> const & matrix) const {
    return map(matrix, std::divides<>());
}

template<std::size_t M, std::size_t N>
Matrix<M, N> Matrix<M, N>::operator * (float scalar) const {
    return map(scalar, std::multiplies<>());
}

template<std::size_t M, std::size_t N>
Matrix<M, N> Matrix<M, N>::operator / (float scalar) const {
    return map(scalar, std::divides<>());
}

template<std::size_t M, std::size_t N>
Matrix<M, N> & Matrix<M, N>::operator += (Matrix<M, N> const & matrix) {
    return apply(matrix, std::plus<>());
}

template<std::size_t M, std::size_t N>
Matrix<M, N> & Matrix<M, N>::operator -= (Matrix<M, N> const & matrix) {
    return apply(matrix, std::minus<>());
}

template<std::size_t M, std::size_t N>
Matrix<M, N> & Matrix<M, N>::operator *= (Matrix<M, N> const & matrix) {
    return apply(matrix, std::multiplies<>());
}

template<std::size_t M, std::size_t N>
Matrix<M, N> & Matrix<M, N>::operator /= (Matrix<M, N> const & matrix) {
    return apply(matrix, std::divides<>());
}

template<std::size_t M, std::size_t N>
Matrix<M, N> & Matrix<M, N>::operator *= (float scalar) {
    return apply(scalar, std::multiplies<>());
}

template<std::size_t M, std::size_t N>
Matrix<M, N> & Matrix<M, N>::operator /= (float scalar) {
    return apply(scalar, std::divides<>());
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
Vector<N> * Matrix<M, N>::begin() {
    return std::begin(rows);
}

template<std::size_t M, std::size_t N>
Vector<N> * Matrix<M, N>::end() {
    return std::end(rows);
}
