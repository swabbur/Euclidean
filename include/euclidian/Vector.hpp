#pragma once

#include <algorithm>
#include <array>

template<std::size_t N>
class Vector {

    std::array<float, N> components;

    [[nodiscard]] Vector<N> map(std::function<float(float)> const & function) const;

    [[nodiscard]] Vector<N> map(float scalar, std::function<float(float, float)> const & function) const;

    [[nodiscard]] Vector<N> map(Vector<N> const & vector, std::function<float(float, float)> const & function) const;

    Vector<N> & apply(float scalar, std::function<float(float, float)> const & function) const;

    Vector<N> & apply(Vector<N> const & vector, std::function<float(float, float)> const & function) const;

public:

    template<typename ... Arguments>
    Vector(Arguments ... arguments);

    [[nodiscard]] float operator [] (std::size_t index) const;

    float & operator [] (std::size_t index);

    [[nodiscard]] Vector<N> operator - () const;

    [[nodiscard]] Vector<N> operator + (Vector<N> const & vector) const;

    [[nodiscard]] Vector<N> operator - (Vector<N> const & vector) const;

    [[nodiscard]] Vector<N> operator * (Vector<N> const & vector) const;

    [[nodiscard]] Vector<N> operator / (Vector<N> const & vector) const;

    [[nodiscard]] Vector<N> operator * (float scalar) const;

    [[nodiscard]] Vector<N> operator / (float scalar) const;

    Vector<N> & operator += (Vector<N> const & vector);

    Vector<N> & operator -= (Vector<N> const & vector);

    Vector<N> & operator *= (Vector<N> const & vector);

    Vector<N> & operator /= (Vector<N> const & vector);

    Vector<N> & operator *= (float scalar);

    Vector<N> & operator /= (float scalar);

    [[nodiscard]] float const * begin() const;

    [[nodiscard]] float const * end() const;

    float * begin();

    float * end();
};

template<std::size_t N>
Vector<N> Vector<N>::map(std::function<float(float)> const & function) const {
    Vector<N> result;
    std::transform(begin(), end(), std::begin(result), function);
    return result;
}

template<std::size_t N>
Vector<N> Vector<N>::map(float scalar, std::function<float(float, float)> const & function) const {
    Vector<N> result;
    std::transform(begin(), end(), std::begin(result), [scalar, &function](float component){
        return function(component, scalar);
    });
    return result;
}

template<std::size_t N>
Vector<N> Vector<N>::map(Vector<N> const & vector, std::function<float(float, float)> const & function) const {
    Vector<N> result;
    std::transform(begin(), end(), std::begin(vector), std::begin(result), function);
    return result;
}

template<std::size_t N>
Vector<N> & Vector<N>::apply(float scalar, std::function<float(float, float)> const & function) const {
    std::transform(begin(), end(), begin(), [scalar, &function](float component){
        return function(component, scalar);
    });
    return *this;
}

template<std::size_t N>
Vector<N> & Vector<N>::apply(Vector<N> const & vector, std::function<float(float, float)> const & function) const {
    std::transform(begin(), end(), std::begin(vector), begin(), function);
    return *this;
}

template<std::size_t N>
template<typename ... Arguments>
Vector<N>::Vector(Arguments ... arguments): components{ arguments ... } {
    std::size_t const SIZE = sizeof ... (Arguments);
    static_assert(SIZE == 0 || SIZE == N, "Incorrect number of components");
}

template<std::size_t N>
float Vector<N>::operator [] (std::size_t index) const {
    return components[index];
}

template<std::size_t N>
float & Vector<N>::operator [] (std::size_t index) {
    return components[index];
}

template<std::size_t N>
Vector<N> Vector<N>::operator - () const {
    return map(std::negate<>());
}

template<std::size_t N>
Vector<N> Vector<N>::operator + (Vector<N> const & vector) const {
    return map(vector, std::plus<>());
}

template<std::size_t N>
Vector<N> Vector<N>::operator - (Vector<N> const & vector) const {
    return map(vector, std::minus<>());
}

template<std::size_t N>
Vector<N> Vector<N>::operator * (Vector<N> const & vector) const {
    return map(vector, std::multiplies<>());
}

template<std::size_t N>
Vector<N> Vector<N>::operator / (Vector<N> const & vector) const {
    return map(vector, std::divides<>());
}

template<std::size_t N>
Vector<N> Vector<N>::operator * (float scalar) const {
    return map(scalar, std::multiplies<>());
}

template<std::size_t N>
Vector<N> Vector<N>::operator / (float scalar) const {
    return map(scalar, std::divides<>());
}

template<std::size_t N>
Vector<N> & Vector<N>::operator += (Vector<N> const & vector) {
    return apply(vector, std::plus<>());
}

template<std::size_t N>
Vector<N> & Vector<N>::operator -= (Vector<N> const & vector) {
    return apply(vector, std::minus<>());
}

template<std::size_t N>
Vector<N> & Vector<N>::operator *= (Vector<N> const & vector) {
    return apply(vector, std::multiplies<>());
}

template<std::size_t N>
Vector<N> & Vector<N>::operator /= (Vector<N> const & vector) {
    return apply(vector, std::divides<>());
}

template<std::size_t N>
Vector<N> & Vector<N>::operator *= (float scalar) {
    return apply(scalar, std::multiplies<>());
}

template<std::size_t N>
Vector<N> & Vector<N>::operator /= (float scalar) {
    return apply(scalar, std::divides<>());
}

template<std::size_t N>
float const * Vector<N>::begin() const {
    return std::begin(components);
}

template<std::size_t N>
float const * Vector<N>::end() const {
    return std::end(components);
}

template<std::size_t N>
float * Vector<N>::begin() {
    return std::begin(components);
}

template<std::size_t N>
float * Vector<N>::end() {
    return std::end(components);
}
