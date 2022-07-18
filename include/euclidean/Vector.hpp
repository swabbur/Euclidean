#pragma once

#include "Matrix.hpp"

namespace Euclidean {

    template<Field Component, Size SIZE>
    using Vector = Matrix<Component, SIZE, 1>;

    template<Field Component, Size SIZE>
    using Covector = Matrix<Component, 1, SIZE>;
}
