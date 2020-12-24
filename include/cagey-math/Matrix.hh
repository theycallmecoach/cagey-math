// //=============================================================================
// //
// // cagey-math - C++-17 Vector Math Library
// // Copyright (c) 2016-2020 Kyle Girard <theycallmecoach@gmail.com>
// //
// // The MIT License (MIT)
// //
// // Permission is hereby granted, free of charge, to any person obtaining a copy
// // of this software and associated documentation files (the "Software"), to deal
// // in the Software without restriction, including without limitation the rights
// // to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// // copies of the Software, and to permit persons to whom the Software is
// // furnished to do so, subject to the following conditions:
// //
// // The above copyright notice and this permission notice shall be included in
// // all copies or substantial portions of the Software.
// //
// // THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// // IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// // FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// // AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// // LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// // OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// // SOFTWARE.
// //
// //=============================================================================

// #pragma once

// /**
//  * @file
//  * @brief NxN element Matrix class template
//  */

// #include <type_traits>
// #include "cagey-math/detail/Vector.hh"

// namespace cagey::math
// {

//   /**
//    * @class Matrix
//    * Base Matrix class with R rows and C columns.  Matrix uses column vectors.
//    *
//    * The idea here is to use template specializations to implement Matrices of
//    * different size.  To DRY up the code as much as possble the smallest set of
//    * methods possible will be implemented... all other are free functions.  So
//    * the idea goes... it might get annoying I don't know yet.
//    *
//    * @tparam T underlying data type of this Matrix
//    * @tparam R the number of rows in this Matrix
//    * @tparam C the number of columns in this Matrix
//    */
//   template <typename T, std::size_t R, std::size_t C>
//   class Matrix;

//   //   template <typename T, std::size_t R, std::size_t C>
//   //   class Matrix
//   //   {
//   //   public:
//   //     /// The Underlying type of this matrix
//   //     using Type = T;

//   //     enum : std::size_t
//   //     {
//   //       Rows = R, /// the number of rows in this matrix
//   //       Cols = C, /// the number of columns in this matrix
//   //     };

//   //     /// the number of elements in this matrix
//   //     static const std::size_t Size = Rows * Cols;

//   //     // struct {
//   //     std::enable_if_t<is_vec_type<T>::value &&
//   //                          (C >= 2 && C <= 4 && R >= 2 && R <= 4),
//   //                      std::array<Vector<T, R>, C>>
//   //         columns;
//   //     // } impl_;

//   //     inline static constexpr auto fill(T const v) noexcept -> Matrix<T, C, R>;
//   //     inline static constexpr auto identity() noexcept -> Matrix<T, C, R>;
//   //     inline static constexpr auto zero() noexcept -> Matrix<T, C, R>;

//   //     /**
//   //      * Default construct all  components
//   //      */
//   //     inline constexpr Matrix() noexcept = default;

//   //     inline explicit constexpr Matrix(T v) noexcept;

//   //     inline constexpr Matrix(Matrix const &) noexcept = default;

//   //     /**
//   //      * Construct each component with the same value.
//   //      *
//   //      * @param  v The value to initialize each component
//   //      */
//   //     template <typename U, typename V = typename std::enable_if<std::is_same<T, U>::value && R != 1 && C != 1, T>::type,
//   //               typename Indices = std::make_index_sequence<Size>>
//   //     inline explicit constexpr Matrix(U const v) noexcept
//   //         : Matrix(Indices{}, v) {}

//   //     inline explicit constexpr Matrix(Vector<T, R> const &col) noexcept;
//   //     inline explicit constexpr Matrix(Vector<T, R> const &col0,
//   //                                      Vector<T, R> const &col1) noexcept;
//   //     inline explicit constexpr Matrix(Vector<T, R> const &col0,
//   //                                      Vector<T, R> const &col1,
//   //                                      Vector<T, R> const &col2) noexcept;
//   //     inline explicit constexpr Matrix(Vector<T, R> const &col0,
//   //                                      Vector<T, R> const &col1,
//   //                                      Vector<T, R> const &col2,
//   //                                      Vector<T, R> const &col3) noexcept;

//   //     inline constexpr auto operator[](std::size_t i) noexcept -> Vector<T, R> &
//   //     {
//   //       return columns[i];
//   //     }

//   //     inline constexpr auto operator[](std::size_t i) const noexcept -> Vector<T, R> const &
//   //     {
//   //       return columns[i];
//   //     }

//   //   private:
//   //     /**
//   //      * Construct all components using the value of 'v'
//   //      *
//   //      * @param v A value for all components
//   //      */
//   //     template <typename U, std::size_t... I>
//   //     constexpr Matrix(std::index_sequence<I...>, U const v)
//   //         : columns{detail::repeat(v, I)...} {}
//   //   };

//   //   /**
//   //    * An '2x2' Matrix.
//   //    */
//   //   template <typename T>
//   //   class Matrix<T, 2, 2>
//   //   {
//   //   public:
//   //     /// The Underlying type of this matrix
//   //     using Type = T;

//   //     enum : std::size_t
//   //     {
//   //       Rows = 2, /// the number of rows in this matrix
//   //       Cols = 2, /// the number of columns in this matrix
//   //     };

//   //     /// the number of elements in this matrix
//   //     static const std::size_t Size = Rows * Cols;

//   //     union
//   //     {
//   //       std::enable_if_t<is_vec_type<T>::value, std::array<Vector<T, 2>, 2>> columns;
//   //       T data[Size];
//   //     };

//   //     /**
//   //      * Return a Matrix will all values set to the given value
//   //      *
//   //      * @param v the value for all elements
//   //      *
//   //      * @return a matrix will all elements set to the give value
//   //      */
//   //     inline static constexpr auto fill(T const v) noexcept -> Matrix
//   //     {
//   //       return Matrix{v};
//   //     }

//   //     /**
//   //      * Return an Identity matrix
//   //      *
//   //      * @return a matrix with 1's on the diagonal
//   //      */
//   //     inline static constexpr auto identity() noexcept -> Matrix
//   //     {
//   //       return Matrix{{1, 0}, {0, 1}};
//   //     }

//   //     /**
//   //       * Return a Matrix will all values set to the given value
//   //       *
//   //       * @param v the value for all elements
//   //       *
//   //       * @return a matrix will all elements set to the give value
//   //       */
//   //     inline static constexpr auto zero() noexcept -> Matrix
//   //     {
//   //       return Matrix{0};
//   //     }

//   //     /**
//   //      * Default Construct with no value initialization
//   //      */
//   //     inline constexpr Matrix() noexcept = default;

//   //     /**
//   //      * Copy Constructor
//   //      */
//   //     constexpr Matrix(Matrix const &) noexcept = default;

//   //     /**
//   //      * Construct each component with the same value.
//   //      *
//   //      * @param  v The value to initialize each component
//   //      */
//   //     template <typename U, typename Indices = std::make_index_sequence<Size>>
//   //     inline explicit constexpr Matrix(U const v) noexcept
//   //         : Matrix(Indices{}, v) {}

//   //     /**
//   //      * Construct each column from the given column vectors.
//   //      *
//   //      * @param  col0 The first column
//   //      * @param  col1 The second column
//   //      */
//   //     inline constexpr Matrix(Vector<T, 2> const &col0,
//   //                             Vector<T, 2> const &col1) noexcept
//   //         : columns{{col0, col1}}
//   //     {
//   //     }

//   //     template <typename Indices = std::make_index_sequence<Size>>
//   //     inline constexpr explicit Matrix(std::array<T, Size> &elements) noexcept
//   //         : Matrix(elements, Indices{})
//   //     {
//   //     }

//   //     /**
//   //      * Return the column vector at the given index
//   //      *
//   //      * @param i column index
//   //      *
//   //      * @return the column vector at the given index
//   //      */
//   //     inline constexpr auto operator[](std::size_t i) noexcept -> Vector<T, 2> &
//   //     {
//   //       return columns[i];
//   //     }

//   //     /**
//   //      * Return the column vector at the given index
//   //      *
//   //      * @param i column index
//   //      *
//   //      * @return the column vector at the given index
//   //      */
//   //     inline constexpr auto operator[](std::size_t i) const noexcept -> Vector<T, 2> const &
//   //     {
//   //       return columns[i];
//   //     }

//   //     /**
//   //      * Scale this matrix by the given value
//   //      *
//   //      * @param i column index
//   //      *
//   //      * @return the column vector at the given index
//   //      */
//   //     inline constexpr auto operator*=(Type const &value) noexcept -> Matrix &
//   //     {
//   //       for (auto &&c : columns)
//   //       {
//   //         c *= value;
//   //       }
//   //       return *this;
//   //     }

//   //   private:
//   //     /**
//   //      * Construct all components using the value of 'v'
//   //      *
//   //      * @param v A value for all components
//   //      */
//   //     template <typename U, std::size_t... I>
//   //     constexpr Matrix(std::index_sequence<I...>, U const v)
//   //         : data{detail::repeat(static_cast<T>(v), I)...} {}

//   //     template <std::size_t... I>
//   //     constexpr Matrix(std::array<T, Size> &elements, std::index_sequence<I...>)
//   //         : data{elements[I]...}
//   //     {
//   //     }
//   //   };

//   //   /**
//   //    * An '3x3' Matrix.
//   //    */
//   //   template <typename T>
//   //   class Matrix<T, 3, 3>
//   //   {
//   //   public:
//   //     /// The Underlying type of this matrix
//   //     using Type = T;

//   //     enum : std::size_t
//   //     {
//   //       Rows = 3, /// the number of rows in this matrix
//   //       Cols = 3, /// the number of columns in this matrix
//   //     };

//   //     /// the number of elements in this matrix
//   //     static const std::size_t Size = Rows * Cols;

//   //     /**
//   //      * Return a Matrix will all values set to the given value
//   //      *
//   //      * @param v the value for all elements
//   //      *
//   //      * @return a matrix will all elements set to the give value
//   //      */
//   //     inline static constexpr auto fill(T const v) noexcept -> Matrix
//   //     {
//   //       return Matrix{v};
//   //     }

//   //     /**
//   //      * Return an Identity matrix
//   //      *
//   //      * @return a matrix with 1's on the diagonal
//   //      */
//   //     inline static constexpr auto identity() noexcept -> Matrix
//   //     {
//   //       return Matrix{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
//   //     }

//   //     /**
//   //      * Return a Matrix will all values set to the given value
//   //      *
//   //      * @param v the value for all elements
//   //      *
//   //      * @return a matrix will all elements set to the give value
//   //      */
//   //     inline static constexpr auto zero() noexcept -> Matrix
//   //     {
//   //       return Matrix{0};
//   //     }

//   //     /**
//   //      * Return the column vector at the given index
//   //      *
//   //      * @param i column index
//   //      *
//   //      * @return the column vector at the given index
//   //      */
//   //     inline constexpr auto operator[](std::size_t i) noexcept -> Vector<T, 3> &
//   //     {
//   //       return columns[i];
//   //     }

//   //     /**
//   //      * Return the column vector at the given index
//   //      *
//   //      * @param i column index
//   //      *
//   //      * @return the column vector at the given index
//   //      */
//   //     inline constexpr auto operator[](std::size_t i) const noexcept -> Vector<T, 3> const &
//   //     {
//   //       return columns[i];
//   //     }

//   //     //  struct {
//   //     //   std::enable_if_t < is_vec_type<T>::value,std::array<Vector<T, 2>, 2>> columns;
//   //     // } impl_;

//   //     union
//   //     {
//   //       std::enable_if_t<is_vec_type<T>::value, std::array<Vector<T, 3>, 3>> columns;
//   //       T data[Size];
//   //     };
//   //   };

//   //   /**
//   //    * An '4x4' Matrix.
//   //    */
//   //   template <typename T>
//   //   class Matrix<T, 4, 4>
//   //   {
//   //   public:
//   //     /// The Underlying type of this matrix
//   //     using Type = T;

//   //     enum : std::size_t
//   //     {
//   //       Rows = 4, /// the number of rows in this matrix
//   //       Cols = 4, /// the number of columns in this matrix
//   //     };

//   //     /// the number of elements in this matrix
//   //     static const std::size_t Size = Rows * Cols;

//   //     /**
//   //      * Return the column vector at the given index
//   //      *
//   //      * @param i column index
//   //      *
//   //      * @return the column vector at the given index
//   //      */
//   //     inline constexpr auto operator[](std::size_t i) noexcept -> Vector<T, 4> &
//   //     {
//   //       return columns[i];
//   //     }

//   //     /**
//   //      * Return the column vector at the given index
//   //      *
//   //      * @param i column index
//   //      *
//   //      * @return the column vector at the given index
//   //      */
//   //     inline constexpr auto operator[](std::size_t i) const noexcept -> Vector<T, 4> const &
//   //     {
//   //       return columns[i];
//   //     }

//   //     union
//   //     {
//   //       std::enable_if_t<is_vec_type<T>::value, std::array<Vector<T, 4>, 4>> columns;
//   //       T data[Size];
//   //     };
//   //   };

//   //   /**
//   //    * Overload std::begin()
//   //    */
//   //   template <typename T, std::size_t R, std::size_t C>
//   //   inline constexpr auto begin(Matrix<T, R, C> const &m) -> decltype(m.columns.begin())
//   //   {
//   //     return m.columns.begin();
//   //   }

//   //   /**
//   //    * Overload std::begin()
//   //    */
//   //   template <typename T, std::size_t R, std::size_t C>
//   //   inline constexpr auto begin(Matrix<T, R, C> &m) -> decltype(m.columns.begin())
//   //   {
//   //     return m.columns.begin();
//   //   }

//   //   /**
//   //    * Overload std::end()
//   //    */
//   //   template <typename T, std::size_t R, std::size_t C>
//   //   inline constexpr auto end(Matrix<T, R, C> const &m) -> decltype(m.columns.end())
//   //   {
//   //     return m.columns.end();
//   //   }

//   //   /**
//   //    * Overload std::end()
//   //    */
//   //   template <typename T, std::size_t R, std::size_t C>
//   //   inline constexpr auto end(Matrix<T, R, C> &m) -> decltype(m.columns.begin())
//   //   {
//   //     return m.columns.end();
//   //   }

//   //   /**
//   //    * Determines if two Matrices are equal.
//   //    *
//   //    * @tparam T The component type of the lhs and rhs
//   //    * @tparam R The number of rows of both lhs and rhs
//   //    * @tparam C The number of columns of both lhs and rhs
//   //    *
//   //    * @param lhs the left-hand operand
//   //    * @param rhs the right-hand operand
//   //    * @return true if lhs and rhs are equal
//   //    */
//   //   template <typename T, std::size_t R, std::size_t C>
//   //   inline auto operator==(Matrix<T, R, C> const &lhs,
//   //                          Matrix<T, R, C> const &rhs) noexcept -> bool
//   //   {
//   //     using std::begin;
//   //     using std::end;
//   //     return detail::equal(begin(lhs), end(lhs), begin(rhs));
//   //   }

//   //   /**
//   //    * Determines if two Matrices are not equal.
//   //    *
//   //    * @tparam T The component type of the lhs and rhs
//   //    * @tparam R The number of rows of both lhs and rhs
//   //    * @tparam C The number of columns of both lhs and rhs
//   //    *
//   //    * @param lhs the left-hand operand
//   //    * @param rhs the right-hand operand
//   //    * @return true if lhs and rhs are not equal
//   //    */
//   //   template <typename T, std::size_t R, std::size_t C>
//   //   inline auto operator!=(Matrix<T, R, C> const &lhs,
//   //                          Matrix<T, R, C> const &rhs) noexcept -> bool
//   //   {
//   //     return !(lhs == rhs);
//   //   }

//   //   /**
//   //    * Scale a matrix
//   //    *
//   //    * @tparam T The component type of the lhs and rhs
//   //    * @tparam R The number of rows of both lhs and rhs
//   //    * @tparam C The number of columns of both lhs and rhs
//   //    *
//   //    * @param lhs the left-hand operand
//   //    * @param rhs the right-hand operand
//   //    * @return true if lhs and rhs are not equal
//   //    */
//   //   template <typename T, std::size_t R, std::size_t C>
//   //   inline auto operator*(Matrix<T, R, C> const &lhs,
//   //                         T const &value) noexcept -> Matrix<T, R, C> const
//   //   {
//   //     Matrix<T, R, C> res{lhs};
//   //     return res *= value;
//   //   }

//   // } // namespace cagey::math
