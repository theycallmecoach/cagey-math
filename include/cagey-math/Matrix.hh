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
#include <cagey-math/Vector.hh>

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
  template <typename T, std::size_t R, std::size_t C> class Matrix;


  template <typename T, std::size_t R, std::size_t C> class Matrix {
  public:

    // struct {
      std::enable_if_t < is_vec_type<T>::value &&
          (C >= 2 && C <= 4 && R >= 2 && R <= 4),
          std::array<Vector<T, R>, C>> columns;
    // } impl_;

    /// The Underlying type of this matrix
    using Type = T;

    enum : std::size_t {
      Rows = R, /// the number of rows in this matrix
      Cols = C, /// the number of columns in this matrix
    };
    
    /// the number of elements in this matrix
    static const std::size_t Size = Rows * Cols;

    inline static constexpr auto fill(T const v) noexcept -> Matrix<T, C, R>;
    inline static constexpr auto identity() noexcept -> Matrix<T, C, R>;
    inline static constexpr auto zero() noexcept -> Matrix<T, C, R>;

    /**
     * Default construct all  components
     */
    inline constexpr Matrix() noexcept = default;

    inline explicit constexpr Matrix(T v) noexcept;

  /**
     * Construct each component with the same value.
     *
     * @param  v The value to initialize each component
     */
    template <typename U, typename V = typename std::enable_if<
                              std::is_same<T, U>::value && R != 1 && C != 1, T>::type,
              typename Indices = std::make_index_sequence<Size>>
    inline explicit constexpr Matrix(U const v) noexcept
        : Matrix(Indices{}, v) {}


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

    
  inline constexpr auto operator[](std::size_t i) noexcept -> Vector<T,R> & { 
    return columns[i];
  }

  inline constexpr auto operator[](std::size_t i) const noexcept -> Vector<T,R> const & { 
    return columns[i];
  }

  private:
    /**
     * Construct all components using the value of 'v'
     *
     * @param v A value for all components
     */
    template <typename U, std::size_t... I>
    constexpr Matrix(std::index_sequence<I...>, U const v)
        : columns{detail::repeat(v, I)...} {}

  };

  /**
   * An '2x2' Matrix.
   */
  template <typename T>  class Matrix<T, 2, 2> {
  public:
    inline constexpr Matrix() noexcept = default;

    inline constexpr auto operator[](std::size_t i) noexcept -> Vector<T,2> & { 
      return columns[i];
    }

    inline constexpr auto operator[](std::size_t i) const noexcept -> Vector<T,2> const & { 
      return columns[i];
    }

    // struct {
    //   std::enable_if_t < is_vec_type<T>::value,
    //       std::array<Vector<T, 2>, 2>> columns;
    // } impl_;

    std::enable_if_t < is_vec_type<T>::value, std::array<Vector<T, 2>, 2>> columns;
  };

  /**
   * An '3x' Matrix.
   */
  template <typename T>  class Matrix<T, 3, 3> {
  public:

    inline constexpr auto operator[](std::size_t i) noexcept -> Vector<T,3> & { 
      return columns[i];
    }

    inline constexpr auto operator[](std::size_t i) const noexcept -> Vector<T,3> const & { 
      return columns[i];
    }

    //  struct {
    //   std::enable_if_t < is_vec_type<T>::value,std::array<Vector<T, 2>, 2>> columns;
    // } impl_;

    std::enable_if_t < is_vec_type<T>::value,std::array<Vector<T, 2>, 2>> columns;

 };


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
  template <typename T, std::size_t R, std::size_t C>
  inline auto operator==(Matrix<T, R, C> const &lhs,
                         Matrix<T, R, C> const &rhs) noexcept->bool {
    return detail::equal(std::begin(lhs), std::end(lhs), std::begin(rhs));
  }

  /**
   * Determines if two Matrices are not equal.
   *
   * @tparam T The component type of the lhs and rhs
   * @tparam R The number of rows of both lhs and rhs
   * @tparam C The number of columns of both lhs and rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return true if lhs and rhs are not equal
   */
  template <typename T, std::size_t R, std::size_t C>
  inline auto operator!=(Matrix<T, R, C> const &lhs,
                         Matrix<T, R, C> const &rhs) noexcept->bool {
    return !(lhs == rhs);
  }


} // namespace cagey::math
