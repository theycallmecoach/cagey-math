////////////////////////////////////////////////////////////////////////////////
//
// cagey-math - C++-17 Vector Math Library
// Copyright (c) 2016 Kyle Girard <theycallmecoach@gmail.com>
//
// The MIT License (MIT)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>

/**
 * Common Math constants like pi.
 */
namespace cagey::math::constants {

  /**
   * The mystical value of pi (3.14....) to the accuracy of T.
   *
   * @tparam T the desired type of Pi
   */
  template <typename T>
  constexpr
      typename std::enable_if<std::is_floating_point<T>::value, T>::type pi =
          static_cast<T>(3.141592653589793238462643383279502884);

  /**
   * Value to convert between degrees and radians.
   * Equivalent to pi / 180

   * @tparam T the desired type of converstion value
   */
  template <typename T>
  constexpr
      typename std::enable_if<std::is_arithmetic<T>::value, T>::type degToRad =
          pi<T> / static_cast<T>(180.0);

  /**
   * Value to convert between radians and degrees.
   * Equivalent to 180 / pi
   *
   * @tparam T the desired type of converstion value
   */
  template <typename T>
  constexpr
      typename std::enable_if<std::is_arithmetic<T>::value, T>::type radToDeg =
          static_cast<T>(180.0) / pi<T>;

} // namespace cagey::math::constants
