#pragma once

#include "../Tensor.hpp"

template<Field Component, Size SIZE>
using Vector = Tensor<Component, Dimension<Variance::CONTRAVARIANT, SIZE>>;

// TODO: Vector products