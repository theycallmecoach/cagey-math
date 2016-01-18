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

#include <cagey-math/MathFwd.hh>
#include <cagey-math/detail/BaseAngle.hh>
#include <cagey-math/Constants.hh>

namespace cagey::math {

  /**
   * Represents an Angle using Radians
   *
   * @tparam T Underlying type
   */
  template <typename T> class Radian : public BaseAngle<Radian, T> {
  public:
    /**
     * Default constructor.  Initializes values to 0
     */
    constexpr Radian() = default;

    /**
     * Value Constructor.  Initializes the angle to the given value
     *
     * @param val the value for this Radian
     */
    constexpr explicit Radian(T const val) : BaseAngle<math::Radian, T>{val} {}

    /**
     * Conversion Constructor.  Initializes this Radian using the value from the
     * given Radian
     *
     * @tparam U an arithmatic type
     * @param val the Radian to copy
     */
    template <typename U>
    constexpr explicit Radian(BaseAngle<math::Radian, U> val)
        : BaseAngle<math::Radian, T>{val} {}

    /**
     * Convert Degree to Radian
     *
     * @param val Degree to convert to a Radian
     */
    constexpr explicit Radian(BaseAngle<Degree, T> val)
        : BaseAngle<math::Degree, T>{T{val} * constants::degToRad<T>} {}
  };

  /**
   * Literal Operator. Converts a double to a Radian
   *
   * @param value a double.
   */
  constexpr Radian<double> operator"" _rad(long double value) {
    return Radian<double>(value);
  }

  /**
   * Literal Operator. Converts a float to a Radian
   *
   * @param value a double.
   */
  constexpr Radian<float> operator"" _radf(long double value) {
    return Radian<float>(value);
  }

} // namespace cagey::math
