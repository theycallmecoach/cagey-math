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
 * @brief 2x2 element Matrix class template
 */

#include <cmath>
#include "cagey-math/detail/Matrix.hh"
#include "cagey-math/Vector2.hh"

namespace cagey::math
{

  /**
   * @class Matrix
   * Base Matrix class with R rows and C columns.  Matrix uses column vectors.
   *
   * The idea here is to use template specializations to implement Matrices of
   * different size.  To DRY up the code as much as possble the smallest set of
   * methods possible will be implemented... all other are free functions.  So
   * the idea goes... it might get annoying I don't know yet.
   *
   * @tparam T underlying data type of this Matrix
   * @tparam C the number of columns in this Matrix
   * @tparam R the number of rows in this Matrix
   */
  template <typename T>
  class Matrix<T, 2, 2>
  {
  public:
    enum : std::size_t
    {
      Rows = 2, ///< the number of rows in this matrix
      Cols = 2, ///< the number of columns in this matrix
    };

    static const std::size_t Size = Rows * Cols;                                       ///< the number of elements in this matrix
    using Type = Matrix<T, Cols, Rows>;                                                ///< The matrix type
    using ColumnType = Vector<T, Cols>;                                                ///< The type of columns
    using RowType = Vector<T, Rows>;                                                   ///< The type of rows
    using ElementType = T;                                                             ///< The underlying value type
    using Reference = ElementType &;                                                   ///< The matrix element reference type
    using ConstReference = ElementType const &;                                        ///< The matrix element const reference type
    using ColumnIterator = typename std::array<ColumnType, Cols>::iterator;            ///< The column iterator type
    using ConstColumnIterator = typename std::array<ColumnType, Cols>::const_iterator; ///< The const column iterator type

    //===========================================================================
    // Static Member Functions
    //===========================================================================

    /**
     * @brief Create matrix with all elements equal to the given value
     * 
     * @param v the value to assign to all elements
     */
    static constexpr auto fill(T const v) noexcept -> Matrix<ElementType, Cols, Rows>
    {
      return Matrix{v};
    }

    /**
     * @brief Create an indentity matrix
     * 
     */
    static constexpr auto identity() noexcept -> Matrix<ElementType, Cols, Rows>
    {
      return Matrix{{1, 0}, {0, 1}};
    }

    /**
     * @brief Create a matrix with all elements set to zero
     */
    static constexpr auto zero() noexcept -> Matrix<ElementType, Cols, Rows>
    {
      return Matrix{0};
    }

    //==========================================================================
    /// @name Implicit Constructors
    //==========================================================================
    ///@{

    /**
     * @brief Default constructor
     */
    constexpr Matrix() noexcept = default;

    /**
     * @brief Default copy consructor
     */
    constexpr Matrix(Matrix const &m) noexcept = default;

    ///@}
    //==========================================================================
    /// @name Explicit Constructors
    //==========================================================================
    ///@{

    /**
     * @brief Construct matrix will all values equal to given value
     * 
     * @param v value for all elements
     */
    explicit constexpr Matrix(T v) noexcept : Matrix(ColumnType{v, v}, ColumnType{v, v}) {}

    /**
     * @brief Construct matrix from column vectors
     * 
     * @param col0 first column
     * @param col1 second column
     */
    inline constexpr Matrix(ColumnType const &col0,
                            ColumnType const &col1) noexcept
        : columns{{col0, col1}}
    {
    }

    /**
     * @brief Construct matrix from an array of Size values
     * 
     * The values are assumed to be in the following order x0, y0, z0, x1, y1, z1, x2, y2, z2
     * 
     * @param elements for the given matrix.
     */
    inline constexpr explicit Matrix(std::array<T, Size> const &elements) noexcept
    {
      columns[0][0] = elements[0];
      columns[0][1] = elements[1];
      columns[1][0] = elements[2];
      columns[1][1] = elements[3];
    }

    /**
     * @brief Construct matrix from an array of Size values
     * 
     * The values are assumed to be in the following order x0, y0, z0, x1, y1, z1, x2, y2, z2
     * 
     * @param elements for the given matrix.
     */
    inline constexpr explicit Matrix(T const x1, T const y1, T const x2, T const y2) noexcept
    {
      columns[0][0] = x1;
      columns[0][1] = y1;
      columns[1][0] = x2;
      columns[1][1] = y2;
    }

    ///@}
    //==========================================================================
    /// @name Component Access
    //==========================================================================
    ///@{

    /**
     * @brief Column Access
     * 
     * @param index 
     */
    inline constexpr auto operator[](std::size_t i) noexcept -> ColumnType &
    {
      assert(i >= 0 && i < Cols);
      return columns[i];
    }

    /**
     * @brief Column Access
     * 
     * @param index 
     */
    inline constexpr auto operator[](std::size_t i) const noexcept -> ColumnType const &
    {
      assert(i >= 0 && i < Cols);
      return columns[i];
    }

    ///@}

    //==========================================================================
    /// @name Unary Operators
    //==========================================================================
    ///@{
    inline constexpr auto operator=(Matrix<T, Cols, Rows> const &value) noexcept -> Matrix &
    {
      columns[0] = value.columns[0];
      columns[1] = value.columns[1];
      return *this;
    }

    /** 
     * @brief Add the given value to each element in this matrix
     * 
     * @tparam U type of the src matrix 
     * @param value value to add to each element
     */
    template <typename U>
    inline constexpr auto operator+=(U const &value) noexcept -> Matrix &
    {
      columns[0] += value;
      columns[1] += value;
      return *this;
    }

    /**
     * @brief Add the given matrix componentwise to this vector
     *
     * @tparam U type of the src matrix 
     * @param value src matrix;
     */
    template <typename U>
    inline constexpr auto operator+=(Matrix<U, Cols, Rows> const &value) noexcept -> Matrix &
    {
      columns[0] += value[0];
      columns[1] += value[1];
      return *this;
    }

    /** 
     * @brief Subtract the given value from each element in this matrix
     * 
     * @tparam U type of the src matrix 
     * @param value value to add to each element
     */
    template <typename U>
    inline constexpr auto operator-=(U const &value) noexcept -> Matrix &
    {
      columns[0] -= value;
      columns[1] -= value;
      return *this;
    }

    /**
     * @brief subtract the given matrix componentwise from this vector
     *
     * @tparam U type of the src matrix 
     * @param value src matrix;
     */
    template <typename U>
    inline constexpr auto operator-=(Matrix<U, Cols, Rows> const &value) noexcept -> Matrix &
    {
      columns[0] -= value[0];
      columns[1] -= value[1];
      return *this;
    }

    /** 
     * @brief Scale all elements by the given value
     * 
     * @tparam U type of the scalar 
     * @param value value to scale each element
     */
    template <typename U>
    inline constexpr auto operator*=(U const &value) noexcept -> Matrix &
    {
      columns[0] *= value;
      columns[1] *= value;
      return *this;
    }

    /** 
     * @brief Scale all elements by the given value
     * 
     * @tparam U type of the scalar 
     * @param value value to scale each element
     */
    template <typename U>
    inline constexpr auto operator/=(U const &value) noexcept -> Matrix &
    {
      columns[0] /= value;
      columns[1] /= value;
      return *this;
    }

    ///@}

    //==========================================================================
    /// @name Member functions
    //==========================================================================
    ///@{

    /**
     * @brief returns iterator to the beginning
     */
    inline constexpr auto columnBegin() -> ColumnIterator
    {
      return columns.begin();
    }

    /**
     * @brief returns iterator to the first column
     */
    inline constexpr auto columnBegin() const -> ConstColumnIterator
    {
      return columns.begin();
    }

    /**
     * @brief returns iterator to the end
     */
    inline constexpr auto columnEnd() -> ColumnIterator
    {
      return columns.end();
    }

    /**
     * @brief returns iterator to the beginning
     */
    inline constexpr auto columnEnd() const -> ConstColumnIterator
    {
      return columns.end();
    }

    //@}

  private:
    union
    {
      std::array<ColumnType, Cols> columns;
      ElementType data[Size];
    };

  }; // Matrix22

  /**
   * Compute the component wise product of rhs and lhs.
   *
   * @tparam T The component type of the rhs and lhs
   * @tparam U The type of scalar
   * @tparam C The number of components of the lhs
   * @tparam R The number of components of the lhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the product of lhs and each component of rhs
   */
  template <typename T>
  inline constexpr auto operator*(Matrix<T, 2, 2> const &lhs,
                                  typename Matrix<T, 2, 2>::RowType const &rhs) noexcept -> typename Matrix<T, 2, 2>::ColumnType
  {
    return {lhs[0][0] * rhs.x + lhs[1][0] * rhs.y,
            lhs[0][1] * rhs.x + lhs[1][1] * rhs.y};
  }

  /**
   * Compute the component wise product of rhs and lhs.
   *
   * @tparam T The component type of the rhs and lhs
   * @tparam U The type of scalar
   * @tparam C The number of components of the lhs
   * @tparam R The number of components of the lhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the product of lhs and each component of rhs
   */
  template <typename T>
  inline constexpr auto operator*(typename Matrix<T, 2, 2>::ColumnType const &lhs,
                                  Matrix<T, 2, 2> const &rhs) noexcept -> typename Matrix<T, 2, 2>::RowType
  {
    return {lhs.x * rhs[0][0] + lhs.y * rhs[0][1],
            lhs.x * rhs[1][0] + lhs.y * rhs[1][1]};
  }

  /**
   * Compute the component wise product of rhs and lhs.
   *
   * @tparam T The component type of the rhs and lhs
   * @tparam U The type of scalar
   * @tparam C The number of components of the lhs
   * @tparam R The number of components of the lhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the product of lhs and each component of rhs
   */
  template <typename T>
  inline constexpr auto operator*(Matrix<T, 2, 2> const &lhs,
                                  Matrix<T, 2, 2> const &rhs) noexcept -> Matrix<T, 2, 2>
  {
    return Matrix<T, 2, 2>{lhs[0][0] * rhs[0][0] + lhs[1][0] * rhs[0][1],
                           lhs[0][1] * rhs[0][0] + lhs[1][1] * rhs[0][1],
                           lhs[0][0] * rhs[1][0] + lhs[1][0] * rhs[1][1],
                           lhs[0][1] * rhs[1][0] + lhs[1][1] * rhs[1][1]};
  }

} //namespace cagey::math