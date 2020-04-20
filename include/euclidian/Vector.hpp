#pragma once

#include <algorithm>
#include <array>
#include <functional>

template<std::size_t N>
class Vector {

    template<std::size_t OFFSET, typename ... Arguments>
    struct Filler;

    std::array<float, N> components;

    [[nodiscard]] Vector<N> map(std::function<float(float)> const & function) const;

    [[nodiscard]] Vector<N> map(float scalar, std::function<float(float, float)> const & function) const;

    [[nodiscard]] Vector<N> map(Vector<N> const & vector, std::function<float(float, float)> const & function) const;

    Vector<N> & apply(float scalar, std::function<float(float, float)> const & function) const;

    Vector<N> & apply(Vector<N> const & vector, std::function<float(float, float)> const & function) const;

public:

    template<typename ... Arguments>
    Vector(Arguments const & ... arguments);

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
template<std::size_t OFFSET, typename ... Arguments>
struct Vector<N>::Filler {

    static void fill(Vector<N> & vector) {
        static_assert(OFFSET == N, "Incorrect number of arguments provided");
    }
};

template<std::size_t N>
template<std::size_t OFFSET, typename ... Arguments>
struct Vector<N>::Filler<OFFSET, float, Arguments ...> {

    static void fill(Vector<N> & vector, float component, Arguments const & ... arguments) {
        vector[OFFSET] = component;
        Filler<OFFSET + 1, Arguments ...>::fill(vector, arguments ...);
    }
};

template<std::size_t N>
template<std::size_t OFFSET, std::size_t M, typename ... Arguments>
struct Vector<N>::Filler<OFFSET, Vector<M>, Arguments ...> {

    static void fill(Vector<N> & vector, Vector<M> const & components, Arguments const & ... arguments) {
        std::move(std::begin(components), std::end(components), std::next(std::begin(vector), OFFSET));
        Filler<OFFSET + M, Arguments ...>::fill(vector, arguments ...);
    }
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
Vector<N>::Vector(Arguments const & ... arguments): components{} {
    if constexpr (sizeof ... (Arguments) > 0) {
        Filler<0, Arguments ...>::fill(*this, arguments ...);
    }
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
