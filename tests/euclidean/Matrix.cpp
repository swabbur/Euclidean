#include <catch2/catch_test_macros.hpp>
#include <euclidean/Matrix.hpp>

using Element = std::int32_t;

template<typename Element, std::size_t ROWS, std::size_t COLUMNS>
static void require(Euclidean::Matrix<Element, ROWS, COLUMNS> const & matrix,
                    std::array<Element, ROWS * COLUMNS> const & array) {
    for (std::size_t i = 0; i < ROWS; i++) {
        for (std::size_t j = 0; j <  COLUMNS; j++) {
            REQUIRE(matrix[i, j] == array[i * COLUMNS + j]);
        }
    }
}

TEST_CASE("default constructor", "[matrix]") {
    Euclidean::Matrix<Element, 2, 3> matrix;
    require(matrix, {
        0, 0, 0,
        0, 0, 0,
    });
}

TEST_CASE("default implicit constructor", "[matrix]") {
    Euclidean::Matrix<Element, 2, 3> matrix = {};
    require(matrix, {
            0, 0, 0,
            0, 0, 0,
    });
}

TEST_CASE("implicit constructor", "[matrix]") {
    Euclidean::Matrix<Element, 2, 3> matrix = {
            1, 2, 3,
            4, 5, 6,
    };
    require(matrix, {
            1, 2, 3,
            4, 5, 6,
    });
}
