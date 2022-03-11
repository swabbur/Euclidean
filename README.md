# Euclidean

A header-only C++ library implementing linear algebra operations with compile-time constant dimensions using STL algorithms and template metaprogramming, build with [CMake](https://cmake.org/), tested with [Catch2](https://github.com/catchorg/Catch2) and styled based on the Pitchfork Layout ([PFL](https://github.com/vector-of-bool/pitchfork)) and the style guide for python code ([PEP8](https://www.python.org/dev/peps/pep-0008/)).

Do not forget to pass CMake the `-DBUILD_TESTING=ON` option to enable unit testing.

![Continuous Integration](https://github.com/swabbur/Euclidian/workflows/Continuous%20Integration/badge.svg)

## Features

### Composition
Composition constructors make it a lot easier to construct larger and more complex vectors from smaller ones.
```cpp
Vector<float, 5> vector(1.0f, 2.0f, Vector<float, 2>(3.0f, 4.0f), 5.0f);
```

### STL Compatibility
Vector and Matrix classes are written to be used with existing STL algorithm.
```cpp
Vector<3> vector;
std::fill(std::begin(vector), std::end(vector), 1.0f);
```

### Implicit Constructors
Implicit constructors allow for readable vector and matrix definitions.
```cpp
Matrix<float, 3, 3> matrix = {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
};
```

## Upcoming Features
- Quaternions
