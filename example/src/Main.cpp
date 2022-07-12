#include <euclidean/Matrix.hpp>
#include <iostream>

using namespace Euclidean;

template<typename Element, Size ROWS, Size COLUMNS>
void print(Array<Element, ROWS, COLUMNS> const & matrix) {
    for (Index row = 0; row < ROWS; row++) {
        for (Index column = 0; column < COLUMNS; column++) {
            std::cout << matrix[row, column] << '\t';
        }
        std::cout << '\n';
    }
    std::cout << std::flush;
}

int main() {

    Matrix<int, 2> a = {
            1, 2,
            3, 4
    };

    Matrix<int, 2> b = {
            5, 6,
            7, 8
    };

    print(-a);

    print(a + b);

    print(a - b);

    print(a * b);

    print(2 * a);

    print(a * 2);

    print(a / 2);

    return 0;
}