#pragma once

#include "Definitions.hpp"

namespace Euclidean {

    template<typename Element, Size ... DIMENSIONS>
    requires ((DIMENSIONS > 0) and ...)
    class Array;

    template<typename Element, Size ... DIMENSIONS>
    requires ((DIMENSIONS > 0) and ...)
    class Array {

        template<Index INDEX, Size, Size ... TAIL>
        [[nodiscard]] static constexpr auto get_stride() noexcept {
            if constexpr (INDEX == 0) {
                return (1 * ... * TAIL);
            } else {
                return get_stride<INDEX - 1, TAIL ...>();
            }
        }

        static constexpr auto DEPTH = sizeof ... (DIMENSIONS);
        static constexpr auto SIZE = (1 * ... * DIMENSIONS);
        static constexpr auto STRIDES = [](){
            return []<Index ... INDICES>(std::index_sequence<INDICES ...>){
                return std::index_sequence<get_stride<INDICES, DIMENSIONS ...>() ...>();
            }(std::make_index_sequence<DEPTH>());
        }();

        template<Size ... STRIDES, typename ... Indices>
        [[nodiscard]] static constexpr auto get_index(std::index_sequence<STRIDES ...>, Indices ... indices) noexcept {
            return (0 + ... + (STRIDES * indices));
        }

        template<typename ... Indices>
        [[nodiscard]] static constexpr auto get_index(Indices ... indices) noexcept {
            return get_index(STRIDES, std::forward<Indices>(indices) ...);
        }

        std::array<Element, SIZE> elements;

    public:

        template<typename ... Elements>
        requires (sizeof ... (Elements) == 0 or sizeof ... (Elements) == SIZE) and (std::constructible_from<Element, Elements> and ...)
        [[nodiscard]] constexpr Array(Elements && ... elements) noexcept : elements{ elements ...} {} // NOLINT(google-explicit-constructor)

        template<typename ... Indices>
        requires (sizeof ... (Indices) == DEPTH) and (std::convertible_to<Indices, Index> and ...)
        [[nodiscard]] constexpr Element const & operator [] (Indices && ... indices) const noexcept {
            auto index = get_index(std::forward<Indices>(indices) ...);
            return elements[index];
        }

        template<typename ... Indices>
        requires (std::convertible_to<Indices, Index> and ...) and (sizeof ... (Indices) == DEPTH)
        [[nodiscard]] constexpr Element & operator [] (Indices && ... indices) noexcept {
            auto index = get_index(std::forward<Indices>(indices) ...);
            return elements[index];
        }
    };
}
