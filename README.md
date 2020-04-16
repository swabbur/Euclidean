# Euclidian

A header-only C++ library for linear algebra operations with compile-time constant dimensions. Build with the [CMake](https://cmake.org/), tested with [Google Test](https://github.com/google/googletest), and styled based on the Pitchfork Layout ([PFL](https://github.com/vector-of-bool/pitchfork)) and the style guide for python code ([PEP8](https://www.python.org/dev/peps/pep-0008/)).

## Example
Code:
```cpp
Matrix<2, 3> A = {
        2.0f, 0.0f, 0.5f,
        0.0f, 1.0f, 0.5f
};

Vector<3> x = {
        2.0f, 8.0f, 1.0f
};

auto y = dot(A, x);

std::cout << y[0] << ' ' << y[1] << std::endl;
```
Output:
```
4.5 8.5
```
