cmake_minimum_required(VERSION 3.16)

project(low_latency_trading_system LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(matching_tests
    tests/order_test.cpp
    tests/price_level_test.cpp
)

target_include_directories(matching_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_options(matching_tests PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion
    -Wshadow
)

target_link_libraries(matching_tests PRIVATE
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(matching_tests)