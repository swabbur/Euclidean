#include <euclidean/Matrix.hpp>
#include <iostream>

using namespace Euclidean;

template<Field Component, Size ROWS, Size COLUMNS>
void print(Matrix<Component, ROWS, COLUMNS> const & matrix) {
    for (Index row = 0; row < ROWS; row++) {
        for (Index column = 0; column < COLUMNS; column++) {
            std::cout << matrix[row, column] << '\t';
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
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

    return 0;
}