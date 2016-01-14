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

#include <type_traits>
#include <Vector.hh>

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
   * @tparam R the number of rows in this Matrix
   * @tparam C the number of columns in this Matrix
   */
  template <typename T, std::size_t R, std::size_t C> struct Matrix;

  /**
   * A 2x2 Matrix.
   *
   * @tparam T component type
   */
  template <typename T> using Matrix22 = Matrix<T, 2, 2>;

  /**
   * A 2x3 Matrix.
   *
   * @tparam T component type
   */
  template <typename T> using Matrix23 = Matrix<T, 2, 3>;

  /**
   * A 2x4 Matrix.
   *
   * @tparam T component type
   */
  template <typename T> using Matrix24 = Matrix<T, 2, 4>;

  /**
   * A 3x2 Matrix.
   *
   * @tparam T component type
   */
  template <typename T> using Matrix32 = Matrix<T, 3, 2>;

  /**
   * A 3x3 Matrix.
   *
   * @tparam T component type
   */
  template <typename T> using Matrix33 = Matrix<T, 3, 3>;

  /**
   * A 3x4 Matrix.
   *
   * @tparam T component type
   */
  template <typename T> using Matrix34 = Matrix<T, 3, 4>;

  /**
   * A 4x2 Matrix.
   *
   * @tparam T component type
   */
  template <typename T> using Matrix34 = Matrix<T, 4, 2>;

  /**
   * A 4x3 Matrix.
   *
   * @tparam T component type
   */
  template <typename T> using Matrix34 = Matrix<T, 4, 3>;

  /**
   * A 4x4 Matrix.
   *
   * @tparam T component type
   */
  template <typename T> using Matrix34 = Matrix<T, 4, 4>;

  /**
   * A 2x2 Matrix with float components.
   */
  using Matrix22f = Matrix22<float>;

  /**
   * A 2x3 Matrix with float components.
   */
  using Matrix23f = Matrix23<float>;

  /**
   * A 2x4 Matrix with float components.
   */
  using Matrix24f = Matrix24<float>;

  /**
   * A 3x2 Matrix with float components.
   */
  using Matrix32f = Matrix32<float>;

  /*
   * A 3x3 Matrix with float components.
   */
  using Matrix33f = Matrix33<float>;

  /*
   * A 3x4 Matrix with float components.
   */
  using Matrix34f = Matrix34<float>;

  /*
   * A 4x2 Matrix with float components.
   */
  using Matrix42f = Matrix42<float>;

  /*
   * A 4x3 Matrix with float components.
   */
  using Matrix43f = Matrix43<float>;

  /*
   * A 4x4 Matrix with float components.
   */
  using Matrix44f = Matrix44<float>;

  /*
   * A 2x2 Matrix with double components.
   */
  using Matrix22d = Matrix22<double>;

  /*
   * A 2x3 Matrix with double components.
   */
  using Matrix23d = Matrix23<double>;

  /*
   * A 2x4 Matrix with double components.
   */
  using Matrix24d = Matrix24<double>;

  /*
   * A 3x2 Matrix with double components.
   */
  using Matrix32d = Matrix32<double>;

  /*
   * A 3x3 Matrix with double components.
   */
  using Matrix33d = Matrix33<double>;

  /*
   * A 3x4 Matrix with double components.
   */
  using Matrix34d = Matrix34<double>;

  /*
   * A 4x2 Matrix with double components.
   */
  using Matrix42d = Matrix42<double>;

  /*
   * A 4x3 Matrix with double components.
   */
  using Matrix43d = Matrix43<double>;

  /*
   * A 4x4 Matrix with double components.
   */
  using Matrix44d = Matrix44<double>;

  template <typename T, std::size_t C, std::size_t R> struct Matrix {
    struct {
      std::enable_if_t < is_vec_type<T>::value &&
          (C >= 2 && C <= 4 && R >= 2 && R <= 4),
          std::array<Vector<T, R>, C> columns;
    } impl_;

    /// The Underlying type of this matrix
    using Type = T;
    /// the number of rows in this matrix
    static const int Rows = R;
    /// the number of columns in this matrix
    static const int Cols = C;
    /// the number of elements in this matrix
    static const int Size = Rows * Cols;

    inline static constexpr auto fill(T const v) noexcept -> Matrix<T, C, R>;
    inline static constexpr auto identity() noexcept -> Matrix<T, C, R>;
    inline static constexpr auto zero() noexcept -> Matrix<T, C, R>;

    /**
     * Default construct all  components
     */
    Matrix() noexcept = default;

    inline explicit constexpr Matrix(T v) noexcept;
    inline explicit constexpr Matrix(Vector<T, R> const &col) noexcept;
    inline explicit constexpr Matrix(Vector<T, R> const &col0,
                                     Vector<T, R> const &col1) noexcept;
    inline explicit constexpr Matrix(Vector<T, R> const &col0,
                                     Vector<T, R> const &col1,
                                     Vector<T, R> const &col2) noexcept;
    inline explicit constexpr Matrix(Vector<T, R> const &col0,
                                     Vector<T, R> const &col1,
                                     Vector<T, R> const &col2,
                                     Vector<T, R> const &col3) noexcept;
  };
} // namespace cagey::math
