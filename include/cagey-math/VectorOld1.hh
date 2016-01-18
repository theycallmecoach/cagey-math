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
#include <array>
#include <numeric> //for std::numeric_limits
#include <cagey-math/MathFwd.hh>

namespace cagey::math {
  /**
   * Checks if the given type can be used as a Vector component.  Supported
   * types are the following:

   *            - `float`
   *            - `double`
   *            - `std::int8_t`
   *            - `std::int16_t`
   *            - `std::int32_t`
   *            - `std::int64_t`
   *            - `std::uint8_t`
   *            - `std::uint16_t`
   *            - `std::uint32_t`
   *            - `std::uint64_t`
   *
   * @tparam T the type to check
   */
  template <typename T> struct is_vec_type;
}

#include "detail/vec_type.hh"

namespace cagey::math {

  // /**
  //  * An N dimensional vector.
  //  *
  //  * @tparam T component type.  is_vec_type<T>::value must be true
  //  * @tparam N the number of components. Supported values are 2, 3, and 4
  //  */
  // template <typename T, std::size_t N> struct Vector;
  //
  // /**
  //  * 2 Dimensional Vector
  //  * @tparam T component type.  is_vec_type<T>::value must be true.
  //  **/
  // template <typename T> using Vec2 = Vector<T, 2>;
  //
  // /**
  //  * 3 Dimensional Vector
  //  * @tparam T component type.  is_vec_type<T>::value must be true.
  //  **/
  // template <typename T> using Vec3 = Vector<T, 3>;
  //
  // /**
  //  * 4 Dimensional Vector
  //  * @tparam T component type.  is_vec_type<T>::value must be true.
  //  **/
  // template <typename T> using Vec4 = Vector<T, 4>;
  //
  // /**
  //  * 2 Dimensional Vector with float components.
  //  **/
  // using Vec2f = Vec2<float>;
  //
  // /**
  //  * 2 Dimensional Vector with double components.
  //  **/
  // using Vec2d = Vec2<double>;
  // /**
  //  * 2 Dimensional Vector with int components.
  //  **/
  // using Vec2i = Vec2<int>;
  //
  // /**
  //  * 2 Dimensional Vector with unsigned int components.
  //  **/
  // using Vec2u = Vec2<unsigned int>;
  //
  // /**
  //  * 3 Dimensional Vector with float components.
  //  **/
  // using Vec3f = Vec3<float>;
  //
  // /**
  //  * 3 Dimensional Vector with double components.
  //  **/
  // using Vec3d = Vec3<double>;
  //
  // /**
  //  * 3 Dimensional Vector with int components.
  //  **/
  // using Vec3i = Vec3<int>;
  //
  // /**
  //  * 3 Dimensional Vector with unsigned int components.
  //  **/
  // using Vec3u = Vec3<unsigned int>;
  //
  // /**
  //  * 4 Dimensional Vector with float components.
  //  **/
  // using Vec4f = Vec4<float>;
  //
  // /**
  //  * 4 Dimensional Vector with double components.
  //  **/
  // using Vec4d = Vec4<double>;
  //
  // /**
  //  * 4 Dimensional Vector with int components.
  //  **/
  // using Vec4i = Vec4<int>;
  //
  // /**
  //  * 4 Dimensional Vector with unsigned int components.
  //  **/
  // using Vec4u = Vec4<unsigned int>;

  /**/
  template <typename T, std::size_t N> struct Vector {

    static_assert(N >= 2 && N <= 4,
                  "Vector must have between 2 and 4 components");

    /**
     * This Vector's component type.
     */
    using Type = T;

    /**
     * The number of components in this Vector.
     */
    static constexpr std::size_t Size = N;

    /**
     * Returns a Vector with each component set to 0.
     *
     * @return A Vector with each component set to 0
     */
    inline static constexpr auto zero() noexcept -> Vector<T, N>;

    /**
     * Returns a Vector with the first component set to 1 and all other
     * components set to 0.
     *
     * @return A Vector with the first component set to 1 and all other
     * components set to 0.
     */
    inline static constexpr auto xAxis() noexcept -> Vector<T, N>;

    /**
     * Returns a Vector with the second component set to 1 and all other
     * components set to 0.
     *
     * @return A Vector with the second component set to 1 and all other
     * components set to 0.
     */
    inline static constexpr auto yAxis() noexcept -> Vector<T, N>;

    /**
     * Returns a Vector with the third component set to 1 and all other
     * components set to 0.
     *
     * Note: Function only available when N > 2.
     *
     * @return A Vector with the third component set to 1 and all other
     * components set to 0.
     */
    inline static constexpr auto zAxis() noexcept -> Vector<T, N>;

    /**
     * Returns a Vector with the forth component set to 1 and all other
     * components set to 0.
     *
     * Note: Function only available when N > 3.
     *
     * @return A Vector with the forth component set to 1 and all other
     * components set to 0.
     */
    inline static constexpr auto wAxis() noexcept -> Vector<T, N>;

    /**
     * Default Construct all Vector components.
     */
    constexpr Vector() noexcept = default;

    /**
     * Construct each component with the same value.
     *
     * @param  v The value to initialize each component
     */
    inline explicit constexpr Vector(T v) noexcept;

    /**
     * Construct each component with the value of the corresponding parameter.
     *
     * This constructor is only available when N = 2.
     *
     * @param  x The value to init the first component.
     * @param  y The value to init the second component.
     */
    inline constexpr Vector(T x, T y) noexcept;

    /**
     * Construct each component with the value of the corresponding parameter.
     *
     * This constructor is only available when N = 3.
     *
     * @param  x The value to init the first component.
     * @param  y The value to init the second component.
     * @param  z The value to init the third component.
     */
    inline constexpr Vector(T x, T y, T z) noexcept;

    /**
     * Construct each component with the value of the corresponding parameter.
     *
     * This constructor is only available when N = 4.
     *
     * @param  x The value to init the first component.
     * @param  y The value to init the second component.
     * @param  z The value to init the third component.
     * @param  w The value to init the forth component.
     */
    inline constexpr Vector(T x, T y, T z, T w) noexcept;

    /**
     * Construct each component with the value of the corresponding parameter.
     *
     * This constructor is only available when N = 3.
     *
     * @param  xy The value to init the first and second components.
     * @param  z The value to init the second component.
     */
    inline constexpr Vector(Vec2<T> const &xy, T z) noexcept;

    /**
     * Construct each component with the value of the corresponding parameter.
     *
     * This constructor is only available when N = 4.
     *
     * @param  xy The value to init the first and second components.
     * @param  z The value to init the second component.
     * @param  w The value to init the forth component.
     */
    inline constexpr Vector(Vec2<T> const &xy, T z, T w) noexcept;

    /**
     * Construct each component with the value of the corresponding parameter.
     *
     * This constructor is only available when N = 4.
     *
     * @param  xy The value to init the first,second and third components.
     * @param  w The value to init the forth component.
     */
    inline constexpr Vector(Vec3<T> const &xyz, T w) noexcept;

    /**
     * Construct each component with the values pointed at by val.  Note
     * arrays which are not of size N cause undefined behaviour.
     *
     * @param  val A pointer to an array
     */
    inline constexpr Vector(T *const val) noexcept;

    /**
     * Construct each component with the value of the corresponding array
     * element.
     *
     * @param  vals An array of values
     */
    inline constexpr Vector(std::array<T, N> const &vals) noexcept;

    /**
     * Downsizes a larger vector with same type.
     *
     * @tparam VN the size of v
     *
     * @param v Vector to trucate.
     **/
    template <int VN, typename = std::enable_if_t<(VN > N)>>
    inline explicit constexpr Vector(Vector<T, VN> const &v) noexcept;

    /**
     * Cast given Vector with different Type.
     *
     * @tparam U The type of vec
     *
     * @param vec The vec to cast.
     */
    template <typename U>
    inline explicit constexpr Vector(Vector<U, N> const &vec) noexcept;

    /**
     * Implicitly cast this vector to a different type.
     *
     * @tparam U The new component type.
     *
     * @return A new Vector with type U.
     */
    template <typename U>
    inline constexpr operator Vector<U, N>() const noexcept;

    /**
     * Return a reference to the component at the given index.
     *
     * This function does not perform any bounds checking
     *
     * @tparam I index type.
     *
     * @param i the index.
     *
     * @return a reference to the component at the given index.
     */
    template <typename I>
    inline constexpr auto operator[](I i) const noexcept -> T &;

    /**
     * Return a reference to the component at the given index.
     *
     * This function does not perform any bounds checking
     *
     * @tparam I index type.
     *
     * @param i the index.
     *
     * @return a reference to the component at the given index.
     */
    template <typename I> inline constexpr auto operator[](I i) noexcept -> T &;

    /**
     * Returns an iterator pointing to the first component
     *
     * @return A pointer to this Vectors data
     */
    inline constexpr auto begin() const noexcept -> T const *;

    /**
     * Returns an iterator pointing to the first component
     *
     * @return A pointer to this Vectors data
     */
    inline constexpr auto begin() noexcept -> T *;

    /**
     * Returns an iterator pointing to the last component
     *
     * @return A pointer to this Vectors data
     */
    inline constexpr auto end() const noexcept -> T const *;

    /**
     * Returns an iterator pointing to the last component
     *
     * @return A pointer to this Vectors data
     */
    inline constexpr auto end() noexcept -> T *;

    // /**
    //  * Sets the first two components of this Vector
    //  * @param  x the new value for the first component
    //  * @param  y the new value for the second component
    //  */
    // inline auto set(T const x, T const y) noexcept -> void;
    //
    // /**
    //  * Sets the first three components of this Vector.  This overload is
    //  * only available when the size of this vector is greater than 2
    //  * @param  x the new value for the first component
    //  * @param  y the new value for the second component
    //  * @param  z the new value for the third component
    //  */
    // inline auto set(T const x, T const y, T const z) noexcept -> void;
    //
    // /**
    //  * Sets the first four components of this Vector.  This overload is
    //  * only available when the size of this vector is greater than 3
    //  * @param  x the new value for the first component
    //  * @param  y the new value for the second component
    //  * @param  z the new value for the third component
    //  * @param  w the new value for the fourth component
    //  */
    // inline auto set(T const x, T const y, T const z, T const w) noexcept
    //     -> void;

    /**
     * Pre-increments each component of this Vector.
     *
     * @return A reference to this Vector.
     */
    inline auto operator++() noexcept -> Vector<T, N> &;

    /**
     * Post-increments each component of this Vector.
     *
     * @return A copy of this Vector before it is incremented
     */
    inline auto operator++(int) noexcept -> Vector<T, N>;

    /**
     * Pre-decrements each component of this Vector.
     *
     * @return A reference to this Vector.
     */
    inline auto operator--() noexcept -> Vector<T, N> &;

    /**
     * Post-decrements each component of this Vector.
     *
     * @return A copy of this Vector before it is decremented
     */
    inline auto operator--(int) noexcept -> Vector<T, N>;

    /**
     * Add x to each component of this Vector.
     *
     * @tparam U The type of X
     *
     * @param x The value to add to each component of this Vector
     * @return A reference to this Vector
     */
    template <typename U>
    inline auto operator+=(U x) noexcept
        -> std::enable_if_t<is_vec_type<U>::value, Vector<T, N> &>;

    /**
     * Add each component of the given vector to the corresponding component
     * of this Vector.
     *
     * @tparam U The component type of v
     *
     * @param v The values to add to this Vectors components.
     *
     * @return A reference to this Vector
     */
    template <typename U>
    inline auto operator+=(Vector<U, N> const &v) noexcept -> Vector<T, N> &;

    /**
     * Subtract x from the corresponding component of this Vector.
     *
     * @tparam U The component type of v
     *
     * @param v The values to add to this Vectors components.
     *
     * @return A reference to this Vector
     */
    template <typename U>
    inline auto operator-=(U x) noexcept
        -> std::enable_if_t<is_vec_type<U>::value, Vector<T, N> &>;

    /**
     * Subtract each component of the given vector from the corresponding
     * component
     * of this Vector.
     *
     * @tparam U The component type of v
     *
     * @param v The values to add to this Vectors components.
     *
     * @return A reference to this Vector
     */
    template <typename U>
    inline auto operator-=(Vector<U, N> const &v) noexcept -> Vector<T, N> &;

    /**
     * Multiplies each component of this Vector by x.
     *
     * @tparam U The type of parameter x.
     *
     * @param x The value to multiply against each component of this Vector
     *
     * @return A reference to this Vector.
     */
    template <typename U>
    inline auto operator*=(U x) noexcept
        -> std::enable_if_t<is_vec_type<U>::value, Vector<T, N> &>;

    /**
     * Multiplies each component of this Vector by the corresponding
     * component
     * from the given Vector v.
     *
     * @tparam U The component type of v.
     *
     * @param v The values to multiply each component of this Vector
     *
     * @return A reference to this Vector.
     */
    template <typename U>
    inline auto operator*=(Vector<U, N> const &v) noexcept -> Vector<T, N> &;

    /**
     * Divides each component of this Vector by x.
     *
     * @tparam U The type of parameter x.
     *
     * @param x The value to use to divide each component of this Vector
     *
     * @return A reference to this Vector.
     */
    template <typename U>
    inline auto operator/=(U x) noexcept
        -> std::enable_if_t<is_vec_type<U>::value, Vector<T, N> &>;

    /**
     * Divides each component of this Vector by the corresponding
     * component from the given Vector v.
     *
     * @tparam U The component type of v.
     *
     * @param v The values to use to  divide each component of this Vector
     *
     * @return A reference to this Vector.
     */
    template <typename U>
    inline auto operator/=(Vector<U, N> const &v) noexcept -> Vector<T, N> &;

    /**
     * Vector Component representation;
     */
    std::array<T, N> data;
  };
}

#include "detail/Vector2.hh"
//#include "detail/Vector3.hh"
//#include "detail/Vector4.hh"
#include "detail/VectorOpImpl.hh"

namespace cagey::math {

  /**
   * Compute the sum of the lhs and each component of rhs.
   *
   * @tparam T The component type of the lhs
   * @tparam U The component type of the rhs
   * @tparam N The number of components of both lhs and rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the sum of lhs and each component of rhs
   */
  template <typename T, typename U, std::size_t N,
            typename Indices = std::make_index_sequence<N>>
  inline constexpr auto operator+(T const lhs, Vector<U, N> const &rhs) noexcept
      ->std::enable_if_t<
          is_vec_type<T>::value,
          Vector<decltype(std::declval<T>() + std::declval<U>()), N>> {
    return detail::additionOperatorScalarVector(lhs, rhs, Indices());
  }

  /**
   * Compute the sum of the each component of lhs and rhs.
   *
   * @tparam T The component type of the lhs
   * @tparam U The component type of the rhs
   * @tparam N The number of components of both lhs and rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the sum of rhs and each component of lhs
   */
  template <typename T, typename U, std::size_t N,
            typename Indices = std::make_index_sequence<N>>
  inline constexpr auto operator+(Vector<T, N> const &lhs, U const rhs) noexcept
      ->std::enable_if_t<
          is_vec_type<T>::value,
          Vector<decltype(std::declval<T>() + std::declval<U>()), N>> {
    return detail::additionOperatorVectorScalar(lhs, rhs, Indices());
  }

  /**
   * Compute the component wise sum of the lhs and rhs.
   *
   * @tparam T The component type of the lhs
   * @tparam U The component type of the rhs
   * @tparam N The number of components of both lhs and rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the component wise sum of lhs and rhs
   */
  template <typename T, typename U, std::size_t N,
            typename Indices = std::make_index_sequence<N>>
  inline constexpr auto operator+(Vector<T, N> const &lhs,
                                  Vector<U, N> const &rhs) noexcept
      ->std::enable_if_t<
          is_vec_type<T>::value,
          Vector<decltype(std::declval<T>() + std::declval<U>()), N>> {
    return detail::additionOperatorVector(lhs, rhs, Indices());
  }

  /**
   * Negates each component of v
   *
   * @tparam T The component type of v
   * @tparam N The number of components of v
   *
   * @param v A Vector.
   * @return The negation of each component of v
   */
  template <typename T, std::size_t N,
            typename Indices = std::make_index_sequence<N>>
  inline constexpr auto operator-(
      Vector<T, N> const &v) noexcept->Vector<decltype(-std::declval<T>()), N> {
    return detail::unaryMinusOperatorVector(v, Indices());
  }

  /**
   * Compute the differences of the lhs and each component of rhs.
   *
   * @tparam T The component type of the lhs
   * @tparam U The component type of the rhs
   * @tparam N The number of components of both lhs and rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the differences of lhs and each component of rhs
   */
  template <typename T, typename U, std::size_t N,
            typename Indices = std::make_index_sequence<N>>
  inline constexpr auto
  operator-(T const &lhs, Vector<U, N> const &rhs) noexcept->std::enable_if_t<
      is_vec_type<T>::value,
      Vector<decltype(std::declval<T>() - std::declval<U>()), N>> {
    return detail::subtractionOperatorScalarVector(lhs, rhs, Indices());
  }

  /**
   * Compute the differences of the each component of lhs and rhs.
   *
   * @tparam T The component type of the lhs
   * @tparam U The component type of the rhs
   * @tparam N The number of components of both lhs and rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the differences of rhs and each component of lhs
   */
  template <typename T, typename U, std::size_t N,
            typename Indices = std::make_index_sequence<N>>
  inline constexpr auto
  operator-(Vector<U, N> const &lhs, T const &rhs) noexcept->std::enable_if_t<
      is_vec_type<T>::value,
      Vector<decltype(std::declval<T>() - std::declval<U>()), N>> {
    return detail::subtractionOperatorVectorScalar(lhs, rhs, Indices());
  }

  /**
   * Compute the component wise difference of the lhs and rhs.
   *
   * @tparam T The component type of the lhs
   * @tparam U The component type of the rhs
   * @tparam N The number of components of both lhs and rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the differences of lhs and rhs
   */
  template <typename T, typename U, std::size_t N,
            typename Indices = std::make_index_sequence<N>>
  inline constexpr auto operator-(Vector<T, N> const &lhs,
                                  Vector<U, N> const &rhs) noexcept
      ->std::enable_if_t<
          is_vec_type<T>::value,
          Vector<decltype(std::declval<T>() - std::declval<U>()), N>> {
    return detail::subtractionOperatorVector(lhs, rhs, Indices());
  }

  /**
   * Computes the products of lhs and each component of rhs
   *
   * @tparam T The component type of the lhs
   * @tparam U The component type of the rhs
   * @tparam N The number of components of both lhs and rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the component wise product of lhs and rhs
   */
  template <typename T, typename U, std::size_t N,
            typename Indices = std::make_index_sequence<N>>
  inline constexpr auto operator
      *(T const &lhs, Vector<U, N> const &rhs) noexcept->std::enable_if_t<
          is_vec_type<T>::value,
          Vector<decltype(std::declval<T>() * std::declval<U>()), N>> {
    return detail::multiplicationOperatorScalarVector(lhs, rhs, Indices());
  }

  /**
   * Computes the products of each components of lhs and rhs
   *
   * @tparam T The component type of the lhs
   * @tparam U The component type of the rhs
   * @tparam N The number of components of both lhs and rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the component wise product of lhs and rhs
   */
  template <typename T, typename U, std::size_t N,
            typename Indices = std::make_index_sequence<N>>
  inline constexpr auto operator
      *(Vector<T, N> const &lhs, U const &rhs) noexcept->std::enable_if_t<
          is_vec_type<T>::value,
          Vector<decltype(std::declval<T>() * std::declval<U>()), N>> {
    return detail::multiplicationOperatorVectorScalar(lhs, rhs, Indices());
  }

  /**
   * Compute the component wise products of the lhs and rhs.
   *
   * @tparam T The component type of the lhs
   * @tparam U The component type of the rhs
   * @tparam N The number of components of both lhs and rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the products of lhs and rhs
   */
  template <typename T, typename U, std::size_t N,
            typename Indices = std::make_index_sequence<N>>
  inline constexpr auto operator*(Vector<T, N> const &lhs,
                                  Vector<U, N> const &rhs) noexcept
      ->std::enable_if_t<
          is_vec_type<T>::value,
          Vector<decltype(std::declval<T>() * std::declval<U>()), N>> {
    return detail::multiplicationOperatorVector(lhs, rhs, Indices());
  }

  /**
   * Computes the quotients of lhs and each component of rhs
   *
   * @tparam T The component type of the lhs
   * @tparam U The component type of the rhs
   * @tparam N The number of components of both lhs and rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the component wise quotients of lhs and rhs
   */
  template <typename T, typename U, std::size_t N,
            typename Indices = std::make_index_sequence<N>>
  inline constexpr auto
  operator/(T const &lhs, Vector<U, N> const &rhs) noexcept->std::enable_if_t<
      is_vec_type<T>::value,
      Vector<decltype(std::declval<T>() / std::declval<U>()), N>> {
    return detail::divisionOperatorScalarVector(lhs, rhs, Indices());
  }

  /**
   * Computes the quotients of each component of lhs and rhs
   *
   * @tparam T The component type of the lhs
   * @tparam U The component type of the rhs
   * @tparam N The number of components of both lhs and rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the component wise quotients of lhs and rhs
   */
  template <typename T, typename U, std::size_t N,
            typename Indices = std::make_index_sequence<N>>
  inline constexpr auto
  operator/(Vector<T, N> const &lhs, U const &rhs) noexcept->std::enable_if_t<
      is_vec_type<T>::value,
      Vector<decltype(std::declval<T>() / std::declval<U>()), N>> {
    return detail::divisionOperatorVectorScalar(lhs, rhs, Indices());
  }

  /**
   * Compute the component wise quotients of the lhs and rhs.
   *
   * @tparam T The component type of the lhs
   * @tparam U The component type of the rhs
   * @tparam N The number of components of both lhs and rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the quotients of lhs and rhs
   */
  template <typename T, typename U, std::size_t N,
            typename Indices = std::make_index_sequence<N>>
  inline constexpr auto operator/(Vector<T, N> const &lhs,
                                  Vector<U, N> const &rhs) noexcept
      ->std::enable_if_t<
          is_vec_type<T>::value,
          Vector<decltype(std::declval<T>() / std::declval<U>()), N>> {
    return detail::divisionOperatorVector(lhs, rhs, Indices());
  }

  /**
   * Determines if two Vectors are equal.
   *
   * @tparam T The component type of the lhs
   * @tparam U The component type of the rhs
   * @tparam N The number of components of both lhs and rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return true if lhs and rhs are equal
   */
  template <typename T, typename U, std::size_t N,
            typename Indices = std::make_index_sequence<N>>
  inline constexpr auto operator==(Vector<T, N> const &lhs,
                                   Vector<U, N> const &rhs) noexcept->bool {
    // TODO I think I should be able to use some type of meta programming here
    return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs));
  }

  /**
   * Determines the inequality of if two Vectors.
   *
   * @tparam T The component type of the lhs
   * @tparam U The component type of the rhs
   * @tparam N The number of components of both lhs and rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return true if lhs and rhs are not equal
   */
  template <typename T, typename U, std::size_t N>
  inline constexpr auto operator!=(Vector<T, N> const &lhs,
                                   Vector<U, N> const &rhs) noexcept->bool {
    return !(lhs == rhs);
  }

  /**
   * Computes the dot product of lhs and rhs.
   *
   * @tparam T The type of the components of lhs
   * @tparam U The type of the components of rhs
   * @tparam N The number of component of vec
   *
   * @param lhs A Vector
   * @param rhs A Vector
   *
   * @return The dot product of lhs and rhs
   */
  template <typename T, typename U, std::size_t N>
  inline constexpr auto dot(
      Vector<T, N> const &lhs,
      Vector<U, N> const &rhs) noexcept->decltype(std::declval<T>() *
                                                  std::declval<U>()) {
    return detail::dot(lhs, rhs);
  }

  /**
   * Computes the cross product of lhs and rhs.
   *
   * @tparam T The type of the components of lhs
   * @tparam U The type of the components of rhs
   *
   * @param lhs A Vector
   * @param rhs A Vector
   *
   * @return The cross product of lhs and rhs.
   */
  template <typename T, typename U>
  inline constexpr auto cross(Vector<T, 3> const &lhs,
                              Vector<U, 3> const &rhs) noexcept
      ->Vec3<decltype(std::declval<T>() * std::declval<U>())> {
    return {
        lhs[1] * rhs[2] - lhs[2] * rhs[1], lhs[2] * rhs[0] - lhs[0] * rhs[2],
        lhs[0] * rhs[1] - lhs[1] * rhs[0],
    };
  }

  /**
   * Computes the length of vec.
   *
   * @tparam T The type of the components of vec
   * @tparam N The number of component of vec
   * @param vec A Vector
   *
   * @return The length of vec.
   */
  template <typename T, std::size_t N>
  inline auto length(Vector<T, N> const &vec) noexcept->T {
    using std::sqrt;
    return sqrt(lengthSquared(vec));
  }

  /**
   * Computes the length of vec squared.
   *
   * @tparam T The type of the components of vec
   * @tparam N The number of component of vec
   * @param vec A Vector
   *
   * @return The squared length of vec.
   */
  template <typename T, std::size_t N>
  inline constexpr auto lengthSquared(Vector<T, N> const &vec) noexcept->T {
    return dot(vec, vec);
  }

  /**
  * Computes length of vec and returns true if it is zero.
  *
  * @tparam T The type of the components of vec.
  * @tparam S The number of components in vec.
  *
  * @param vec The Vector to check for zero length
  * @return true if length of vec is zero
  */
  template <typename T, std::size_t S>
  inline auto isZeroLength(Vector<T, S> const &vec)->bool {
    T epsilon = std::numeric_limits<T>::epsilon();
    return std::abs(lengthSquared(vec)) < (epsilon * epsilon);
  }

  /**
   * Computes a normalized copy of vec.  If the length of the vec is
   * 0 the behaviour is undefined.
   *
   * @tparam T The type of the components of vec
   * @tparam N The number of component of vec
   *
   * @param vec A Vector
   * @return a normalized copy of vec.
   */
  template <typename T, std::size_t N>
  inline auto normalize(Vector<T, N> vec) noexcept->Vector<T, N> {
    return vec *= (T{1} / length(vec));
  }
}
