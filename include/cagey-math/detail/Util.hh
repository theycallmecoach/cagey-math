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

#include <limits>
#include <type_traits>
#include <cmath>

namespace cagey::math {

  /**
   * Performs fuzzy equals between the given values, use for floating point
   * types
   * @tparam T an arithmetic type, only floating point as been tested
   * @param x value to be tested
   * @param y value to be tested
   */
  template <typename T>
  typename std::enable_if<std::is_arithmetic<T>::value, bool>::type equals(
      T const x, T const y) {
    // values are actually equal
    if (x == y) {
      return true;
    }

    using std::abs;
    const auto xx = std::abs(x);
    const auto yy = std::abs(y);
    const auto diff = std::abs(x - y);
    const auto ep = std::numeric_limits<T>::epsilon();

    // one or both of the number are zero or close enough that
    // relative error is meaningless
    if (x == T{} || y == T{} || diff < ep) {
      return diff < ep;
    }

    // relative error
    return diff / (xx + yy) < ep;
  }

} // namespace cagey::math
