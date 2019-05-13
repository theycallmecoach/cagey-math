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

/**
 * @file
 * Forward declarations for the cagey::math namespace
 */

#include <cstdint>
#include <cstddef>

/**
 * Namespace to contain all cagey
 */
namespace cagey::math {

  template <typename> class Degree;
  template <typename> class Radian;

  /// Shorthand for float Degree template
  template <typename T> using Degf = Degree<float>;
  /// Shorthand for double Degree template
  template <typename T> using Degd = Degree<double>;
  /// Shorthand for float Radian template
  template <typename T> using Radf = Radian<float>;
  /// Shorthand for double Radian template
  template <typename T> using Radd = Radian<double>;

  template <typename, std::size_t> class Vector;
  /// Shorthand for the two element Vector
  template <typename T> using Vec2 = Vector<T, 2>;
  /// Shorthand for the three element Vector
  template <typename T> using Vec3 = Vector<T, 3>;
  /// Shorthand for the four element Vector
  template <typename T> using Vec4 = Vector<T, 4>;

  /// Shorthand for the two element unsigned Vector
  using Vec2u = Vector<std::uint32_t, 2>;
  /// Shorthand for the two element int Vector
  using Vec2i = Vector<std::int32_t, 2>;
  /// Shorthand for the two element float Vector
  using Vec2f = Vector<float, 2>;
  /// Shorthand for the two element double Vector
  using Vec2d = Vector<double, 2>;

  /// Shorthand for the three element unsigned Vector
  using Vec3u = Vector<std::uint32_t, 3>;
  /// Shorthand for the three element int Vector
  using Vec3i = Vector<std::int32_t, 3>;
  /// Shorthand for the three element float Vector
  using Vec3f = Vector<float, 3>;
  /// Shorthand for the three element double Vector
  using Vec3d = Vector<double, 3>;

  /// Shorthand for the four element unsigned Vector
  using Vec4u = Vector<std::uint32_t, 4>;
  /// Shorthand for the four element int Vector
  using Vec4i = Vector<std::int32_t, 4>;
  /// Shorthand for the four element float Vector
  using Vec4f = Vector<float, 4>;
  /// Shorthand for the four element double Vector
  using Vec4d = Vector<double, 4>;

  template <typename, std::size_t, std::size_t> class Matrix;
  /// Shorthand for 2x2 square matrix
  template <typename T> using Mat22 = Matrix<T, 2, 2>;
  /// Shorthand for 2x3 Matrix.
  template <typename T> using Mat23 = Matrix<T, 2, 3>;
  /// Shorthand for 2x4 Matrix.
  template <typename T> using Mat24 = Matrix<T, 2, 4>;
  /// Shorthand for 3x2 Matrix.
  template <typename T> using Mat32 = Matrix<T, 3, 2>;
  /// Shorthand for 3x3 square matrix
  template <typename T> using Mat33 = Matrix<T, 3, 3>;
  /// Shorthand for 3x4 matrix
  template <typename T> using Mat34 = Matrix<T, 3, 4>;
  /// Shorthand for 4x2 Matrix.
  template <typename T> using Mat42 = Matrix<T, 4, 2>;
  /// Shorthand for 4x3 Matrix.
  template <typename T> using Mat43 = Matrix<T, 4, 3>;
  /// Shorthand for 4x4 square matrix
  template <typename T> using Mat44 = Matrix<T, 4, 4>;

  /**
   * A 2x4 Matrix.
   *
   * @tparam T component type
   */
  template <typename T> using Matrix24 = Matrix<T, 2, 4>;

  /// Shorthand for 2x2 square int matrix
  using Mat22u = Matrix<std::uint32_t, 2, 2>;
  /// Shorthand for 2x2 square int matrix
  using Mat33u = Matrix<std::uint32_t, 3, 3>;
  /// Shorthand for 2x2 square int matrix
  using Mat44u = Matrix<std::uint32_t, 4, 4>;

  /// Shorthand for 2x2 square int matrix
  using Mat22i = Matrix<std::int32_t, 2, 2>;
  /// Shorthand for 2x2 square int matrix
  using Mat33i = Matrix<std::int32_t, 3, 3>;
  /// Shorthand for 2x2 square int matrix
  using Mat44i = Matrix<std::int32_t, 4, 4>;

  /// Shorthand for 2x3 double matrix
  using Mat23i = Mat23<std::int32_t>;
  /// Shorthand A 3x2 Matrix with double components.
  using Mat32i = Mat32<std::int32_t>;
  /// Shorthand A 3x4 Matrix with double components.
  using Mat34i = Mat34<std::int32_t>;
  /// Shorthand A 4x2 Matrix with double components.
  using Mat42i = Mat42<std::int32_t>;
  /// Shorthand A 4x3 Matrix with double components.
  using Mat43i = Mat43<std::int32_t>;

  /// Shorthand for 2x2 square float matrix
  using Mat22f = Matrix<float, 2, 2>;
  /// Shorthand for 3x3 square float matrix
  using Mat33f = Matrix<float, 3, 3>;
  /// Shorthand for 4x4 square float matrix
  using Mat44f = Matrix<float, 4, 4>;

  /// Shorthand for 2x3 double matrix
  using Mat23f = Mat23<float>;
  /// Shorthand A 3x2 Matrix with double components.
  using Mat32f = Mat32<float>;
  /// Shorthand A 3x4 Matrix with double components.
  using Mat34f = Mat34<float>;
  /// Shorthand A 4x2 Matrix with double components.
  using Mat42f = Mat42<float>;
  /// Shorthand A 4x3 Matrix with double components.
  using Mat43f = Mat43<float>;

  /// Shorthand for 2x2 square double matrix
  using Mat22d = Matrix<double, 2, 2>;
  /// Shorthand for 3x3 square double matrix
  using Mat33d = Matrix<double, 3, 3>;
  /// Shorthand for 4x4 square double matrix
  using Mat44d = Matrix<double, 4, 4>;

  /// Shorthand for 2x3 double matrix
  using Mat23d = Mat23<double>;
  /// Shorthand A 3x2 Matrix with double components.
  using Mat32d = Mat32<double>;
  /// Shorthand A 3x4 Matrix with double components.
  using Mat34d = Mat34<double>;
  /// Shorthand A 4x2 Matrix with double components.
  using Mat42d = Mat42<double>;
  /// Shorthand A 4x3 Matrix with double components.
  using Mat43d = Mat43<double>;

} // namespace cagey::math
