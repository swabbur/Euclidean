#pragma once

#include <array>
#include <random>

template<std::size_t N>
class Vector {

    std::array<float, N> components;

public:

    static Vector<N> random();

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
Vector<N> Vector<N>::random() {

    static std::random_device device;
    static std::default_random_engine engine(device());
    static std::uniform_real_distribution<float> distribution;

    Vector<N> vector;
    for (std::size_t n = 0; n < N; n++) {
        vector[n] = distribution(engine);
    }
    return vector;
}

template<std::size_t N>
template<typename ... Arguments>
Vector<N>::Vector(Arguments ... arguments): components{ arguments ... } {
    static_assert(sizeof ... (Arguments) == 0 || sizeof ... (Arguments) == N, "Incorrect number of components");
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
    Vector<N> negative;
    std::transform(
            std::begin(components), std::end(components),
            std::begin(negative.components),
            std::negate<>());
    return negative;
}

template<std::size_t N>
Vector<N> Vector<N>::operator + (Vector<N> const & vector) const {
    Vector<N> sum;
    std::transform(
            std::begin(components), std::end(components),
            std::begin(vector.components),
            std::begin(sum.components),
            std::plus<>());
    return sum;
}

template<std::size_t N>
Vector<N> Vector<N>::operator - (Vector<N> const & vector) const {
    Vector<N> difference;
    std::transform(
            std::begin(components), std::end(components),
            std::begin(vector.components),
            std::begin(difference.components),
            std::minus<>());
    return difference;
}

template<std::size_t N>
Vector<N> Vector<N>::operator * (Vector<N> const & vector) const {
    Vector<N> product;
    std::transform(
            std::begin(components), std::end(components),
            std::begin(vector.components),
            std::begin(product.components),
            std::multiplies<>());
    return product;
}

template<std::size_t N>
Vector<N> Vector<N>::operator / (Vector<N> const & vector) const {
    Vector<N> fraction;
    std::transform(
            std::begin(components), std::end(components),
            std::begin(vector.components),
            std::begin(fraction.components),
            std::divides<>());
    return fraction;
}

template<std::size_t N>
Vector<N> Vector<N>::operator * (float scalar) const {
    Vector<N> product;
    std::transform(
            std::begin(components), std::end(components),
            std::begin(product.components),
            [&scalar](float component){
                return component * scalar;
            });
    return product;
}

template<std::size_t N>
Vector<N> Vector<N>::operator / (float scalar) const {
    Vector<N> fraction;
    std::transform(
            std::begin(components), std::end(components),
            std::begin(fraction.components),
            [&scalar](float component){
                return component / scalar;
            });
    return fraction;
}

template<std::size_t N>
Vector<N> & Vector<N>::operator += (Vector<N> const & vector) {
    std::transform(
            std::begin(components), std::end(components),
            std::begin(vector.components),
            std::begin(components),
            std::plus<>());
    return *this;
}

template<std::size_t N>
Vector<N> & Vector<N>::operator -= (Vector<N> const & vector) {
    std::transform(
            std::begin(components), std::end(components),
            std::begin(vector.components),
            std::begin(components),
            std::minus<>());
    return *this;
}

template<std::size_t N>
Vector<N> & Vector<N>::operator *= (Vector<N> const & vector) {
    std::transform(
            std::begin(components), std::end(components),
            std::begin(vector.components),
            std::begin(components),
            std::multiplies<>());
    return *this;
}

template<std::size_t N>
Vector<N> & Vector<N>::operator /= (Vector<N> const & vector) {
    std::transform(
            std::begin(components), std::end(components),
            std::begin(vector.components),
            std::begin(components),
            std::divides<>());
    return *this;
}

template<std::size_t N>
Vector<N> & Vector<N>::operator *= (float scalar) {
    std::transform(
            std::begin(components),std::end(components),
            std::begin(components),
            [&scalar](float component){
                return component * scalar;
            });
    return *this;
}

template<std::size_t N>
Vector<N> & Vector<N>::operator /= (float scalar) {
    std::transform(
            std::begin(components),std::end(components),
            std::begin(components),
            [&scalar](float component){
                return component / scalar;
            });
    return *this;
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
