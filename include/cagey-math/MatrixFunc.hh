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
 * @brief Utility functions for matrices of various sizes
 */

#include "cagey-math/Matrix22.hh"

namespace cagey::math
{
  namespace detail
  {
    template <typename T, std::size_t C, std::size_t R>
    struct determinantImpl
    {
    };

    template <typename T>
    struct determinantImpl<T, 2, 2>
    {
      static constexpr auto exec(Matrix<T, 2, 2> const &mat) -> T
      {
        return mat[0][0] * mat[1][1] - mat[1][0] * mat[0][1];
      }
    };

    template <typename T, std::size_t C, std::size_t R>
    struct transposeImpl
    {
    };

    template <typename T>
    struct transposeImpl<T, 2, 2>
    {
      static constexpr auto exec(Matrix<T, 2, 2> const &mat) -> Matrix<T, 2, 2>
      {
        Matrix<T, 2, 2> result;
        result[0][0] = mat[0][0];
        result[0][1] = mat[1][0];
        result[1][0] = mat[0][1];
        result[1][1] = mat[1][1];
        return result;
      }
    };

  } // namespace detail

  /**
   * @brief Calculate the determinant of the given square matrix
   * 
   * @return the determinant of the given matrix
   */
  template <typename T, std::size_t C, std::size_t R>
  auto determinant(Matrix<T, C, R> const &mat) -> T
  {
    return detail::determinantImpl<T, C, R>::exec(mat);
  }

  /**
   * @brief Transpose the given matrix
   * 
   * @param mat the matrix to transpose
   * @return the transpose of the given matrix
   */
  template <typename T, std::size_t C, std::size_t R>
  auto transpose(Matrix<T, C, R> const &mat) -> Matrix<T, C, R>
  {
    return detail::transposeImpl<T, C, R>::exec(mat);
  }

} // namespace cagey::math