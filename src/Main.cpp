#include <euclidean/types/Covector.hpp>
#include <euclidean/Iterator.hpp>
#include <euclidean/types/Matrix.hpp>
#include <euclidean/types/Scalar.hpp>
#include <euclidean/types/Vector.hpp>
#include <iostream>


template<Field Component, typename ... Dimensions>
void print(Tensor<Component, Dimensions ...> const & tensor) {
    for (auto const & component : tensor) {
        std::cout << component << ' ';
    }
    std::cout << std::endl;
}

// TODO: Provide a choice between different multiplications (tensor, matrix, element, etc.) at type definition. Only if
//  both sides of a multiplication operation agree on the type to be used is the multiplication performed.



int main() {

    Array<int, 3, 3, 2> array = {

            1, 2, 3,
            4, 5, 6,

            1, 2, 3,
            4, 5, 6,

            1, 2, 3,
            4, 5, 6,
    };

    for (auto const & sub_view : iterate(array)) {
        for (auto const & sub_sub_view : sub_view) {
            for (auto const & element : sub_sub_view) {
                std::cout << element << '\t';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
    std::cout << std::flush;

    return 0;
}
