#pragma once

#include "Tensor.hpp"

namespace Euclidean {

//    template<Field Component, Size SIZE>
//    class ColumnVector : public Matrix<Component, SIZE, 1> {
//
//    public:
//
//        template<typename ... Components>
//        [[nodiscard]] constexpr ColumnVector(Components && ... components) noexcept : // NOLINT(google-explicit-constructor)
//                Matrix<Component, SIZE, 1>(std::forward<Components>(components) ...)
//        {}
//    };
//
//    template<Field Component, Size SIZE>
//    using Vector = ColumnVector<Component, SIZE>;
//
//    template<Field Component, Size SIZE>
//    class RowVector : public Matrix<Component, 1, SIZE> {
//
//    public:
//
//        template<typename ... Components>
//        [[nodiscard]] constexpr RowVector(Components && ... components) noexcept : // NOLINT(google-explicit-constructor)
//                Matrix<Component, 1, SIZE>(std::forward<Components>(components) ...)
//        {}
//    };
//
//    template<Field Component, Size SIZE>
//    using Covector = RowVector<Component, SIZE>;
}
