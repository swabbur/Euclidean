#pragma once

#include <concepts>

// TODO: Require associativity of addition and multiplication.
// TODO: Require commutativity of addition and multiplication.
// TODO: Require distributivity of multiplication over addition.
// Might be good to automatically generate test cases for these.

// TODO: Require Additive and multiplicative identities.
// TODO: Require Additive inverses.
// TODO: Require Multiplicative inverses.
// Should have some kind of static access to these identities and inverses (additive inverse is negation operator).

/**
 * @tparam Type The type to be evaluated.
 * @see <a href="https://en.wikipedia.org/wiki/Field_(mathematics)">Field (mathematics)</a>
 */
template<typename Type>
concept Field = std::regular<Type> and requires (Type const & lhs, Type const & rhs) {
    { -lhs } -> std::convertible_to<Type>;
    { lhs + rhs } -> std::convertible_to<Type>;
    { lhs - rhs } -> std::convertible_to<Type>;
    { lhs * rhs } -> std::convertible_to<Type>;
    { lhs / rhs } -> std::convertible_to<Type>;
};
