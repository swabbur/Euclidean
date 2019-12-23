# Euclidian

...

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
