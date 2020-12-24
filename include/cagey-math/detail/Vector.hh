//=============================================================================
//
// cagey-math - C++-17 Vector Math Library
// Copyright (c) 2020 Kyle Girard <theycallmecoach@gmail.com>
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
 * @brief N-Dimensional Vector class template
 */

#include <cmath>

#include "cagey-math/Math.hh"
#include "cagey-math/detail/MetaUtil.hh"
#include "cagey-math/detail/vec_type.hh"
#include "cagey-math/detail/ConstExprUtil.hh"

namespace cagey::math
{

  /**
   * @brief An 'N' - Dimensional Vector.
   * 
   * All other vectors are specializations of this template.
   * 
   * @tparam T the type of elements of this vector
   * @tparam N the number of elements of this vector
   */
  template <typename T, std::size_t N>
  class Vector
  {
  public:
    /// The number of elements in this Point
    const static std::size_t Size = N;
    using Type = Vector<T, Size>;                                       ///< The vector type
    using ElementType = T;                                              ///< The underlying value type
    using Reference = ElementType &;                                    ///< The vector element reference type
    using ConstReference = ElementType const &;                         ///< The vector element const reference type
    using Iterator = typename std::array<T, Size>::iterator;            ///< The vector element iterator type
    using ConstIterator = typename std::array<T, Size>::const_iterator; ///< The vector element const iterator type

    //==========================================================================
    /// @name Iterators
    //==========================================================================

    constexpr auto begin() noexcept -> typename Vector::Iterator
    {
      return elements.begin();
    }

    constexpr auto begin() const noexcept -> typename Vector::ConstIterator
    {
      return elements.begin();
    }

    constexpr auto end() noexcept -> typename Vector::Iterator
    {
      return elements.end();
    }

    constexpr auto end() const noexcept -> typename Vector::ConstIterator
    {
      return elements.end();
    }

    /**
     * Anonymous union to allow access to members using different names
     */
    union
    {
      std::enable_if_t<is_vec_type<T>::value, std::array<T, N>> elements; /// elements as an std::array
      T rawElements[N];                                                   /// elements as native array
    };
  }; // Vector

  /**
   * Overload std::begin()
   */
  template <typename T, std::size_t N>
  inline constexpr auto begin(Vector<T, N> const &v) -> typename Vector<T, N>::ConstIterator
  {
    return v.begin();
  }

  /**
   * Overload std::begin()
   */
  template <typename T, std::size_t N>
  inline constexpr auto begin(Vector<T, N> &v) -> typename Vector<T, N>::Iterator
  {
    return v.begin();
  }

  /**
   * Overload std::end()
   */
  template <typename T, std::size_t N>
  inline constexpr auto end(Vector<T, N> const &v) -> decltype(&v.rawElements[0])
  {
    return v.end();
  }

  /**
   * Overload std::end()
   */
  template <typename T, std::size_t N>
  inline constexpr auto end(Vector<T, N> &v) -> decltype(&v.rawElements[0])
  {
    return v.end();
  }

  //==========================================================================
  /// @name Binary Operators
  //==========================================================================
  ///@{
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
                                  Vector<T, N> const &rhs) noexcept
  {
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
                                  Vector<T, N> const &rhs) noexcept
  {
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
                                  Vector<T, N> rhs) noexcept -> Vector<T, N>
  {
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
                                  T const rhs) noexcept -> Vector<T, N>
  {
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
      T const lhs, Vector<T, N> const &rhs) noexcept -> Vector<T, N>
  {
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
                                  T const rhs) noexcept -> Vector<T, N>
  {
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
                         Vector<T, N> const &rhs) noexcept -> bool
  {
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
                                   Vector<T, N> const &rhs) noexcept -> bool
  {
    return !(lhs == rhs);
  }

  ///@}
  //==========================================================================
  /// @name Unary Operators
  //==========================================================================
  ///@{

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
      Vector<T, N> const &v) noexcept -> Vector<T, N>
  {
    return detail::vector::operatorUnaryMinus(v, Indices());
  }

  ///@}
} //namespace cagey::math