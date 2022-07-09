cmake_minimum_required(VERSION 3.18)
project(Euclidean VERSION 1.0.0 LANGUAGES C CXX)

# Configure CMake
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
include(CMakeDependentOption)

# Create library
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)

    # Find test packages
    find_package(Catch2 3 REQUIRED)

    # Find test sources
    file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/tests/*.cpp")

    # Create test executable
    add_executable(${PROJECT_NAME}Test ${TEST_SOURCES})
    target_link_libraries(${PROJECT_NAME}Test ${PROJECT_NAME} Catch2::Catch2WithMain)

    # Enable tests
    enable_testing()
    add_test(NAME ${PROJECT_NAME}Test COMMAND ${PROJECT_NAME}Test)
endif()
