cmake_minimum_required(VERSION 3.4)

# Options. Turn on with 'cmake -Dmyvarname=ON'.
#option(test "Build all tests." OFF) # Makes boolean 'test' available.

project(cagey-math)

SET(CMAKE_CXX_FLAGS "-std=c++1z")

include_directories(
    include
    lib/googletest/googletest/include)


set(MATH_SOURCES
    include/cagey-math/MathFwd.hh
    include/cagey-math/Vector.hh
    include/cagey-math/Matrix.hh
    include/cagey-math/Constants.hh
    include/cagey-math/Degree.hh
    include/cagey-math/Radian.hh
    include/cagey-math/detail/BaseAngle.hh
    include/cagey-math/detail/ConstExprUtil.hh
    include/cagey-math/detail/MetaUtil.hh
    include/cagey-math/detail/vec_type.hh)

set(MATH_TEST_SOURCES
    test/DegreeTests.cc
    test/VectorTests.cc
    test/Vector2Tests.cc
    test/Vector3Tests.cc)

##################################################
#Testing
##################################################

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()


add_executable(
    cageyMath.tests
    ${MATH_SOURCES}
    ${MATH_TEST_SOURCES})

target_link_libraries(cageyMath.tests gtest_main)


add_test(NAME cageyMath.tests COMMAND cageyMath.tests)
