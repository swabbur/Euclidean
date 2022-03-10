#pragma once

#include <algorithm>
#include <array>
#include <functional>
#include <numeric>
#include <ranges>

template<std::semiregular Component, std::size_t SIZE>
class Vector {

    template<typename>
    struct Size;

    template<template <typename, std::size_t> typename Container, std::convertible_to<Component> C, std::size_t S>
    struct Size<Container<C, S>> {
        static constexpr std::size_t VALUE = S;
    };

    template<std::convertible_to<Component> C>
    struct Size<C> {
        static constexpr std::size_t VALUE = 1;
    };

    template<typename ... Values>
    static constexpr std::size_t COUNT = (0 + ... + Size<std::remove_cvref_t<Values>>::VALUE);


    template<std::input_iterator Iterator, std::ranges::range Range>
    static constexpr auto add(Iterator iterator, Range const & range) noexcept {
        return std::copy(std::begin(range), std::end(range), iterator);
    }

    template<std::input_iterator Iterator, std::convertible_to<Component> Value>
    static constexpr auto add(Iterator iterator, Value const & value) noexcept {
        *iterator = value;
        return std::next(iterator);
    }

    std::array<Component, SIZE> components;

public:

    [[nodiscard]] constexpr Vector() noexcept : components{} {}

    template<typename ... Values>
    requires (COUNT<Values ...> == SIZE)
    [[nodiscard]] constexpr Vector(Values && ... values) noexcept : components() { // NOLINT(google-explicit-constructor)
        auto iterator = std::begin(components);
        ((iterator = add(iterator, values)), ...);
    }

    template<typename T = Component, typename = std::enable_if_t<std::is_same_v<T, bool>>>
    [[nodiscard]] constexpr explicit operator bool () const noexcept {
        return std::all_of(std::begin(components), std::end(components), [](auto const & component){
            return component;
        });
    }

    [[nodiscard]] constexpr auto & operator [] (std::size_t index) const noexcept {
        return components[index];
    }

    [[nodiscard]] constexpr auto & operator [] (std::size_t index) noexcept {
        return components[index];
    }

    [[nodiscard]] constexpr auto begin() const noexcept {
        return std::cbegin(components);
    }

    [[nodiscard]] constexpr auto end() const noexcept {
        return std::cend(components);
    }

    [[nodiscard]] constexpr auto begin() noexcept {
        return std::begin(components);
    }

    [[nodiscard]] constexpr auto end() noexcept {
        return std::end(components);
    }
};

// Structured binding decomposition

namespace std {

    template<std::semiregular Type, std::size_t SIZE>
    struct tuple_size<Vector<Type, SIZE>> : integral_constant<std::size_t, SIZE> {};

    template<std::size_t INDEX, std::semiregular Type, std::size_t SIZE>
    struct tuple_element<INDEX, Vector<Type, SIZE>> {
        using type = Type;
    };
}

template<std::size_t INDEX, std::semiregular Type, std::size_t SIZE>
auto get(Vector<Type, SIZE> const & vector) {
    return vector[INDEX];
}

template<std::size_t INDEX, std::semiregular Type, std::size_t SIZE>
auto get(Vector<Type, SIZE> & vector) {
    return vector[INDEX];
}

// Functional functions

template<typename Operator, typename Component, std::size_t SIZE>
requires requires (Component const & component) {
    { Operator()(component) };
}
[[nodiscard]] constexpr auto map(Vector<Component, SIZE> const & vector) {
    Vector<decltype(Operator()(std::declval<Component>())), SIZE> result;
    std::transform(std::begin(vector), std::end(vector), std::begin(result), Operator());
    return result;
}

template<typename Operator, typename LHS, typename RHS, std::size_t SIZE>
requires requires (LHS const & lhs, RHS const & rhs) {
    { Operator()(lhs, rhs) };
}
[[nodiscard]] constexpr auto map(Vector<LHS, SIZE> const & lhs, RHS const & rhs) {
    Vector<decltype(Operator()(std::declval<LHS>(), std::declval<RHS>())), SIZE> result;
    std::transform(std::begin(lhs), std::end(lhs), std::begin(result), [&rhs](auto const & component) {
        return Operator()(component, rhs);
    });
    return result;
}

template<typename Operator, typename RHS, typename LHS, std::size_t SIZE>
requires requires (RHS const & lhs, LHS const & rhs) {
    { Operator()(lhs, rhs) };
}
[[nodiscard]] constexpr auto map(LHS const & test, Vector<RHS, SIZE> const & rhs) {
    Vector<decltype(Operator()(std::declval<LHS>(), std::declval<RHS>())), SIZE> result;
    std::transform(std::begin(rhs), std::end(rhs), std::begin(result), [&test](auto const & component) {
        return Operator()(test, component);
    });
    return result;
}

template<typename Operator, typename LHS, typename RHS, std::size_t SIZE>
requires requires (LHS const & lhs, RHS const & rhs) {
    { Operator()(lhs, rhs) };
}
[[nodiscard]] constexpr auto map(Vector<LHS, SIZE> const & lhs, Vector<RHS, SIZE> const & rhs) {
    Vector<decltype(Operator()(std::declval<LHS>(), std::declval<RHS>())), SIZE> result;
    std::transform(std::begin(lhs), std::end(lhs), std::begin(rhs), std::begin(result), Operator());
    return result;
}

// Math functions

template<typename LHS, typename RHS, std::size_t SIZE>
[[nodiscard]] constexpr auto dot(Vector<LHS, SIZE> const & lhs, Vector<RHS, SIZE> const & rhs) {
    return std::transform_reduce(std::begin(lhs), std::end(lhs), std::begin(rhs), std::common_type_t<LHS, RHS>{});
}

template<typename LHS, typename RHS>
[[nodiscard]] constexpr auto cross(Vector<LHS, 3> const & lhs, Vector<RHS, 3> const & rhs) {
    // TODO: Implement.
}

// Element-wise operations

template<typename Component, std::size_t SIZE>
[[nodiscard]] constexpr auto operator - (Vector<Component, SIZE> const & vector) {
    return map<std::negate<>, Component, SIZE>(vector);
}

template<typename LHS, typename RHS, std::size_t SIZE>
[[nodiscard]] constexpr auto operator + (Vector<LHS, SIZE> const & lhs, Vector<RHS, SIZE> const & rhs) {
    return map<std::plus<>, LHS, RHS, SIZE>(lhs, rhs);
}

template<typename LHS, typename RHS, std::size_t SIZE>
[[nodiscard]] constexpr auto operator - (Vector<LHS, SIZE> const & lhs, Vector<RHS, SIZE> const & rhs) {
    return map<std::minus<>, LHS, RHS, SIZE>(lhs, rhs);
}

template<typename LHS, typename RHS, std::size_t SIZE>
[[nodiscard]] constexpr auto operator * (Vector<LHS, SIZE> const & lhs, Vector<RHS, SIZE> const & rhs) {
    return map<std::multiplies<>, LHS, RHS, SIZE>(lhs, rhs);
}

template<typename LHS, typename RHS, std::size_t SIZE>
[[nodiscard]] constexpr auto operator / (Vector<LHS, SIZE> const & lhs, Vector<RHS, SIZE> const & rhs) {
    return map<std::divides<>, LHS, RHS, SIZE>(lhs, rhs);
}

template<typename LHS, typename RHS, std::size_t SIZE>
[[nodiscard]] constexpr auto operator % (Vector<LHS, SIZE> const & lhs, Vector<RHS, SIZE> const & rhs) {
    return map<std::modulus<>, LHS, RHS, SIZE>(lhs, rhs);
}

template<typename LHS, typename RHS, std::size_t SIZE>
[[nodiscard]] constexpr auto operator == (Vector<LHS, SIZE> const & lhs, Vector<RHS, SIZE> const & rhs) {
    return map<std::equal_to<>, LHS, RHS, SIZE>(lhs, rhs);
}

template<typename LHS, typename RHS, std::size_t SIZE>
[[nodiscard]] constexpr auto operator != (Vector<LHS, SIZE> const & lhs, Vector<RHS, SIZE> const & rhs) {
    return map<std::not_equal_to<>, LHS, RHS, SIZE>(lhs, rhs);
}

template<typename LHS, typename RHS, std::size_t SIZE>
[[nodiscard]] constexpr auto operator > (Vector<LHS, SIZE> const & lhs, Vector<RHS, SIZE> const & rhs) {
    return map<std::greater<>, LHS, RHS, SIZE>(lhs, rhs);
}

template<typename LHS, typename RHS, std::size_t SIZE>
[[nodiscard]] constexpr auto operator < (Vector<LHS, SIZE> const & lhs, Vector<RHS, SIZE> const & rhs) {
    return map<std::less<>, LHS, RHS, SIZE>(lhs, rhs);
}

template<typename LHS, typename RHS, std::size_t SIZE>
[[nodiscard]] constexpr auto operator >= (Vector<LHS, SIZE> const & lhs, Vector<RHS, SIZE> const & rhs) {
    return map<std::greater_equal<>, LHS, RHS, SIZE>(lhs, rhs);
}

template<typename LHS, typename RHS, std::size_t SIZE>
[[nodiscard]] constexpr auto operator <= (Vector<LHS, SIZE> const & lhs, Vector<RHS, SIZE> const & rhs) {
    return map<std::less_equal<>, LHS, RHS, SIZE>(lhs, rhs);
}

template<typename LHS, typename RHS, std::size_t SIZE>
[[nodiscard]] constexpr auto operator && (Vector<LHS, SIZE> const & lhs, Vector<RHS, SIZE> const & rhs) {
    return map<std::logical_and<>, LHS, RHS, SIZE>(lhs, rhs);
}

template<typename LHS, typename RHS, std::size_t SIZE>
[[nodiscard]] constexpr auto operator || (Vector<LHS, SIZE> const & lhs, Vector<RHS, SIZE> const & rhs) {
    return map<std::logical_or<>, LHS, RHS, SIZE>(lhs, rhs);
}

template<typename Component, std::size_t SIZE>
[[nodiscard]] constexpr auto operator ! (Vector<Component, SIZE> const & vector) {
    return map<std::logical_not<>, Component, SIZE>(vector);
}

template<typename LHS, typename RHS, std::size_t SIZE>
[[nodiscard]] constexpr auto operator & (Vector<LHS, SIZE> const & lhs, Vector<RHS, SIZE> const & rhs) {
    return map<std::bit_and<>, LHS, RHS, SIZE>(lhs, rhs);
}

template<typename LHS, typename RHS, std::size_t SIZE>
[[nodiscard]] constexpr auto operator | (Vector<LHS, SIZE> const & lhs, Vector<RHS, SIZE> const & rhs) {
    return map<std::bit_or<>, LHS, RHS, SIZE>(lhs, rhs);
}

template<typename LHS, typename RHS, std::size_t SIZE>
[[nodiscard]] constexpr auto operator ^ (Vector<LHS, SIZE> const & lhs, Vector<RHS, SIZE> const & rhs) {
    return map<std::bit_xor<>, LHS, RHS, SIZE>(lhs, rhs);
}

template<typename Component, std::size_t SIZE>
[[nodiscard]] constexpr auto operator ~ (Vector<Component, SIZE> const & vector) {
    return map<std::bit_not<>, Component, SIZE>(vector);
}

// Scalar operations

