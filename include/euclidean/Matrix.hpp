#pragma once

#include "Assert.hpp"
#include "Definitions.hpp"

#include <array>

namespace Euclidean {

    template<typename Element, Size ROWS, Size COLUMNS>
    requires (ROWS > 0 and COLUMNS > 0)
    struct Matrix {

        static constexpr Size SIZE = ROWS * COLUMNS;

        std::array<Element, SIZE> elements;

        template<typename ... Elements>
        requires (std::convertible_to<Element, Elements> and ...) and (sizeof ... (Elements) == 0 or sizeof ... (Elements) == SIZE)
        constexpr Matrix(Elements && ... elements) : elements{ Element(elements) ... } {} // NOLINT(google-explicit-constructor)

        constexpr Element const & operator [] (Index index) const {
            assert_bounds(index, SIZE);
            return elements[index];
        }

        constexpr Element & operator [] (Index index) {
            assert_bounds(index, SIZE);
            return elements[index];
        }

//        constexpr Element const & operator [] (Index row, Index column) const {
//            return operator [] (row * COLUMNS + column);
//        }

//        constexpr Element & operator [] (Index row, Index column) {
//            return operator [] (row * COLUMNS + column);
//        }

        constexpr auto begin() const {
            return std::cbegin(elements);
        }

        constexpr auto end() const {
            return std::cend(elements);
        }

        constexpr auto begin() {
            return std::begin(elements);
        }

        constexpr auto end() {
            return std::end(elements);
        }
    };

    template<typename Element, Size ROWS, Size COLUMNS>
    constexpr auto operator - (Matrix<Element, ROWS, COLUMNS> const & matrix) {
        using NegatedElement = decltype(std::negate<>(std::declval<Element>()));
        Matrix<NegatedElement, ROWS, COLUMNS> negated_matrix;
        std::transform(std::begin(matrix), std::end(matrix), std::begin(negated_matrix), std::negate<>());
        return negated_matrix;
    }
}
