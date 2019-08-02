////////////////////////////////////////////////////////////////////////////////
//
// cagey-math - C++-17 Vector Math Library
// Copyright (c) 2019 Kyle Girard <theycallmecoach@gmail.com>
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

#include <cmath>
#include <cagey-math/MathFwd.hh>
#include <cagey-math/detail/MetaUtil.hh>
#include <cagey-math/detail/vec_type.hh>
#include <cagey-math/detail/ConstExprUtil.hh>

namespace cagey::math {

  /**
   * An 'N' - Dimensional Vector.
   */
  template <typename T, std::size_t N> class Vector {
  public:
    /// The underlying data type
    using Type = T;
    /// The number of elements in this Point
    const static std::size_t Size = N;

    /**
     * Anonymous union to allow access to members using different names
     */
    union {
      std::enable_if_t<is_vec_type<T>::value, std::array<T, N>> data;
      T raw[N];
    };
  }; // Vector

  /**
   * Overload std::begin()
   */
  template <typename T, std::size_t N>
  inline constexpr auto begin(Vector<T, N> const & v) -> decltype(&v.raw[0]) {
    return &v.raw[0];
  }
  
  /**
   * Overload std::begin()
   */
  template <typename T, std::size_t N>
  inline constexpr auto begin(Vector<T, N> & v) -> decltype(&v.raw[0]) {
    return &v.raw[0];
  }
 
  /**
   * Overload std::end()
   */
  template <typename T, std::size_t N>
  inline constexpr auto end(Vector<T, N> const & v) -> decltype(&v.raw[0]) {
    return &v.raw[0] + Vector<T, N>::Size;
  }
  
  /**
   * Overload std::end()
   */
  template <typename T, std::size_t N>
  inline constexpr auto end(Vector<T, N> & v) -> decltype(&v.raw[0]) {
    return &v.raw[0] + Vector<T, N>::Size;
  }

  ////////////////////////////////////////////////////////////////////////////
  /// Binary Operators
  ////////////////////////////////////////////////////////////////////////////

  /**
   * Compute the component wise sum of rhs and lhs.
   *
   * @tparam T The component type of the rhs and lhs
   * @tparam N The number of components in rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the component wise sum of lhs and rhs
   */
  template <typename T, std::size_t N>
  inline constexpr auto operator+(Vector<T, N> lhs,
                                  Vector<T, N> const &rhs) noexcept {
    return lhs += rhs;
  }

  /**
   * Compute the component wise difference of rhs and lhs.
   *
   * @tparam T The component type of the rhs and lhs
   * @tparam N The number of components in rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the component wise difference of lhs and rhs
   */
  template <typename T, std::size_t N>
  inline constexpr auto operator-(Vector<T, N> lhs,
                                  Vector<T, N> const &rhs) noexcept {
    return lhs -= rhs;
  }

 /**
   * Compute the component wise product of rhs and lhs.
   *
   * @tparam T The component type of the rhs and lhs
   * @tparam N The number of components in rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the product of lhs and each component of rhs
   */
  template <typename T, std::size_t N>
  inline constexpr auto operator*(T const lhs,
                                  Vector<T, N> rhs) noexcept->Vector<T, N> {
    return rhs *= lhs;
  }

  /**
   * Compute the component wise product of rhs and lhs.
   *
   * @tparam T The component type of the rhs and lhs
   * @tparam N The number of components of the lhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the product of lhs and each component of rhs
   */
  template <typename T, std::size_t N>
  inline constexpr auto operator*(Vector<T, N> lhs,
                                  T const rhs) noexcept->Vector<T, N> {
    return lhs *= rhs;
  }

  /**
   * Compute the component wise quotients of rhs and lhs.
   *
   * @tparam T The component type of the rhs and lhs3
   * @tparam N The number of components in rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the quotients of lhs and each component of rhs
   */
  template <typename T, std::size_t N,
            typename Indices = std::make_index_sequence<N>>
  inline constexpr auto operator/(
      T const lhs, Vector<T, N> const &rhs) noexcept->Vector<T, N> {
    return detail::vector::operatorDivision(lhs, rhs, Indices());
  }

  /**
   * Compute the component wise quotients of rhs and lhs.
   *
   * @tparam T The component type of the rhs and lhs
   * @tparam N The number of components of the lhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the quotients of lhs and each component of rhs
   */
  template <typename T, std::size_t N>
  inline constexpr auto operator/(Vector<T, N> lhs,
                                  T const rhs) noexcept->Vector<T, N> {
    return lhs /= rhs;
  }

  /**
   * Determines if two Vectors are equal.
   *
   * @tparam T The component type of the lhs and rhs
   * @tparam N The number of components of both lhs and rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return true if lhs and rhs are equal
   */
  template <typename T, std::size_t N>
  inline auto operator==(Vector<T, N> const &lhs,
                         Vector<T, N> const &rhs) noexcept->bool {
    using std::begin;
    using std::end;
    return detail::equal(begin(lhs), end(lhs), begin(rhs));
  }

  /**
   * Determines the inequality of if two Vectors.
   *
   * @tparam T The component type of the lhs and rhs
   * @tparam N The number of components of both lhs and rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return true if lhs and rhs are not equal
   */
  template <typename T, std::size_t N>
  inline constexpr auto operator!=(Vector<T, N> const &lhs,
                                   Vector<T, N> const &rhs) noexcept->bool {
    return !(lhs == rhs);
  }


  ////////////////////////////////////////////////////////////////////////////
  /// Unary Operators
  ////////////////////////////////////////////////////////////////////////////


  /**
   * Negates each component of v
   *
   * @tparam T The component type of v
   * @tparam N The number of components of v
   *
   * @param v A Vector.
   * @return The negation of each component of v
   */
  template <typename T, std::size_t N,
            typename Indices = std::make_index_sequence<N>>
  inline constexpr auto operator-(
      Vector<T, N> const &v) noexcept->Vector<T, N> {
    return detail::vector::operatorUnaryMinus(v, Indices());
  }


  ////////////////////////////////////////////////////////////////////////////
  /// Basic Functions
  ////////////////////////////////////////////////////////////////////////////

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
                            Vector<T, N> const &rhs) noexcept->T {
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
      ->Vec3<decltype(std::declval<T>() * std::declval<U>())> {
    return {
        lhs[1] * rhs[2] - lhs[2] * rhs[1], lhs[2] * rhs[0] - lhs[0] * rhs[2],
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
  inline auto length(Vector<T, N> const &vec) noexcept->T {
    using std::sqrt;
    return sqrt(length_squared(vec));
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
  inline auto length_inverted(Vector<T, N> const &vec) noexcept->T {
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
  inline constexpr auto length_squared(Vector<T, N> const &vec) noexcept->T {
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
  inline auto is_zero_length(Vector<T, S> const &vec)->bool {
    T epsilon = std::numeric_limits<T>::epsilon();
    using std::abs;
    return abs(length_squared(vec)) < (epsilon * epsilon);
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
  inline auto normalize(Vector<T, N> vec) noexcept->Vector<T, N> {
    return vec *= length_inverted(vec);
  }

  /**
   * Computes if the lhs and rhs are nearlyEqual within a tolerance of epsilon.
   *
   * @tparam T The type of the components of vec
   * @tparam N The number of component of vec
   *
   * @param lhs A Vector.
   * @param rhs A
   */
  template <typename T, std::size_t N>
  auto nearly_equal(Vector<T, N> const &lhs, Vector<T, N> const &rhs,
                   T const epsilon = std::numeric_limits<T>::epsilon())
      ->bool {
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), [epsilon](T r, T l) {
      using std::abs;
      return static_cast<T>(abs(l - r)) <= epsilon;
    });
  }

} //namespace cagey::math