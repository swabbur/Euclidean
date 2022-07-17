#pragma once

#include <concepts>

// TODO: Require associativity of addition and multiplication.
// TODO: Require commutativity of addition and multiplication.
// TODO: Require distributivity over addition.

// TODO: Require additive and multiplicative identities.
// TODO: Require additive inverses.
// TODO: Require multiplicative inverses.

template<typename Element>
concept Field = requires(Element const & lhs, Element const & rhs) {
    { -lhs } -> std::convertible_to<Element>;
    { lhs + rhs } -> std::convertible_to<Element>;
    { lhs - rhs } -> std::convertible_to<Element>;
    { lhs * rhs } -> std::convertible_to<Element>;
    { lhs / rhs } -> std::convertible_to<Element>;
};
