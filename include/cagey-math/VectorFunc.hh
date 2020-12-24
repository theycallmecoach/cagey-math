//=============================================================================
//
// cagey-math - C++-17 Vector Math Library
// Copyright (c) 2016-2020 Kyle Girard <theycallmecoach@gmail.com>
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
//=============================================================================

#pragma once

/**
 * @file
 * @brief Utility function for vectors of various sizes
 */

#include "cagey-math/Vector3.hh"

namespace cagey::math
{

  /**
   * Computes the dot product of lhs and rhs.
   *
   * @tparam T The type of the components of lhs
   * @tparam N The number of component of vec
   *
   * @param lhs A Vector
   * @param rhs A Vector
   *
   * @return The dot product of lhs and rhs
   */
  template <typename T, std::size_t N>
  inline constexpr auto dot(Vector<T, N> const &lhs,
                            Vector<T, N> const &rhs) noexcept -> T
  {
    using std::begin;
    return detail::inner_product(begin(lhs), end(lhs), begin(rhs), T(0));
  }

  /**
   * Computes the cross product of lhs and rhs.
   *
   * @tparam T The type of the components of lhs
   * @tparam U The type of the components of rhs
   *
   * @param lhs A Vector
   * @param rhs A Vector
   *
   * @return The cross product of lhs and rhs.
   */
  template <typename T, typename U>
  inline constexpr auto cross(Vector<T, 3> const &lhs,
                              Vector<U, 3> const &rhs) noexcept
      -> Vector3<decltype(std::declval<T>() * std::declval<U>())>
  {
    return {
        lhs[1] * rhs[2] - lhs[2] * rhs[1],
        lhs[2] * rhs[0] - lhs[0] * rhs[2],
        lhs[0] * rhs[1] - lhs[1] * rhs[0],
    };
  }

  /**
   * Computes the length of vec.
   *
   * @tparam T The type of the components of vec
   * @tparam N The number of component of vec
   * @param vec A Vector
   *
   * @return The length of vec.
   */
  template <typename T, std::size_t N>
  inline auto length(Vector<T, N> const &vec) noexcept -> T
  {
    using std::sqrt;
    return sqrt(lengthSquared(vec));
  }

  /**
   * Computes the inverted length of vec.
   *
   * @tparam T The type of the components of vec
   * @tparam N The number of component of vec
   * @param vec A Vector
   *
   * @return The length of vec.
   */
  template <typename T, std::size_t N>
  inline auto lengthInverted(Vector<T, N> const &vec) noexcept -> T
  {
    return T{1} / length(vec);
  }

  /**
   * Computes the length of vec squared.
   *
   * @tparam T The type of the components of vec
   * @tparam N The number of component of vec
   * @param vec A Vector
   *
   * @return The squared length of vec.
   */
  template <typename T, std::size_t N>
  inline constexpr auto lengthSquared(Vector<T, N> const &vec) noexcept -> T
  {
    return dot(vec, vec);
  }

  /**
  * Computes length of vec and returns true if it is zero.
  *
  * @tparam T The type of the components of vec.
  * @tparam S The number of components in vec.
  *
  * @param vec The Vector to check for zero length
  * @return true if length of vec is zero
  */
  template <typename T, std::size_t S>
  inline auto isZeroLength(Vector<T, S> const &vec) -> bool
  {
    T epsilon = std::numeric_limits<T>::epsilon();
    using std::abs;
    return abs(lengthSquared(vec)) < (epsilon * epsilon);
  }

  /**
   * Computes a normalized copy of vec.  If the length of the vec is
   * 0 the behaviour is undefined.
   *
   * @tparam T The type of the components of vec
   * @tparam N The number of component of vec
   *
   * @param vec A Vector
   * @return a normalized copy of vec.
   */
  template <typename T, std::size_t N>
  inline auto normalize(Vector<T, N> vec) noexcept -> Vector<T, N>
  {
    return vec *= lengthInverted(vec);
  }

  /**
   * Computes if the lhs and rhs are nearlyEqual within a tolerance of epsilon.
   *
   * @tparam T The type of the components of vec
   * @tparam N The number of component of vec
   *
   * @param lhs A Vector.
   * @param rhs A Vector
   * @param epsilon the amount of tolerance
   */
  template <typename T, std::size_t N>
  auto fuzzyEquals(Vector<T, N> const &lhs, Vector<T, N> const &rhs,
                   T const epsilon = std::numeric_limits<T>::epsilon())
      -> bool
  {
    using std::begin;
    using std::end;
    return std::equal(begin(lhs), end(lhs), begin(rhs), [epsilon](T r, T l) {
      using std::abs;
      return static_cast<T>(abs(l - r)) <= epsilon;
    });
  }

} // namespace cagey::math