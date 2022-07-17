#pragma once

#include "Tensor.hpp"

namespace Euclidean {

    template<Field Component, Size ROWS, Size COLUMNS = ROWS>
    class Matrix {

        using TensorType = Tensor<Component, Dimension<Variance::COVARIANT, ROWS>, Dimension<Variance::CONTRAVARIANT, COLUMNS>>;
        using ArrayType = Array<Component, ROWS, COLUMNS>;

        TensorType tensor;

    public:

        template<typename ... Components>
        [[nodiscard]] constexpr Matrix(Components && ... components) noexcept : // NOLINT(google-explicit-constructor)
            tensor(std::forward<Components>(components) ...)
        {}

        [[nodiscard]] explicit constexpr Matrix(TensorType const & tensor) noexcept : tensor(tensor) {}

        [[nodiscard]] explicit constexpr Matrix(TensorType && tensor) noexcept : tensor(tensor) {}

        [[nodiscard]] explicit constexpr Matrix(ArrayType const & array) noexcept : tensor(array) {}

        [[nodiscard]] explicit constexpr Matrix(ArrayType && array) noexcept : tensor(array) {}

        [[nodiscard]] constexpr operator TensorType const & () const { // NOLINT(google-explicit-constructor)
            return tensor;
        }

        [[nodiscard]] constexpr operator TensorType & () { // NOLINT(google-explicit-constructor)
            return tensor;
        }

        [[nodiscard]] constexpr operator ArrayType const & () const { // NOLINT(google-explicit-constructor)
            return static_cast<ArrayType const &>(tensor);
        }

        [[nodiscard]] constexpr operator ArrayType & () { // NOLINT(google-explicit-constructor)
            return static_cast<ArrayType &>(tensor);
        }

        template<typename ... Indices>
        [[nodiscard]] constexpr Component const & operator [] (Indices && ... indices) const noexcept {
            return tensor[std::forward<Indices>(indices) ...];
        }

        template<typename ... Indices>
        [[nodiscard]] constexpr Component & operator [] (Indices && ... indices) noexcept {
            return tensor[std::forward<Indices>(indices) ...];
        }

        [[nodiscard]] constexpr bool operator <=> (TensorType const & rhs) const noexcept {
            return tensor <=> rhs;
        }

        [[nodiscard]] constexpr auto begin() const noexcept {
            return tensor.begin();
        }

        [[nodiscard]] constexpr auto begin() noexcept {
            return tensor.begin();
        }

        [[nodiscard]] constexpr auto end() const noexcept {
            return tensor.end();
        }

        [[nodiscard]] constexpr auto end() noexcept {
            return tensor.end();
        }

        [[nodiscard]] constexpr Matrix<Component, ROWS, COLUMNS> operator - () const noexcept {
            return -tensor;
        }

        [[nodiscard]] constexpr Matrix<Component, ROWS, COLUMNS> operator + (Matrix<Component, ROWS, COLUMNS> const & rhs) const noexcept {
            return tensor + rhs;
        }

        constexpr Matrix<Component, ROWS, COLUMNS> & operator += (Matrix<Component, ROWS, COLUMNS> const & rhs) noexcept {
            return tensor += rhs;
        }

        [[nodiscard]] constexpr Matrix<Component, ROWS, COLUMNS> operator - (Matrix<Component, ROWS, COLUMNS> const & rhs) const noexcept {
            return tensor - rhs;
        }

        constexpr Matrix<Component, ROWS, COLUMNS> & operator -= (Matrix<Component, ROWS, COLUMNS> const & rhs) noexcept {
            return tensor -= rhs;
        }

        template<Size SIZE>
        [[nodiscard]] constexpr Matrix<Component, ROWS> operator * (Matrix<Component, COLUMNS, SIZE> const & rhs) const noexcept {
            Matrix<Component, ROWS, SIZE> result;
            for (Index row = 0; row < ROWS; row++) {
                for (Index size = 0; size < SIZE; size++) {
                    result[row, size] = 0;
                    for (Index column = 0; column < COLUMNS; column++) {
                        result[row, size] += (*this)[row, column] * rhs[column, size];
                    }
                }
            }
            return result;
        }

        template<Size RHS_COLUMNS>
        requires (ROWS == RHS_COLUMNS)
        constexpr Matrix<Component, ROWS> & operator *= (Matrix<Component, ROWS, RHS_COLUMNS> const & rhs) noexcept {
            return operator=(operator*(rhs));
        }
    };
}
