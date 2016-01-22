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

#include "cagey-math/Constants.hh"
#include "cagey-math/detail/Util.hh"

namespace cagey::math {

  /**
   * Base class for representing Angles. ie Degrees and Radians.  The value
   * contained within in this class is just that, a value.  How it is
   * interpretted is defined by the derived classes.
   *
   * @tparam D The derived type
   * @tparam T The type of the angle representation
   */
  template <template <typename> class D, typename T> class BaseAngle {

    /**
     * Ensure the derived class is a friend.
     */
    template <template <typename> class, typename> friend class BaseAngle;

  public:
    /** @cond doxygen has some issues with static assert */
    static_assert(std::is_arithmetic<T>::value,
                  "Underlying type must be a number");
    /** @endcond */

    /// Underlying type
    using Type = T;

  protected:
    /**
     * Default Construct angle component.
     */
    constexpr BaseAngle() = default;

    /**
     * Explicit conversion constructor from raw value
     *
     * @param value A value
     */
    constexpr explicit BaseAngle(T const value) : value{value} {}

    /**
     * Copy construct a BaseAngle from one with possibly different
     * underlying type.
     *
     * @tparam U A new type
     * @param other A BaseAngle to convert to this.
     */
    template <typename U>
    constexpr explicit BaseAngle(BaseAngle<D, U> const &other)
        : value(T(other.value)) {}

  public:
    /**
     * Explicit conversion operator to raw value
     *
     * @return a unitless value
     */
    constexpr explicit operator T() const { return value; }

    /**
     * Assign the value of 'other' to this value.
     *
     * @param other an other instance of BaseAngle
     */
    constexpr auto operator+=(BaseAngle<D, T> const &other)
        -> BaseAngle<D, T> & {
      value += other.value;
      return *this;
    }

    /**
     * Subtract the value of 'other' from this value.
     *
     * @param other an other instance of BaseAngle
     */
    constexpr auto operator-=(BaseAngle<D, T> const &other)
        -> BaseAngle<D, T> & {
      value -= other.value;
      return *this;
    }

    /**
     * Multiply the value of this and 'val'.
     *
     * @param val the scaling factor
     */
    constexpr auto operator*=(T const val) -> BaseAngle<D, T> & {
      value *= val;
      return *this;
    }

    /**
     * Divide the value of this by 'val'.
     *
     * @param val the scaling factor
     */
    constexpr auto operator/=(T const val) -> BaseAngle<D, T> & {
      value /= val;
      return *this;
    }

    /**
     * Add the value of 'lhs' and 'rhs'.
     *
     * @param lhs the left hand side of the addition
     * @param rhs the right hand side of the addition
     */
    friend constexpr auto operator+(BaseAngle<D, T> lhs,
                                    BaseAngle<D, T> const &rhs)
        -> BaseAngle<D, T> {
      return lhs += rhs;
    }

    /**
     * Subtract the value of 'rhs' from 'lhs'.
     *
     * @param lhs the left hand side of the subtraction
     * @param rhs the right hand side of the subtraction
     */
    friend constexpr auto operator-(BaseAngle<D, T> lhs,
                                    BaseAngle<D, T> const &rhs)
        -> BaseAngle<D, T> {
      return lhs -= rhs;
    }

    /**
     * Check the values of 'lhs' and 'rhs' for exact equality.  Not really
     * useful with floating point based angles
     *
     * @param lhs the left hand side of the equality operation
     * @param rhs the right hand side of the equality operation
     */
    friend constexpr auto operator==(BaseAngle<D, T> const &lhs,
                                     BaseAngle<D, T> const &rhs) -> bool {
      return lhs.value == rhs.value;
    }

    /**
     * Check the value of 'lhs' and 'rhs' for inequality.  Not really
     * useful with floating point based angles
     *
     * @param lhs the left hand side of the inequality operation
     * @param rhs the right hand side of the inequality operation
     */
    friend constexpr auto operator!=(BaseAngle<D, T> const &lhs,
                                     BaseAngle<D, T> const &rhs) -> bool {
      return !(lhs == rhs);
    }

    /**
     * Check if the 'lhs' value is less than the 'rhs' value.
     *
     * @param lhs the left hand side BaseAngle
     * @param rhs the right hand side BaseAngle
     */
    friend constexpr auto operator<(BaseAngle<D, T> const &lhs,
                                    BaseAngle<D, T> const &rhs) -> bool {
      return lhs.value < rhs.value;
    }

    /**
     * Check if the 'lhs' value is greater than the 'rhs' value.
     *
     * @param lhs the left hand side BaseAngle
     * @param rhs the right hand side BaseAngle
     */
    friend constexpr auto operator>(BaseAngle<D, T> const &lhs,
                                    BaseAngle<D, T> const &rhs) -> bool {
      return rhs < lhs;
    }

    /**
     * Check if the 'lhs' value is less than or equal to the 'rhs' value.
     *
     * @param lhs the left hand side BaseAngle
     * @param rhs the right hand side BaseAngle
     */
    friend constexpr auto operator<=(BaseAngle<D, T> const &lhs,
                                     BaseAngle<D, T> const &rhs) -> bool {
      return !(lhs > rhs);
    }

    /**
     * Check if the 'lhs' value is greater than or equal to the 'rhs' value.
     *
     * @param lhs A BaseAngle
     * @param rhs A BaseAngle
     *
     * @return true if the lhs value is greater than or equal to rhs value
     */
    friend constexpr auto operator>=(BaseAngle<D, T> const &lhs,
                                     BaseAngle<D, T> const &rhs) -> bool {
      return !(lhs < rhs);
    }

    /**
     * Returns a negative copy of 'val'
     *
     * @param val The val
     *
     * @return a negative angle equal in magnatude to this
     */
    friend constexpr auto operator-(BaseAngle<D, T> const &val)
        -> BaseAngle<D, T> {
      return BaseAngle<D, T>{-val.value};
    }

    /**
     * Multiplies the 'lhs' value by 'val'.
     *
     * @param lhs the left hand side of the multiplication
     * @param val the amount to scale by
     */
    friend constexpr auto operator*(BaseAngle<D, T> lhs, T val)
        -> BaseAngle<D, T> {
      return lhs *= val;
    }

    /**
     * Multiplies the 'rhs' value by 'val'.
     *
     * @param rhs the rhs hand side of the multiplication
     * @param val the amount to scale by
     */
    friend constexpr auto operator*(T val, BaseAngle<D, T> rhs)
        -> BaseAngle<D, T> {
      return rhs *= val;
    }

    /**
     * Divide the value of 'lhs' by a 'val'.
     *
     * @param lhs the lhs hand side of the division
     * @param val the amount to scale by
     */
    friend constexpr auto operator/(BaseAngle<D, T> lhs, T const val)
        -> BaseAngle<D, T> {
      return lhs /= val;
    }

    /**
     * Compute the ratio between the two angles.
     *
     * @param rhs the rhs hand side of the division
     * @param lhs the lhs hand side of the division
     */
    friend constexpr auto operator/(BaseAngle<D, T> lhs,
                                    BaseAngle<D, T> const &rhs) -> T {
      return lhs.value / rhs.value;
    }

    /**
     * Fuzzy Equals between 'lhs' and 'rhs'.
     *
     * @param rhs a BaseAngle
     * @param lhs a BaseAngle
     */
    friend constexpr auto equals(BaseAngle<D, T> const &rhs,
                                 BaseAngle<D, T> const &lhs) {
      return equals(rhs.value, lhs.value);
    }

  private:
    Type value;
  };

} // namespace cagey::math
