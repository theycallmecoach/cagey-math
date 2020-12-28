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

#include <cmath>
#include "cagey-math/detail/Vector.hh"

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
  template <typename T, std::size_t C, std::size_t R>
  class Matrix
  {

  public:
    enum : std::size_t
    {
      Rows = R, ///< the number of rows in this matrix
      Cols = C, ///< the number of columns in this matrix
    };

    static const std::size_t Size = Rows * Cols;                                       ///< the number of elements in this matrix
    using Type = Matrix<T, Cols, Rows>;                                                ///< The matrix type
    using ColumnType = Vector<T, C>;                                                   ///< The type of columns
    using RowType = Vector<T, R>;                                                      ///< The type of rows
    using ElementType = T;                                                             ///< The underlying value type
    using Reference = ElementType &;                                                   ///< The vector element reference type
    using ConstReference = ElementType const &;                                        ///< The vector element const reference type
    using ColumnIterator = typename std::array<ColumnType, Cols>::iterator;            ///< The column iterator type
    using ConstColumnIterator = typename std::array<ColumnType, Cols>::const_iterator; ///< The const column iterator type

  private:
    union
    {
      std::array<ColumnType, Cols> columns; ///< storage
      ElementType raw[Size];
    };

  public:
    //===========================================================================
    // Static Member Functions
    //===========================================================================

    /**
     * @brief Create matrix with all elements equal to the given value
     * 
     * @param v the value to assign to all elements
     */
    inline static constexpr auto
    fill(T const v) noexcept -> Type
    {
      return Matrix{v};
    }

    /**
     * @brief Create an indentity matrix
     * 
     */
    inline static constexpr auto identity() noexcept -> Type
    {
      Matrix ret;
      for (int r; r < R; ++r)
      {
        for (int c; c < C; ++c)
        {
          ret.columns[r][c] = (r == c) ? ElementType{1} : ElementType{0};
        }
      }
      return ret;
    }

    /**
     * @brief Create a matrix with all elements set to zero
     */
    inline static constexpr auto zero() noexcept -> Type
    {
      return Matrix{0};
    }

    //==========================================================================
    /// @name Implicit Constructors
    //==========================================================================
    ///@{

    /**
     * @brief Construct a matrix all elements default initialized.
     */
    inline constexpr Matrix() noexcept = default;

    //@}

    //==========================================================================
    /// @name Explicit Constructors
    //==========================================================================
    ///@{

    inline explicit constexpr Matrix(T v) noexcept
    {
      // std::fill_n(std::begin(columns), Size, v);
      for (auto &&c : columns)
      {
        c = ColumnType::fill(v);
      }
    }
    //@}

    //==========================================================================
    /// @name Member functions
    //==========================================================================
    ///@{

    /**
     * @brief returns iterator to the beginning
     */
    inline constexpr auto columnsBegin() -> ColumnIterator
    {
      return columns.begin();
    }

    /**
     * @brief returns iterator to the first column
     */
    inline constexpr auto columnsBegin() const -> ConstColumnIterator
    {
      return columns.begin();
    }

    /**
     * @brief returns iterator to the end
     */
    inline constexpr auto columnsEnd() -> ColumnIterator
    {
      return columns.end();
    }

    /**
     * @brief returns iterator to the beginning
     */
    inline constexpr auto columnsEnd() const -> ConstColumnIterator
    {
      return columns.end();
    }

    //@}
  };

  /**
   * Compute the component wise addition of rhs and lhs.
   *
   * @tparam T The component type of the rhs and lhs
   * @tparam U The type of scalar
   * @tparam C The number of Columns
   * @tparam R The number of Rows
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the addition of lhs and each component of rhs
   */
  template <typename U, typename T, std::size_t C, std::size_t R>
  inline constexpr auto operator+(U const lhs,
                                  Matrix<T, C, R> rhs) noexcept -> Matrix<T, C, R>
  {
    return rhs += lhs;
  }

  /**
   * Compute the component wise addition of rhs and lhs.
   *
   * @tparam T The component type of the rhs and lhs
   * @tparam U The type of scalar
   * @tparam C The number of components of the lhs
   * @tparam R The number of components of the lhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the addition of lhs and each component of rhs
   */
  template <typename U, typename T, std::size_t C, std::size_t R>
  inline constexpr auto operator+(Matrix<T, C, R> lhs,
                                  U const rhs) noexcept -> Matrix<T, C, R>
  {
    return lhs += rhs;
  }

  /**
   * Compute the component wise subtraction of rhs and lhs.
   *
   * @tparam T The component type of the rhs and lhs
   * @tparam U The type of scalar
   * @tparam C The number of Columns
   * @tparam R The number of Rows
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the subraction of lhs and each component of rhs
   */
  template <typename U, typename T, std::size_t C, std::size_t R>
  inline constexpr auto operator-(U const lhs,
                                  Matrix<T, C, R> rhs) noexcept -> Matrix<T, C, R>
  {
    return rhs -= lhs;
  }

  /**
   * Compute the component wise subtraction of rhs and lhs.
   *
   * @tparam T The component type of the rhs and lhs
   * @tparam U The type of scalar
   * @tparam C The number of components of the lhs
   * @tparam R The number of components of the lhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the subtraction of lhs and each component of rhs
   */
  template <typename U, typename T, std::size_t C, std::size_t R>
  inline constexpr auto operator-(Matrix<T, C, R> lhs,
                                  U const rhs) noexcept -> Matrix<T, C, R>
  {
    return lhs -= rhs;
  }

  /**
   * Compute the component wise product of rhs and lhs.
   *
   * @tparam T The component type of the rhs and lhs
   * @tparam U The type of scalar
   * @tparam C The number of Columns
   * @tparam R The number of Rows
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the product of lhs and each component of rhs
   */
  template <typename U, typename T, std::size_t C, std::size_t R>
  inline constexpr auto operator*(U const lhs,
                                  Matrix<T, C, R> rhs) noexcept -> Matrix<T, C, R>
  {
    return rhs *= lhs;
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
  template <typename U, typename T, std::size_t C, std::size_t R>
  inline constexpr auto operator*(Matrix<T, C, R> lhs,
                                  U const rhs) noexcept -> Matrix<T, C, R>
  {
    return lhs *= rhs;
  }

  /**
   * Compute the component wise division of rhs and lhs.
   *
   * @tparam T The component type of the rhs and lhs
   * @tparam U The type of scalar
   * @tparam C The number of components of the lhs
   * @tparam R The number of components of the lhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the division of lhs and each component of rhs
   */
  template <typename U, typename T, std::size_t C, std::size_t R>
  inline constexpr auto operator/(Matrix<T, C, R> lhs,
                                  U const rhs) noexcept -> Matrix<T, C, R>
  {
    return lhs /= rhs;
  }

  /**
     * Determines if two Matrices are equal.
     *
     * @tparam T The component type of the lhs and rhs
     * @tparam R The number of rows of both lhs and rhs
     * @tparam C The number of columns of both lhs and rhs
     *
     * @param lhs the left-hand operand
     * @param rhs the right-hand operand
     * @return true if lhs and rhs are equal
     */
  template <typename T, std::size_t C, std::size_t R>
  inline auto operator==(Matrix<T, C, R> const &lhs,
                         Matrix<T, C, R> const &rhs) noexcept -> bool
  {
    return detail::equal(lhs.columnBegin(), lhs.columnEnd(), rhs.columnBegin());
  }

  /**
     * @brief Determines if two Matrices are not equal.
     *
     * @tparam T The component type of the lhs and rhs
     * @tparam R The number of rows of both lhs and rhs
     * @tparam C The number of columns of both lhs and rhs
     *
     * @param lhs the left-hand operand
     * @param rhs the right-hand operand
     * @return true if lhs and rhs are not equal
     */
  template <typename T, std::size_t C, std::size_t R>
  inline auto operator!=(Matrix<T, C, R> const &lhs,
                         Matrix<T, C, R> const &rhs) noexcept -> bool
  {
    return !(lhs == rhs);
  }

} //namespace cagey::math