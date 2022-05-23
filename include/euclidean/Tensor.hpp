#pragma once

#include "Array.hpp"
#include "Dimension.hpp"
#include "Field.hpp"

#include <algorithm>
#include <numeric>
#include <functional>

template<Field Component, typename ... Dimensions>
requires ((Dimensions::SIZE > 1) and ...)
class Tensor : public Array<Component, Dimensions::SIZE ...> {

public:

    template<typename ... Components>
    constexpr Tensor(Components ... components) noexcept : Array<Component, Dimensions::SIZE ...>(std::forward<Components>(components) ...) {} // NOLINT(google-explicit-constructor)
};

template<Field C, typename ... DS, typename R = std::invoke_result_t<std::negate<>, C>>
requires requires (C c) { { -c } -> std::convertible_to<R>; }
constexpr Tensor<R, DS ...> operator - (Tensor<C, DS ...> const & lhs) noexcept {
    Tensor<R, DS ...> result;
    std::transform(std::begin(lhs), std::end(lhs), std::begin(result), std::negate<>());
    return result;
}

template<Field C1, Field C2, typename ... DS, Field R = std::invoke_result_t<std::plus<>, C1, C2>>
requires requires (C1 c1, C2 c2) { { c1 + c2 } -> std::convertible_to<R>; }
constexpr Tensor<R, DS ...> operator + (Tensor<C1, DS ...> const & lhs, Tensor<C2, DS ...> const & rhs) noexcept {
    Tensor<R, DS ...> result;
    std::transform(std::begin(lhs), std::end(lhs), std::begin(rhs), std::begin(result), std::plus<>());
    return result;
}

template<Field C1, Field C2, typename ... DS>
requires requires (C1 c1, C2 c2) { { c1 + c2 } -> std::convertible_to<C1>; }
constexpr Tensor<C1, DS ...> & operator += (Tensor<C1, DS ...> & lhs, Tensor<C2, DS ...> const & rhs) noexcept {
    std::transform(std::begin(lhs), std::end(lhs), std::begin(rhs), std::begin(lhs), std::plus<>());
    return lhs;
}

template<Field C1, Field C2, typename ... DS, Field R = std::invoke_result_t<std::minus<>, C1, C2>>
requires requires (C1 c1, C2 c2) { { c1 - c2 } -> std::convertible_to<R>; }
constexpr Tensor<R, DS ...> operator - (Tensor<C1, DS ...> const & lhs, Tensor<C2, DS ...> const & rhs) noexcept {
    Tensor<R, DS ...> result;
    std::transform(std::begin(lhs), std::end(lhs), std::begin(rhs), std::begin(result), std::minus<>());
    return result;
}

template<Field C1, Field C2, typename ... DS>
requires requires (C1 c1, C2 c2) { { c1 - c2 } -> std::convertible_to<C1>; }
constexpr Tensor<C1, DS ...> & operator -= (Tensor<C1, DS ...> & lhs, Tensor<C2, DS ...> const & rhs) noexcept {
    std::transform(std::begin(lhs), std::end(lhs), std::begin(rhs), std::begin(lhs), std::minus<>());
    return lhs;
}

//template<Field Component, typename ... Ds1, typename ... Ds2>
//Tensor<Component, Ds1 ..., Ds2 ...> tensor_product(Tensor<Component, Ds1 ...> const & lhs, Tensor<Component, Ds2 ...> const & rhs) {
//    constexpr auto SIZE_1 = (1 * ... * Ds1::SIZE);
//    constexpr auto SIZE_2 = (1 * ... * Ds2::SIZE);
//    Tensor<Component, Ds1 ..., Ds2 ...> result;
//    for (std::size_t j = 0; j < SIZE_2; j++) {
//        for (std::size_t i = 0; i <SIZE_1; i++) {
//            result[i * SIZE_2 + j] = rhs[j] * lhs[i];
//        }
//    }
//    return result;
//}

//template<std::size_t I, std::size_t J, Field Component, typename ... Dimensions>
//requires (I != J) and (I < sizeof ... (Dimensions)) and (J < sizeof ... (Dimensions))
//Tensor<Component, Dimensions ...> tensor_contraction(Tensor<Component, Dimensions ...> const & tensor) {
//    // TODO: Perform contraction.
//    return tensor;
//}
