#pragma once

#include "Array.hpp"
#include "Field.hpp"

#include <algorithm>
#include <functional>

namespace Euclidean {

    template<Field Component, Size ROWS, Size COLUMNS = ROWS>
    class Matrix : public Array<Component, ROWS * COLUMNS> {

    public:

        template<typename ... Components>
        [[nodiscard]] constexpr Matrix(Components && ... components) noexcept : // NOLINT(google-explicit-constructor)
                Array<Component, ROWS * COLUMNS>(std::forward<Components>(components) ...)
        {}

        template<typename ReturnType = Component>
        requires std::derived_from<ReturnType, Component> and (ROWS == 1) and (COLUMNS == 1)
        [[nodiscard]] constexpr operator ReturnType const & () const noexcept { // NOLINT(google-explicit-constructor)
            return (*this)[0];
        }

        [[nodiscard]] constexpr Matrix<Component, ROWS, COLUMNS> operator - () const noexcept {
            Matrix<Component, ROWS, COLUMNS> negative;
            std::transform(std::begin(*this), std::end(*this), std::begin(negative), std::negate<>());
            return negative;
        }

        [[nodiscard]] constexpr Matrix<Component, ROWS, COLUMNS> operator + (Matrix<Component, ROWS, COLUMNS> const & rhs) const noexcept {
            Matrix<Component, ROWS, COLUMNS> sum;
            std::transform(std::begin(*this), std::end(*this), std::begin(rhs), std::begin(sum), std::plus<>());
            return sum;
        }

        constexpr Matrix<Component, ROWS, COLUMNS> & operator += (Matrix<Component, ROWS, COLUMNS> const & rhs) noexcept {
            std::transform(std::begin(*this), std::end(*this), std::begin(rhs), std::begin(*this), std::plus<>());
            return *this;
        }

        [[nodiscard]] constexpr Matrix<Component, ROWS, COLUMNS> operator - (Matrix<Component, ROWS, COLUMNS> const & rhs) const noexcept {
            Matrix<Component, ROWS, COLUMNS> difference;
            std::transform(std::begin(*this), std::end(*this), std::begin(rhs), std::begin(difference), std::minus<>());
            return difference;
        }

        constexpr Matrix<Component, ROWS, COLUMNS> & operator -= (Matrix<Component, ROWS, COLUMNS> const & rhs) noexcept {
            std::transform(std::begin(*this), std::end(*this), std::begin(rhs), std::begin(*this), std::minus<>());
            return *this;
        }

        template<Size SIZE>
        [[nodiscard]] constexpr Matrix<Component, ROWS, SIZE> operator * (Matrix<Component, COLUMNS, SIZE> const & rhs) const noexcept {
            Matrix<Component, ROWS, SIZE> product;
            for (Index row = 0; row < ROWS; row++) {
                for (Index size = 0; size < SIZE; size++) {
                    product[row, size] = 0;
                    for (Index column = 0; column < COLUMNS; column++) {
                        product[row, size] += (*this)[row, column] * rhs[column, size];
                    }
                }
            }
            return product;
        }

        template<Size R = ROWS, Size C = COLUMNS>
        requires (R == ROWS) and (C == COLUMNS)
        constexpr Matrix<Component, ROWS> & operator *= (Matrix<Component, R, C> const & rhs) noexcept {
            return operator=(operator*(rhs));
        }
    };
}
