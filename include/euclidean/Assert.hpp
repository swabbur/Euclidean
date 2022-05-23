#pragma once

#include <functional>
#include <iostream>

#ifdef _DEBUG
    #define assert(condition, message) [=]() {                                                \
        if (not(condition)) {                                                                 \
            std::cerr << "An error occurred at " << (__FILE__) << ':' << (__LINE__) << ":\n"; \
            std::cerr << message << std::endl;                                                \
            std::exit(1);                                                                     \
        }                                                                                     \
    }()

    #define assert_bounds(index, size) [=]() {                                                                 \
        assert(index >= 0 && index < size, "Index (" << index << ") out of bounds [0-" << (size - 1) << "]."); \
    }()
#else
    #define assert(condition, message) [=]() {}()
    #define assert_bounds(index, size) [=]() {}()
#endif
