#pragma once

#include <algorithm>
#include <array>
#include <functional>
#include <numeric>
#include <ranges>

// TODO: Add specialization of SIZE = std::dynamic_extent where Vector stores data on the heap.
// TODO: Differentiate between column and row vectors, thus introducing the concept of a transpose and outer product.
// TODO: Add factory methods for generating vectors of zeros, ones, or random components and unit vectors.
// TODO: Differentiate between free vectors and bound vectors to make geometric functions more intuitive and safe.
// TODO: Add explicit casts to a single component, a tuple, an array, a vector, and a span.
// TODO: Differentiate between vectors and unit vectors.
// TODO: Create specialization for gradient vectors.
// TODO: Add definitions for the base/unit vectors x, y, and z.

namespace Euclidean {

    /**
     * An array type with specialized constructors (default and composition) and (element-wise- and scalar-) operators.
     *
     * @tparam Component The type of components stored in the vector.
     * @tparam SIZE The size of the vector.
     */
    template<std::semiregular Component, std::size_t SIZE>
    class Vector {

        /**
         * A meta-class for counting the number of components in a value.
         */
        template<typename>
        struct Count;

        /**
         * A template specialization counting the number of components in a container.
         *
         * @tparam Container The type of container.
         * @tparam C The type of elements stored in the container.
         * @tparam S The size of the container.
         */
        template<template <typename, std::size_t> typename Container, std::convertible_to<Component> E, std::size_t S>
        struct Count<Container<E, S>> {
            static constexpr auto VALUE = S;
        };

        /**
         * A template specialization representing the case in which the given value is convertible to a component.
         *
         * @tparam Value The type of value.
         */
        template<std::convertible_to<Component> Value>
        struct Count<Value> {
            static constexpr auto VALUE = 1;
        };

        /**
         * A count of the number of components in a pack of values.
         *
         * @tparam Values The pack of values to count.
         */
        template<typename ... Values>
        static constexpr auto COUNT = (0 + ... + Count<Values>::VALUE);

        /**
         * Replace the components starting at the given iterator with those stored in the given range by copying them.
         *
         * @tparam Iterator The type of iterator to copy to.
         * @tparam Range The type of of range to copy from.
         * @param iterator The iterator to copy to.
         * @param range The range to copy from.
         * @return The advanced iterator.
         */
        template<std::input_iterator Iterator, std::ranges::range Range>
        static constexpr auto replace(Iterator iterator, Range const & range) noexcept {
            return std::copy(std::begin(range), std::end(range), iterator);
        }

        /**
         * Replace the components starting at the given iterator with those stored in the given range by moving them.
         *
         * @tparam Iterator The type of iterator to move to.
         * @tparam Range The type of of range to move from.
         * @param iterator The iterator to move to.
         * @param range The range to move from.
         * @return The advanced iterator.
         */
        template<std::input_iterator Iterator, std::ranges::range Range>
        static constexpr auto replace(Iterator iterator, Range && range) noexcept {
            return std::move(std::begin(range), std::end(range), iterator);
        }

        /**
         * Replace the component at the given iterator with the given component.
         *
         * @tparam Iterator The type of iterator to move to.
         * @tparam Value The type of value to move.
         * @param iterator The iterator to move to.
         * @param value The value to move.
         * @return The advanced iterator.
         */
        template<std::input_iterator Iterator, std::convertible_to<Component> Value>
        static constexpr auto replace(Iterator iterator, Value && value) noexcept {
            *iterator = std::forward<Value>(value);
            return std::next(iterator);
        }

        std::array<Component, SIZE> components;

    public:

        /**
         * Create a zero-initialized vector.
         */
        [[nodiscard]] constexpr Vector() noexcept : components{} {}

        /**
         * Compose a sequence of values into a vector.
         *
         * @tparam Values The types of values to compose.
         * @param values The values to compose.
         */
        template<typename ... Values>
        requires (COUNT<Values ...> == SIZE)
        [[nodiscard]] constexpr Vector(Values && ... values) noexcept : components() { // NOLINT(google-explicit-constructor)
            auto iterator = std::begin(components);
            ((iterator = replace(iterator, std::forward<Values>(values))), ...);
        }

        /**
         * Iff the vector contains only boolean components, check whether all of the components are true.
         *
         * @return Whether or not all components in the vector are true.
         */
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

    // Tuple-like access

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
    requires requires (Component const & component) { { Operator()(component) }; }
    [[nodiscard]] constexpr auto map(Vector<Component, SIZE> const & vector) {
        Vector<decltype(Operator()(std::declval<Component>())), SIZE> result;
        std::transform(std::begin(vector), std::end(vector), std::begin(result), Operator());
        return result;
    }

    template<typename Operator, typename LHS, typename RHS, std::size_t SIZE>
    requires requires (LHS const & lhs, RHS const & rhs) { { Operator()(lhs, rhs) }; }
    [[nodiscard]] constexpr auto map(Vector<LHS, SIZE> const & lhs, Vector<RHS, SIZE> const & rhs) {
        Vector<decltype(Operator()(std::declval<LHS>(), std::declval<RHS>())), SIZE> result;
        std::transform(std::begin(lhs), std::end(lhs), std::begin(rhs), std::begin(result), Operator());
        return result;
    }

    template<typename Operator, typename LHS, typename RHS, std::size_t SIZE>
    requires requires (LHS & lhs, RHS const & rhs) { { Operator()(lhs, rhs) } -> std::convertible_to<LHS>; }
    constexpr void apply(Vector<LHS, SIZE> & lhs, Vector<RHS, SIZE> const & rhs) {
        std::transform(std::begin(lhs), std::end(lhs), std::begin(rhs), std::begin(lhs), Operator());
    }

    // Element-wise operations (most important: vector addition)

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

    template<typename LHS, typename RHS, std::size_t SIZE>
    constexpr Vector<LHS, SIZE> & operator += (Vector<LHS, SIZE> & lhs, Vector<RHS, SIZE> const & rhs) {
        apply<std::plus<>, LHS, RHS, SIZE>(lhs, rhs);
        return lhs;
    }

    template<typename LHS, typename RHS, std::size_t SIZE>
    constexpr Vector<LHS, SIZE> & operator -= (Vector<LHS, SIZE> const & lhs, Vector<RHS, SIZE> const & rhs) {
        apply<std::minus<>, LHS, RHS, SIZE>(lhs, rhs);
        return lhs;
    }

    template<typename LHS, typename RHS, std::size_t SIZE>
    constexpr Vector<LHS, SIZE> & operator *= (Vector<LHS, SIZE> const & lhs, Vector<RHS, SIZE> const & rhs) {
        apply<std::multiplies<>, LHS, RHS, SIZE>(lhs, rhs);
        return lhs;
    }

    template<typename LHS, typename RHS, std::size_t SIZE>
    constexpr Vector<LHS, SIZE> & operator /= (Vector<LHS, SIZE> const & lhs, Vector<RHS, SIZE> const & rhs) {
        apply<std::divides<>, LHS, RHS, SIZE>(lhs, rhs);
        return lhs;
    }

    template<typename LHS, typename RHS, std::size_t SIZE>
    constexpr Vector<LHS, SIZE> & operator %= (Vector<LHS, SIZE> const & lhs, Vector<RHS, SIZE> const & rhs) {
        apply<std::modulus<>, LHS, RHS, SIZE>(lhs, rhs);
        return lhs;
    }

    template<typename LHS, typename RHS, std::size_t SIZE>
    constexpr Vector<LHS, SIZE> & operator &= (Vector<LHS, SIZE> const & lhs, Vector<RHS, SIZE> const & rhs) {
        apply<std::bit_and<>, LHS, RHS, SIZE>(lhs, rhs);
        return lhs;
    }

    template<typename LHS, typename RHS, std::size_t SIZE>
    constexpr Vector<LHS, SIZE> & operator |= (Vector<LHS, SIZE> const & lhs, Vector<RHS, SIZE> const & rhs) {
        apply<std::bit_or<>, LHS, RHS, SIZE>(lhs, rhs);
        return lhs;
    }

    template<typename LHS, typename RHS, std::size_t SIZE>
    constexpr Vector<LHS, SIZE> & operator ^= (Vector<LHS, SIZE> const & lhs, Vector<RHS, SIZE> const & rhs) {
        apply<std::bit_xor<>, LHS, RHS, SIZE>(lhs, rhs);
        return lhs;
    }

    // Scalar operations (most important: scalar multiplication)

    // TODO: Create vector-component and component-vector functions (*, /, %, etc.).

    // Vector calculus

    template<typename LHS, typename RHS, std::size_t SIZE>
    [[nodiscard]] constexpr auto dot(Vector<LHS, SIZE> const & lhs, Vector<RHS, SIZE> const & rhs) {
        return std::transform_reduce(std::begin(lhs), std::end(lhs), std::begin(rhs), std::common_type_t<LHS, RHS>{});
    }

    template<typename LHS, typename RHS>
    [[nodiscard]] constexpr auto cross(Vector<LHS, 3> const & lhs, Vector<RHS, 3> const & rhs) {
        return Vector<std::common_type_t<LHS, RHS>, 3>{
                lhs[1] * rhs[2] - lhs[2] * rhs[1],
                lhs[2] * rhs[0] - lhs[0] * rhs[2],
                lhs[0] * rhs[1] - lhs[1] * rhs[0]
        };
    }

    // Geometric functions

        // Utility:

    template<typename Component, std::size_t SIZE>
    [[nodiscard]] constexpr auto squared_length(Vector<Component, SIZE> const & vector) {
        return dot(vector, vector);
    }

    template<typename Component, std::size_t SIZE>
    [[nodiscard]] constexpr auto length(Vector<Component, SIZE> const & vector) {
        return sqrt(squared_length(vector));
    }

    template<typename LHS, typename RHS, std::size_t SIZE>
    [[nodiscard]] constexpr auto distance(Vector<LHS, SIZE> const & lhs, Vector<RHS, SIZE> const & rhs) {
        return length(rhs - lhs);
    }

    template<typename Component, std::size_t SIZE>
    [[nodiscard]] constexpr auto normalize(Vector<Component, SIZE> const & vector) {
        return vector / length(vector);
    }
}

// Structured binding decomposition

namespace std {

    template<std::semiregular Type, std::size_t SIZE>
    struct tuple_size<Euclidean::Vector<Type, SIZE>> : integral_constant<std::size_t, SIZE> {};

    template<std::size_t INDEX, std::semiregular Type, std::size_t SIZE>
    struct tuple_element<INDEX, Euclidean::Vector<Type, SIZE>> {
        using type = Type;
    };
}