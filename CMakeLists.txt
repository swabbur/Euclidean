cmake_minimum_required(VERSION 3.18)
project(Euclidean VERSION 1.0.0 LANGUAGES CXX)

# Configure CMake
set(CMAKE_CXX_STANDARD 23)
include(CMakeDependentOption)

# Create library
add_library(Euclidean INTERFACE)
target_include_directories(Euclidean INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

# Create example executable
add_executable(EuclideanExample src/Main.cpp)
target_link_libraries(EuclideanExample Euclidean)

# Disable tests by default
cmake_dependent_option(
        EUCLIDEAN_BUILD_TESTS
        "Enable ${PROJECT_NAME} project tests" ON
        "BUILD_TESTING" OFF)

# Load catch2 via conan
if (EUCLIDEAN_BUILD_TESTS)

    # Download cmake conan utility
    if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
        message(STATUS "Downloading conan CMake utility")
        file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake")
    endif()

    # Install libraries
    include("${CMAKE_BINARY_DIR}/conan.cmake")
    conan_cmake_install(PATH_OR_REFERENCE "${CMAKE_CURRENT_LIST_DIR}" BUILD missing)

    # Include libraries as cmake packages
    include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    conan_basic_setup(TARGETS)
endif()

# Build tests
if (EUCLIDEAN_BUILD_TESTS)
    file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/tests/*.cpp")
    add_executable(EuclideanTest ${TEST_SOURCES})
    target_link_libraries(EuclideanTest Euclidean CONAN_PKG::catch2)
endif()
