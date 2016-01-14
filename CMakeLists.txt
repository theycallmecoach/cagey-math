cmake_minimum_required(VERSION 3.4)

# Options. Turn on with 'cmake -Dmyvarname=ON'.
#option(test "Build all tests." OFF) # Makes boolean 'test' available.

project(cagey-math)

SET(CMAKE_CXX_FLAGS "-std=c++1z")

include_directories(
    include
    lib/googletest/googletest/include)


set(MATH_SOURCES
    include/cagey-math/Vector.hh
    include/cagey-math/detail/Vector2.hh
    include/cagey-math/detail/vec_type.hh)

set(MATH_TEST_SOURCES
    test/VectorTests.cc
    test/Vector2Tests.cc)

##################################################
#Testing
##################################################

add_subdirectory(lib/googletest/googletest)


add_executable(
    cageyMath.tests
    ${MATH_SOURCES}
    ${MATH_TEST_SOURCES})

target_link_libraries(cageyMath.tests gtest gtest_main)


add_test(
  cageyMath.tests
  cageyMath.tests)
