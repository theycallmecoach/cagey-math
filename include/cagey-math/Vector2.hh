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
 * @brief 2 element Vector class template
 */

#include "cagey-math/detail/Vector.hh"
#include "cagey-math/VectorFunc.hh"

namespace cagey::math
{
  /**
   * @brief A 2 element Vector.
   * 
   * @tparam T the type of elements of this vector
   */
  template <typename T>
  class Vector<T, 2>
  {
  public:
    const static std::size_t Size = 2;                                  ///< The number of elements in this Point
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
    static constexpr auto zero() noexcept -> Vector { return {T(0), T(0)}; }

    /**
     * @brief Return two element x axis vector.
     * 
     * @return two element x axis vector.
     */
    static constexpr auto xAxis() noexcept -> Vector { return {T(1), T(0)}; }

    /**
     * @brief Return two element y axis vector.
     */
    static constexpr auto yAxis() noexcept -> Vector { return {T(0), T(1)}; }

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
    explicit constexpr Vector(T const v) noexcept : elements{v, v} {}

    // template <typename U>
    // explicit constexpr Vector(Vector<U, Size> const &v) :
    // {
    // }

    /**
     * @brief Construct a vector using the given scalars.
     * 
     * @param x the x element
     * @param y the y element
     */
    constexpr Vector(T const x, T const y) noexcept : elements{x, y} {}

    ///@}

    //==========================================================================
    /// @name Explicit Conversion Constructors
    //==========================================================================
    ///@{

    /**
     * @brief Create a vector using another vector for initial values with type conversion
     * 
     * @tparam U The type of the passed vector elements
     * @param v the source vector
     */
    template <typename U>
    explicit constexpr Vector(Vector<U, Size> const &v) noexcept
        : elements{static_cast<T>(v.elements[0]),
                   static_cast<T>(v.elements[1])} {}
    ///@}

    //==========================================================================
    /// @name Component Access
    //==========================================================================
    ///@{

    /**
     * @brief Index operator.  Only 0 and 1 are valid indexes.
     * 
     * @param i index into elements
     */
    constexpr auto operator[](std::size_t i) noexcept -> Reference
    {
      assert(i >= 0 && i < Size);
      return elements[i];
    }

    /**
     * @brief Index operator.  Only 0 and 1 are valid indexes.
     * 
     * @param i index into elements
     */
    constexpr auto operator[](std::size_t i) const noexcept -> ConstReference
    {
      assert(i >= 0 && i < Size);
      return elements[i];
    }

    ///@}
    //==========================================================================
    /// @name Unary Operators
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
      return *this;
    }

    /**
     * @brief Add the given scalar to each component of this vector
     * 
     * @param scalar the amount to add to each element of this vector
     */
    template <typename U>
    constexpr auto operator+=(U const &scalar) noexcept -> Vector &
    {
      elements[0] += static_cast<T>(scalar);
      elements[1] += static_cast<T>(scalar);
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
      elements[0] -= static_cast<T>(scalar);
      elements[1] -= static_cast<T>(scalar);
      return *this;
    }

    /**
     * @brief Multiply this vector by the given scalar
     * 
     * @param scalar the amount to scale
     */
    template <typename U>
    constexpr auto operator*=(U const &scalar) noexcept -> Vector &
    {
      elements[0] *= static_cast<T>(scalar);
      elements[1] *= static_cast<T>(scalar);
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
      return *this;
    }

    /**
     * @brief Divide each element with the given scalar
     * 
     * @param scalar the amount to use in the division
     */
    template <typename U>
    constexpr auto operator/=(U const &scalar) noexcept -> Vector &
    {
      elements[0] /= static_cast<T>(scalar);
      elements[1] /= static_cast<T>(scalar);
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
      return *this;
    }

    /**
     * @brief Increase each element of this vector
     */
    constexpr auto operator++() noexcept -> Vector &
    {
      ++elements[0];
      ++elements[1];
      return *this;
    }

    /**
     * @brief Decrease each element of this vector
     */
    constexpr auto operator--() noexcept -> Vector &
    {
      --elements[0];
      --elements[1];
      return *this;
    }

    /**
     * @brief Increase each element of a copy of this vector
     */
    constexpr auto operator++(int) noexcept -> Vector &
    {
      Vector res = Vector{*this};
      res = res++ * this;
      return *res;
    }

    /**
     * @brief Decrease each element of a copy of this vector
     */
    constexpr auto operator--(int) noexcept -> Vector &
    {
      Vector res = Vector{*this};
      res = res-- * this;
      return *res;
    }

    ///@}

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

    //==========================================================================
    // Member functions
    //==========================================================================

    //==========================================================================
    // elements Members
    //==========================================================================

    union
    {
      std::enable_if_t<is_vec_type<T>::value, std::array<T, Size>> elements; ///< elements as std::array
      T rawElements[Size];                                                   ///< elements as native array

      struct
      {
        T x; ///< x element
        T y; ///< y element
      };
      ///@}
      struct
      {

        T r; ///< r element
        T g; ///< g element
      };
      struct
      {

        T w; ///< w element
        T h; ///< h element
      };
    };
  };
} //namespace cagey::math