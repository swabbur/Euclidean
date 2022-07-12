#pragma once

#include "Array.hpp"

namespace Euclidean {

    template<typename Element, Size ROWS, Size COLUMNS = ROWS>
    requires (ROWS > 0 and COLUMNS > 0)
    class Matrix : public Array<Element, ROWS, COLUMNS> {

    public:

        template<typename ... Elements>
        [[nodiscard]] constexpr Matrix(Elements && ... elements) noexcept : Array<Element, ROWS, COLUMNS>(elements ...) {} // NOLINT(google-explicit-constructor)
    };

    template<typename LHS, Size N, Size M>
    [[nodiscard]] constexpr auto operator - (Matrix<LHS, N, M> const & lhs) noexcept {
        using R = decltype(-std::declval<LHS>());
        Matrix<R, N, M> result;
        for (Index n = 0; n < N; n++) {
            for (Index m = 0; m < M; m++) {
                result[n, m] = -lhs[n, m] ;
            }
        }
        return result;
    }

    template<typename LHS, typename RHS, Size N, Size M>
    [[nodiscard]] constexpr auto operator + (Matrix<LHS, N, M> const & lhs, Matrix<RHS, N, M> const & rhs) noexcept {
        using R = decltype(std::declval<LHS>() + std::declval<RHS>());
        Matrix<R, N, M> result;
        for (Index n = 0; n < N; n++) {
            for (Index m = 0; m < M; m++) {
                result[n, m] = lhs[n, m] + rhs[n, m];
            }
        }
        return result;
    }

    template<typename LHS, typename RHS, Size N, Size M>
    [[nodiscard]] constexpr auto operator - (Matrix<LHS, N, M> const & lhs, Matrix<RHS, N, M> const & rhs) noexcept {
        using R = decltype(std::declval<LHS>() - std::declval<RHS>());
        Matrix<R, N, M> result;
        for (Index n = 0; n < N; n++) {
            for (Index m = 0; m < M; m++) {
                result[n, m] = lhs[n, m] - rhs[n, m];
            }
        }
        return result;
    }

    template<typename LHS, typename RHS, Size N, Size M, Size P>
    [[nodiscard]] constexpr auto operator * (Matrix<LHS, N, M> const & lhs, Matrix<RHS, M, P> const & rhs) noexcept {
        using R = decltype(std::declval<LHS>() * std::declval<RHS>());
        Matrix<R, N, P> result;
        for (Index n = 0; n < N; n++) {
            for (Index p = 0; p < P; p++) {
                result[n, p] = 0;
                for (Index m = 0; m < M; m++) {
                    result[n, p] += lhs[n, m] * rhs[m, p];
                }
            }
        }
        return result;
    }

    template<typename LHS, typename RHS, Size N, Size M>
    [[nodiscard]] constexpr auto operator * (LHS const & lhs, Matrix<RHS, N, M> const & rhs) noexcept {
        using R = decltype(std::declval<LHS>() * std::declval<RHS>());
        Matrix<R, N, M> result;
        for (Index n = 0; n < N; n++) {
            for (Index m = 0; m < M; m++) {
                result[n, m] = lhs * rhs[n, m];
            }
        }
        return result;
    }

    template<typename LHS, typename RHS, Size N, Size M>
    [[nodiscard]] constexpr auto operator * (Matrix<LHS, N, M> const & lhs, RHS const & rhs) noexcept {
        using R = decltype(std::declval<LHS>() * std::declval<RHS>());
        Matrix<R, N, M> result;
        for (Index n = 0; n < N; n++) {
            for (Index m = 0; m < M; m++) {
                result[n, m] = lhs[n, m] * rhs;
            }
        }
        return result;
    }

    template<typename LHS, typename RHS, Size N, Size M>
    [[nodiscard]] constexpr auto operator / (Matrix<LHS, N, M> const & lhs, RHS const & rhs) noexcept {
        using R = decltype(std::declval<LHS>() / std::declval<RHS>());
        Matrix<R, N, M> result;
        for (Index n = 0; n < N; n++) {
            for (Index m = 0; m < M; m++) {
                result[n, m] = lhs[n, m] / rhs;
            }
        }
        return result;
    }
}
