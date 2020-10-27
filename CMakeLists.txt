cmake_minimum_required(VERSION 3.13)
project(Euclidean VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_library(Euclidean INTERFACE)
target_include_directories(Euclidean INTERFACE include/)

include(CMakeDependentOption)

cmake_dependent_option(
        EUCLIDEAN_BUILD_TESTS
        "Enable ${PROJECT_NAME} project tests" ON
        "BUILD_TESTING" OFF)

if (EUCLIDEAN_BUILD_TESTS)

    enable_testing()

    find_package(GTest REQUIRED)
    include(GoogleTest REQUIRED)

    add_executable(EuclideanTest
            tests/euclidean/Assertions.cpp
            tests/euclidean/FunctionsTest.cpp
            tests/euclidean/MatrixTest.cpp
            tests/euclidean/VectorTest.cpp)

    target_link_libraries(EuclideanTest Euclidean GTest::GTest GTest::Main)
    gtest_discover_tests(EuclideanTest)
endif()

cmake_dependent_option(
        EUCLIDEAN_BUILD_BENCHMARKS
        "Enable ${PROJECT_NAME} project benchmarks" ON
        "BUILD_BENCHMARKING" OFF)

if (EUCLIDEAN_BUILD_BENCHMARKS)

    find_package(Threads REQUIRED)
    find_package(benchmark REQUIRED)

    add_executable(EuclideanBenchmark
            benchmarks/euclidean/VectorBenchmark.cpp)

    target_link_libraries(EuclideanBenchmark Euclidean benchmark::benchmark benchmark::benchmark_main Threads::Threads)
endif()
