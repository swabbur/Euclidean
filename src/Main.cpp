#include <euclidean/Vector.hpp>
#include <iostream>

int main() {

    Vector<int, 5> a = { 1 , 2, Vector<int, 2>(3, 4), std::array<int, 1>{5} };
    a = { 2, 3, 4, 5, 6 };
    std::ranges::for_each(a, [](auto const & component) {
        std::cout << component << ' ';
    });
    std::cout << std::endl;

    std::ranges::for_each(a * -a, [](auto const & component) {
        std::cout << component << ' ';
    });
    std::cout << std::endl;

    Vector<int, 5> b = { 1, 2, 3, 4, 5 };
    std::cout << (a == b ? "Identical" : "Different") << std::endl;

    auto [x, y, z] = Vector<int, 3>(1, 2, 3);
    x = 5;
    std::cout << x << ' ' << y << ' ' << z << std::endl;

    return 0;
}