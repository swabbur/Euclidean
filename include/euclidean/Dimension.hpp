#pragma once

#include "Definitions.hpp"
#include "Variance.hpp"

namespace Euclidean {

    template<Variance V, Size S>
    struct Dimension {

        static constexpr auto VARIANCE = V;
        static constexpr auto SIZE = S;

        Dimension() = delete;
    };
}
