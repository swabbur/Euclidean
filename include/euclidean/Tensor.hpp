#pragma once

#include "Array.hpp"
#include "Dimension.hpp"
#include "Field.hpp"

#include <algorithm>
#include <functional>

namespace Euclidean {

    template<Field Component, typename ... Dimensions>
    requires ((Dimensions::SIZE > 1) and ...)
    class Tensor {

        using ArrayType = Array<Component, Dimensions::SIZE ...>;

        ArrayType array;

    public:

        template<typename ... Components>
        [[nodiscard]] constexpr Tensor(Components && ... components) noexcept :  // NOLINT(google-explicit-constructor)
            array(std::forward<Components>(components) ...)
        {}

        [[nodiscard]] explicit constexpr Tensor(ArrayType const & array) noexcept : array(array) {}

        [[nodiscard]] explicit constexpr Tensor(ArrayType && array) noexcept : array(array) {}

        [[nodiscard]] constexpr operator ArrayType const & () const { // NOLINT(google-explicit-constructor)
            return array;
        }

        [[nodiscard]] constexpr operator ArrayType & () { // NOLINT(google-explicit-constructor)
            return array;
        }

        template<typename ... Indices>
        [[nodiscard]] constexpr Component const & operator [] (Indices && ... indices) const noexcept {
            return array[std::forward<Indices>(indices) ...];
        }

        template<typename ... Indices>
        [[nodiscard]] constexpr Component & operator [] (Indices && ... indices) noexcept {
            return array[std::forward<Indices>(indices) ...];
        }

        [[nodiscard]] constexpr bool operator <=> (Tensor<Component, Dimensions ...> const & rhs) const noexcept {
            return array <=> rhs;
        }

        [[nodiscard]] constexpr auto begin() const noexcept {
            return array.begin();
        }

        [[nodiscard]] constexpr auto begin() noexcept {
            return array.begin();
        }

        [[nodiscard]] constexpr auto end() const noexcept {
            return array.end();
        }

        [[nodiscard]] constexpr auto end() noexcept {
            return array.end();
        }
    };
}
