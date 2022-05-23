#pragma once

#include "Assert.hpp"

#include <array>

template<typename Element, std::size_t ... SIZES>
requires ((SIZES > 0) and ...)
class Array {

    template<std::size_t INDEX, std::size_t, std::size_t ... TAIL>
    [[nodiscard]] static constexpr auto stride() noexcept {
        if constexpr (INDEX == 0) {
            return (1 * ... * TAIL);
        } else {
            return stride<INDEX - 1, TAIL ...>();
        }
    }

    static constexpr auto DEPTH = sizeof ... (SIZES);
    static constexpr auto SIZE = (1 * ... * SIZES);
    static constexpr auto STRIDES = [](){
        return []<std::size_t ... INDICES>(std::index_sequence<INDICES ...>){
            return std::index_sequence<stride<INDICES, SIZES ...>() ...>();
        }(std::make_index_sequence<DEPTH>());
    }();

    template<std::size_t ... STRIDES, typename ... Indices>
    [[nodiscard]] static constexpr auto index(std::index_sequence<STRIDES ...>, Indices ... indices) noexcept {
        return (0 + ... + (STRIDES * indices));
    }

    template<typename ... Indices>
    [[nodiscard]] static constexpr auto index(Indices ... indices) noexcept {
        return index(STRIDES, std::forward<Indices>(indices) ...);
    }

    std::array<Element, SIZE> elements;

public:

    template<typename ... Elements>
    requires (sizeof ... (Elements) == 0 or sizeof ... (Elements) == SIZE)
             and (std::constructible_from<Element, Elements> and ...)
    [[nodiscard]] constexpr Array(Elements && ... elements) noexcept : elements { std::forward<Elements>(elements) ... } {} // NOLINT(google-explicit-constructor)

    template<typename ... Indices>
    requires (sizeof ... (Indices) == DEPTH) and (std::convertible_to<Indices, std::size_t> and ...)
    [[nodiscard]] constexpr Element const & at(Indices && ... indices) const noexcept {
        return elements[index(std::forward<Indices>(indices) ...)];
    }

    template<typename ... Indices>
    requires (sizeof ... (Indices) == DEPTH) and (std::convertible_to<Indices, std::size_t> and ...)
    [[nodiscard]] constexpr Element & at(Indices && ... indices) noexcept {
        return elements[index(std::forward<Indices>(indices) ...)];
    }

    [[nodiscard]] constexpr auto begin() const noexcept {
        return elements.begin();
    }

    [[nodiscard]] constexpr auto begin() noexcept {
        return elements.begin();
    }

    [[nodiscard]] constexpr auto end() const noexcept {
        return elements.end();
    }

    [[nodiscard]] constexpr auto end() noexcept {
        return elements.end();
    }

    [[nodiscard]] constexpr Element const & operator [] (std::size_t index) const noexcept {
        assert_bounds(index, SIZE);
        return elements[index];
    }

    [[nodiscard]] constexpr Element & operator [] (std::size_t index) noexcept {
        assert_bounds(index, SIZE);
        return elements[index];
    }

    [[nodiscard]] constexpr bool operator == (Array<Element, SIZES ...> const & array) const noexcept {
        return elements == array.elements;
    }
};
