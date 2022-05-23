#pragma once

#include "../Tensor.hpp"

template<Field Component>
using Scalar = Tensor<Component>;

template<Field C1, Field C2, typename ... DS, Field R = std::invoke_result_t<std::multiplies<>, C1, C2>>
requires requires (C1 c1, C2 c2) { { c1 * c2 } -> std::convertible_to<R>; }
constexpr Tensor<R, DS ...> operator * (Tensor<C1, DS ...> const & lhs, C2 const & rhs) noexcept {
    Tensor<R, DS ...> result;
    std::transform(std::begin(lhs), std::end(lhs), std::begin(result), [&rhs](auto const & component) {
        return component * rhs;
    });
    return result;
}

template<Field C1, Field C2, typename ... DS, Field R = std::invoke_result_t<std::multiplies<>, C1, C2>>
requires requires (C1 c1, C2 c2) { { c1 * c2 } -> std::convertible_to<R>; }
constexpr Tensor<R, DS ...> operator * (C1 const & lhs, Tensor<C2, DS ...> const & rhs) noexcept {
    Tensor<R, DS ...> result;
    std::transform(std::begin(rhs), std::end(rhs), std::begin(result), [&lhs](auto const & component) {
        return lhs * component;
    });
    return result;
}

template<Field C1, Field C2, typename ... DS>
requires requires (C1 c1, C2 c2) { { c1 * c2 } -> std::convertible_to<C1>; }
constexpr Tensor<C1, DS ...> & operator *= (Tensor<C1, DS ...> & lhs, C2 const & rhs) noexcept {
    std::transform(std::begin(lhs), std::end(lhs), std::begin(lhs), [&rhs](auto const & component) {
        return component * rhs;
    });
    return lhs;
}

template<Field C1, Field C2, typename ... DS, Field R = std::invoke_result_t<std::divides<>, C1, C2>>
requires requires (C1 c1, C2 c2) { { c1 / c2 } -> std::convertible_to<R>; }
constexpr Tensor<R, DS ...> operator / (Tensor<C1, DS ...> const & lhs, C2 const & rhs) noexcept {
    Tensor<R, DS ...> result;
    std::transform(std::begin(lhs), std::end(lhs), std::begin(result), [&rhs](auto const & component) {
        return component / rhs;
    });
    return result;
}

template<Field C1, Field C2, typename ... DS, Field R = std::invoke_result_t<std::divides<>, C1, C2>>
requires requires (C1 c1, C2 c2) { { c1 / c2 } -> std::convertible_to<R>; }
constexpr Tensor<R, DS ...> operator / (C1 const & lhs, Tensor<C2, DS ...> const & rhs) noexcept {
    Tensor<R, DS ...> result;
    std::transform(std::begin(rhs), std::end(rhs), std::begin(result), [&lhs](auto const & component) {
        return lhs / component;
    });
    return result;
}

template<Field C1, Field C2, typename ... DS>
requires requires (C1 c1, C2 c2) { { c1 / c2 } -> std::convertible_to<C1>; }
constexpr Tensor<C1, DS ...> & operator /= (Tensor<C1, DS ...> & lhs, C2 const & rhs) noexcept {
    std::transform(std::begin(lhs), std::end(lhs), std::begin(lhs), [&rhs](auto const & component) {
        return component / rhs;
    });
    return lhs;
}
