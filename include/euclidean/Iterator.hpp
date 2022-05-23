#pragma once

#include "Array.hpp"

template<typename Element, std::size_t HEAD, std::size_t ... TAIL>
class View;

template<typename Element, std::size_t HEAD, std::size_t ... TAIL>
class Iterator {

    static constexpr auto STRIDE = (1 * ... * TAIL);

    Element * const pointer;
    std::size_t index;

public:

    [[nodiscard]] explicit constexpr Iterator(Element * pointer, std::size_t index) noexcept
            : pointer(pointer), index(index)
    {}

    [[nodiscard]] constexpr bool operator == (Iterator<Element, HEAD, TAIL ...> const & iterator) const noexcept {
        return pointer == iterator.pointer and index == iterator.index;
    }

    [[nodiscard]] constexpr auto operator * () const noexcept {
        return View<Element, TAIL ...>(pointer + index);
    }

    [[nodiscard]] constexpr auto & operator ++ () noexcept {
        index += STRIDE;
        return *this;
    }
};

template<typename Element, std::size_t HEAD, std::size_t ... TAIL>
class View {

    static constexpr auto STRIDE = (1 * ... * TAIL);
    static constexpr auto END_OFFSET = HEAD * STRIDE;

    Element * const pointer;

public:

    [[nodiscard]] explicit constexpr View(Element * pointer) noexcept : pointer(pointer) {}

    [[nodiscard]] constexpr auto begin() const noexcept {
        if constexpr (sizeof ... (TAIL) == 0) {
            return pointer;
        } else {
            return Iterator<Element, HEAD, TAIL ...>(pointer, 0);
        }
    }

    [[nodiscard]] constexpr auto end() const noexcept {
        if constexpr (sizeof ... (TAIL) == 0) {
            return pointer + END_OFFSET;
        } else {
            return Iterator<Element, HEAD, TAIL ...>(pointer, END_OFFSET);
        }
    }
};

template<typename Element, std::size_t ... SIZES>
[[nodiscard]] constexpr auto iterate(Array<Element, SIZES ...> const & array) {
    return View<Element const, SIZES ...>(array);
}


template<typename Element, std::size_t ... SIZES>
[[nodiscard]] constexpr auto iterate(Array<Element, SIZES ...> & array) {
    return View<Element, SIZES ...>((Element *)&array);
}
