# Euclidian

A header-only C++ library implementing linear algebra operations with compile-time constant dimensions using STL algorithms and template metaprogramming, build with [CMake](https://cmake.org/), tested with [Google Test](https://github.com/google/googletest), and styled based on the Pitchfork Layout ([PFL](https://github.com/vector-of-bool/pitchfork)) and the style guide for python code ([PEP8](https://www.python.org/dev/peps/pep-0008/)).

Do not forget to pass the `-DBUILD_TESTING=ON` option to CMake to enable unit testing.

![Continuous Integration](https://github.com/swabbur/Euclidian/workflows/Continuous%20Integration/badge.svg)

## Features

### Composition
Composition constructors make it a lot easier to construct larger and more complex vectors from smaller ones.
```cpp
Vector<5> vector(1.0f, 2.0f, Vector<2>(3.0f, 4.0f), 5.0f);
```

### STL Compatibility
An important but often overlooked feature is STL compatibility. Which allows the Vector and Matrix classes to be used with existing STL algorithm.
```cpp
Vector<3> vector;
std::fill(std::begin(vector), std::end(vector), 1.0f);
```

### Implicit Constructors
Implicit constructors, while not always optimal, allow for better readable matrix definitions.
```cpp
Matrix<3, 3> matrix = {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
};
```

## Upcoming Features
- Quaternions
