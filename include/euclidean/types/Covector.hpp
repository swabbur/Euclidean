#pragma once

#include "../Tensor.hpp"

template<Field Component, Size SIZE>
using Covector = Tensor<Component, Dimension<Variance::COVARIANT, SIZE>>;

// TODO: Covector products
