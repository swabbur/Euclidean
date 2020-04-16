cmake_minimum_required(VERSION 3.13)
project(Euclidian VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_library(Euclidian INTERFACE)
target_include_directories(Euclidian INTERFACE include/)

include(CMakeDependentOption)

cmake_dependent_option(
        EUCLIDIAN_BUILD_TESTS
        "Enable ${PROJECT_NAME} project tests targets" ON
        "BUILD_TESTING" OFF
)

if (EUCLIDIAN_BUILD_TESTS)

    enable_testing()

    find_package(GTest REQUIRED)
    include(GoogleTest REQUIRED)

    add_executable(EuclidianTest tests/euclidian/VectorTest.cpp)
    target_link_libraries(EuclidianTest Euclidian GTest::GTest GTest::Main)
    gtest_discover_tests(EuclidianTest)
endif()
