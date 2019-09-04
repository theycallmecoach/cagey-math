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
#include <cagey-math/detail/Matrix.hh>

namespace cagey::math {

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
  template<typename T> class Matrix<T, 2, 2> {
  public:
    enum : std::size_t {
        Rows = 2, /// the number of rows in this matrix
        Cols = 2, /// the number of columns in this matrix
    };

    using ColumnType = Vector<Cols,T>;
    using RowType = Vector<Rows,T>;
    using Type = T;


    /// the number of elements in this matrix
    static const std::size_t Size = Rows * Cols;

    ////////////////////////////////////////////////////////////////////////////
    /// Static Member Functions
    ////////////////////////////////////////////////////////////////////////////


    static constexpr auto fill(T const v) noexcept -> Matrix<Type, Cols, Rows> {
      return Matrix{v};
    }
    static constexpr auto identity() noexcept -> Matrix<Type, Cols, Rows> {
      return Matrix{{1, 0}, {0, 1}};
    }
    static constexpr auto zero() noexcept -> Matrix<Type, Cols, Rows> {
      return Matrix{0};
    }

    ////////////////////////////////////////////////////////////////////////////
    /// Implicit Constructors
    ////////////////////////////////////////////////////////////////////////////

    constexpr Matrix() noexcept = default;
    
    constexpr Matrix(Matrix const & m) noexcept = default;

    explicit constexpr Matrix(T v) noexcept {

    }

  private:
    union {
      std::array<ColumnType, Cols>> columns;
      Type data[Size];
    }
     
  }; // Vector
   
} //namespace cagey::math