//=============================================================================
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
//=============================================================================

#pragma once

/**
 * @file
 * @brief 3 Element Vector class template
 */

#include "cagey-math/detail/Vector.hh"

namespace cagey::math
{
  /**
   * @brief A 3 element Vector.
   * 
   * @tparam T the type of elements of this vector
   */
  template <typename T>
  class Vector<T, 3>
  {
  public:
    /// The number of elements in this Point
    const static std::size_t Size = 3;
    using Type = Vector<T, Size>;                                       ///< The vector type
    using ElementType = T;                                              ///< The underlying value type
    using Reference = ElementType &;                                    ///< The vector element reference type
    using ConstReference = ElementType const &;                         ///< The vector element const reference type
    using Iterator = typename std::array<T, Size>::iterator;            ///< The vector element iterator type
    using ConstIterator = typename std::array<T, Size>::const_iterator; ///< The vector element const iterator type

    //===========================================================================
    // Static Member Functions
    //===========================================================================

    /**
     * @brief Return a two element zero vector.
     * 
     * @return two element zero vector.
     */
    static constexpr auto zero() noexcept -> Vector
    {
      return {T(0), T(0), T(0)};
    }

    /**
     * @brief Return three element x axis vector.
     * 
     * @return three element x axis vector.
     */
    static constexpr auto xAxis() noexcept -> Vector
    {
      return {T(1), T(0), T(0)};
    }

    /**
     * @brief Return three element y axis vector.
     * 
     * @return three element y axis vector.
     */
    static constexpr auto yAxis() noexcept -> Vector
    {
      return {T(0), T(1), T(0)};
    }

    /**
     * @brief Return three element z axis vector.
     * 
     * @return three element z axis vector.
     */
    static constexpr auto zAxis() noexcept -> Vector
    {
      return {T(0), T(0), T(1)};
    }

    //==========================================================================
    /// @name Implicit Constructors
    //==========================================================================
    ///@{

    /**
     * @brief Construct a vector, elements are initialized to zero.
     */
    constexpr Vector() noexcept = default;

    /**
     * @brief Construct a vector which is a copy of the given vector.
     */
    constexpr Vector(Vector const &v) noexcept = default;

    /**
     * @brief Default move constructor
     */
    constexpr Vector(Vector &&) noexcept = default;

    ///@}
    //==========================================================================
    /// @name Explicit Constructors
    //==========================================================================
    ///@{

    /**
     * @brief Construct a vector with all elements set to the given value.
     * 
     * @param v the initial value for all elements
     */
    explicit constexpr Vector(T const v) noexcept : elements{v, v, v} {}

    /**
     * @brief Construct a vector using the given scalars.
     * 
     * @param x the x element
     * @param y the y element
     */
    constexpr Vector(T const x, T const y, T const z) noexcept
        : elements{x, y, z} {};

    inline constexpr Vector(Vector2<T> const &v, T const z) noexcept
        : elements{v[0], v[1], z} {};

    ///@}
    //==========================================================================
    /// Explicit Conversion Constructors
    //==========================================================================
    ///@{

    /**
     * @brief Conversion copy constructor
     * 
     * @tparam U the element type of the passed vector
     * @param v source vector
     */
    template <typename U>
    explicit constexpr Vector(Vector<U, Size> const &v) noexcept
        : elements{static_cast<T>(v.elements[0]),
                   static_cast<T>(v.elements[1]),
                   static_cast<T>(v.elements[2])} {}

    /**
     * @brief Conversion copy constructor, only takes the first 3 elements
     *
     * @tparam VN a number >= Size
     */
    template <std::size_t VN, typename = std::enable_if_t<(VN > 2)>>
    explicit constexpr Vector(Vector<T, VN> const &v) noexcept
        : elements{v.elements[0], v.elements[1], v.elements[2]} {}

    ///@}
    //==========================================================================
    /// Component Access
    //==========================================================================
    ///@{

    /**
     * @brief Index operator.  Only 0 and 1 are valid indexes.
     * 
     * @param i index into elements
     */
    constexpr auto operator[](std::size_t i) noexcept -> T &
    {
      assert(i >= 0 && i < Size);
      return elements[i];
    }

    /**
     * @brief Index operator.  Only 0 and 1 are valid indexes.
     * 
     * @param i index into elements
     */
    constexpr auto operator[](std::size_t i) const noexcept -> T const &
    {
      assert(i >= 0 && i < Size);
      return elements[i];
    }

    ///@}
    //==========================================================================
    /// Operators
    //==========================================================================
    ///@{

    /**
     * @brief CopyAssignment operator
     * 
     * @param v src vectror
     */
    constexpr auto operator=(Vector<T, Size> const &v) noexcept -> Vector &
    {
      elements = v.elements;
      return *this;
    }

    /**
     * @brief Add and assign a vector componentwise
     * 
     * Values of the given vector are converted using static_cast
     * 
     * @tparam U type of the source vector
     * @param v a vector
     */
    template <typename U>
    constexpr auto operator+=(Vector<U, Size> const &v) noexcept -> Vector &
    {
      elements[0] += static_cast<T>(v.elements[0]);
      elements[1] += static_cast<T>(v.elements[1]);
      elements[2] += static_cast<T>(v.elements[2]);
      return *this;
    }

    /**
     * @brief Add the given scalar to each component of this vector
     * 
     * @tparam U type of the given scalar
     * @param scalar the amount to add to each element of this vector
     */
    template <typename U>
    constexpr auto operator+=(U const &scalar) noexcept -> Vector &
    {
      for (auto &&r : elements)
      {
        r += static_cast<T>(scalar);
      }
      return *this;
    }

    /**
     * @brief Subtract and assign a vector componentwise
     * 
     * @param v the vector
     */
    template <typename U>
    constexpr auto operator-=(Vector<U, Size> const &v) noexcept -> Vector &
    {
      elements[0] -= static_cast<T>(v.elements[0]);
      elements[1] -= static_cast<T>(v.elements[1]);
      elements[2] -= static_cast<T>(v.elements[2]);
      return *this;
    }

    /**
     * @brief Subtract the given scalar from each component
     * 
     * @param scalar the amount to subtract
     */
    template <typename U>
    constexpr auto operator-=(U const &scalar) noexcept -> Vector &
    {
      for (auto &&r : elements)
      {
        r -= static_cast<T>(scalar);
      }
      return *this;
    }

    /**
     * @brief Multiply this vector by the given scalar
     * 
     * @param scalar the amount to scale
     */
    template <typename U>
    constexpr auto operator*=(U const v) noexcept -> Vector &
    {
      for (auto &&r : elements)
      {
        r *= static_cast<T>(v);
      }
      return *this;
    }

    /**
     * @brief Multiply with the given vector componentwise
     *
     * @param v the vector to scale
     */
    template <typename U>
    constexpr auto operator*=(Vector<U, Size> const &v) noexcept -> Vector &
    {
      elements[0] *= static_cast<T>(v.elements[0]);
      elements[1] *= static_cast<T>(v.elements[1]);
      elements[2] *= static_cast<T>(v.elements[2]);
      return *this;
    }

    /**
     * @brief Divide each element with the given scalar
     * 
     * @param scalar the amount to use in the division
     */
    template <typename U>
    constexpr auto operator/=(U const v) noexcept -> Vector &
    {
      for (auto &&r : elements)
      {
        r /= static_cast<T>(v);
      }
      return *this;
    }

    /**
     * @brief Divide each element with the given vector componentwise
     * 
     * @param v the vector to divide with
     */
    template <typename U>
    constexpr auto operator/=(Vector<U, Size> const &v) noexcept -> Vector &
    {
      elements[0] /= static_cast<T>(v.elements[0]);
      elements[1] /= static_cast<T>(v.elements[1]);
      elements[2] /= static_cast<T>(v.elements[2]);
      return *this;
    }

    /**
     * @brief Increase each element of this vector
     */
    constexpr auto operator++() noexcept -> Vector &
    {
      ++elements[0];
      ++elements[1];
      ++elements[2];
      return *this;
    }

    /**
     * @brief Decrease each element of this vector
     */
    constexpr auto operator--() noexcept -> Vector &
    {
      --elements[0];
      --elements[1];
      --elements[2];
      return *this;
    }

    /**
     * @brief Increase each element of a copy of this vector
     */
    constexpr auto operator++(int) noexcept -> Vector &
    {
      Vector res = Vector(*this)++ * this;
      return *res;
    }

    /**
     * @brief Decrease each element of a copy of this vector
     */
    constexpr auto operator--(int) noexcept -> Vector &
    {
      Vector res = Vector(*this)-- * this;
      return *res;
    }

    ///@}
    //==========================================================================
    /// Member Functions
    //==========================================================================
    ///@{

    inline constexpr Vector2<T> xy() const noexcept
    {
      return Vector2<T>{x, y};
    }

    inline constexpr Vector3<T> xyz() const noexcept
    {
      return Vector3<T>{x, y, z};
    }

    inline constexpr Vector2<T> rg() const noexcept
    {
      return xy();
    }

    inline constexpr Vector3<T> rgb() const noexcept
    {
      return xyz();
    }

    //==========================================================================
    /// @name Iterators
    //==========================================================================

    /**
     * @brief returns iterator to the beginning
     */
    constexpr auto begin() noexcept -> typename Vector::Iterator
    {
      return elements.begin();
    }

    /**
     * @brief returns iterator to the beginning
     */
    constexpr auto begin() const noexcept -> typename Vector::ConstIterator
    {
      return elements.begin();
    }

    /**
     * @brief returns iterator to the end
     */
    constexpr auto end() noexcept -> typename Vector::Iterator
    {
      return elements.end();
    }

    /**
     * @brief returns iterator to the end
     */
    constexpr auto end() const noexcept -> typename Vector::ConstIterator
    {
      return elements.end();
    }

    ///@}
    //==========================================================================
    // elements Members
    //==========================================================================

    /**
     * Anonymous union to allow access to members using different names
     */
    union
    {
      std::enable_if_t<is_vec_type<T>::value, std::array<T, Size>> elements;
      T rawElements[Size];
      struct
      {
        T x;
        T y;
        T z;
      };
      struct
      {
        T r;
        T g;
        T b;
      };
    };
  };

} //namespace cagey::math