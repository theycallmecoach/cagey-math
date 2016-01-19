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

#include <cagey-math/MathFwd.hh>
#include <cagey-math/detail/MetaUtil.hh>
#include <cagey-math/detail/vec_type.hh>
#include <cagey-math/detail/VectorOpImpl.hh>

// namespace cagey::math {
//   /**
//    * Checks if the given type can be used as a Vector component.  Supported
//    * types are the following:
//
//    *            - `float`
//    *            - `double`
//    *            - `std::int8_t`
//    *            - `std::int16_t`
//    *            - `std::int32_t`
//    *            - `std::int64_t`
//    *            - `std::uint8_t`
//    *            - `std::uint16_t`
//    *            - `std::uint32_t`
//    *            - `std::uint64_t`
//    *
//    * @tparam T the type to check
//    */
//   template <typename T> struct is_vec_type;
// }

namespace cagey::math {

  /**
   * An 'N' - Dimensional Vector.
   */
  template <typename T, std::size_t N> class Vector {
  public:
    /// The underlying data type
    using Type = T;

    /// The number of elements in this Point
    const static std::size_t Size = N;

    ////////////////////////////////////////////////////////////////////////////
    /// Constructors
    ////////////////////////////////////////////////////////////////////////////

    /**
     * Default Construct all Vector components.
     */
    inline constexpr Vector() noexcept = default;

    /**
     * Construct each component with the same value.
     *
     * @param  v The value to initialize each component
     */
    template <typename U, typename V = typename std::enable_if<
                              std::is_same<T, U>::value && N != 1, T>::type,
              typename Indices = std::make_index_sequence<N>>
    inline explicit constexpr Vector(U const v) noexcept
        : Vector(Indices(), v) {}

    /**
     * Construct each component with the given values.
     *
     * @param first a component
     * @param next all other components
     */
    template <typename... U, typename V = typename std::enable_if<
                                 sizeof...(U) + 1 == N, T>::type>
    inline constexpr Vector(T first, U... next) : data{first, next...} {}

    ////////////////////////////////////////////////////////////////////////////
    /// Operators
    ////////////////////////////////////////////////////////////////////////////

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
    inline auto operator[](std::size_t i) noexcept -> T &;

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
    inline constexpr auto operator[](std::size_t i) const noexcept -> T const &;

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
    inline constexpr auto operator+=(Vector const &v) noexcept -> Vector &;

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
    inline constexpr auto operator-=(Vector const &v) noexcept -> Vector &;

    /**
     * Multiplies each component of this Vector by x.
     *
     * @tparam U The type of parameter x.
     *
     * @param x The value to multiply against each component of this Vector
     *
     * @return A reference to this Vector.
     */
    inline constexpr auto operator*=(T const x) noexcept -> Vector &;

    /**
     * Divides each component of this Vector by x.
     *
     * @tparam U The type of parameter x.
     *
     * @param x The value to use to divide each component of this Vector
     *
     * @return A reference to this Vector.
     */
    inline constexpr auto operator/=(T const x) noexcept -> Vector &;

    ////////////////////////////////////////////////////////////////////////////
    /// Member Functions
    ////////////////////////////////////////////////////////////////////////////

    /**
     * Returns an iterator pointing to the first component
     *
     * @return A pointer to this Vectors data
     */
    inline auto begin() noexcept -> T * { return data.begin(); }

    /**
     * Returns an iterator pointing to the first component
     *
     * @return A pointer to this Vectors data
     */
    inline constexpr auto begin() const noexcept -> T const * {
      return data.begin();
    }

    /**
     * Returns an iterator pointing to the last component
     *
     * @return A pointer to this Vectors data
     */
    inline auto end() noexcept -> T * { return data.end(); }

    /**
     * Returns an iterator pointing to the last component
     *
     * @return A pointer to this Vectors data
     */
    inline auto end() const noexcept -> T const * { return data.end(); }

    ////////////////////////////////////////////////////////////////////////////
    /// Data Members
    ////////////////////////////////////////////////////////////////////////////

    /// Data representation
    std::enable_if_t<is_vec_type<T>::value, std::array<T, N>> data;

  private:
    /**
     * Construct all components using the value of 'v'
     *
     * @param v A value for all components
     */
    template <typename U, std::size_t... I>
    constexpr Vector(std::index_sequence<I...>, U const v)
        : data{detail::repeat(v, I)...} {}
  };

  /**
   * An '2' Dimensional Vector.
   */
  template <typename T> class Vector<T, 2> {
  public:
    /// The underlying data type
    using Type = T;

    /// The number of elements in this Point
    const static std::size_t Size = 2;

    ////////////////////////////////////////////////////////////////////////////
    /// Constructors
    ////////////////////////////////////////////////////////////////////////////

    inline constexpr Vector() noexcept = default;

    inline explicit constexpr Vector(T const v) noexcept : data{v, v} {};

    inline constexpr Vector(T const x, T const y) noexcept : data{x, y} {};

    template <typename U, std::size_t S>
    inline constexpr Vector(Vector<U, S> const &v) noexcept
        : data{{T(v[0]), T(v[1])}} {}

    ////////////////////////////////////////////////////////////////////////////
    /// Operators
    ////////////////////////////////////////////////////////////////////////////

    inline auto operator[](std::size_t i) noexcept -> T & { return data[i]; }

    inline constexpr auto operator[](std::size_t i) const noexcept
        -> T const & {
      return data[i];
    }

    inline constexpr auto operator+=(Vector const &v) noexcept -> Vector & {
      std::get<0>(data) += v[0];
      std::get<1>(data) += v[1];
      return *this;
    }

    inline constexpr auto operator-=(Vector const &v) noexcept -> Vector & {
      std::get<0>(data) -= v[0];
      std::get<1>(data) -= v[1];
      return *this;
    }

    inline constexpr auto operator*=(T const v) noexcept -> Vector & {
      std::get<0>(data) *= v;
      std::get<1>(data) *= v;
      return *this;
    }

    inline constexpr auto operator/=(T const v) noexcept -> Vector & {
      std::get<0>(data) /= v;
      std::get<1>(data) /= v;
      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    /// Member Functions
    ////////////////////////////////////////////////////////////////////////////
    inline auto begin() noexcept -> T * { return data.begin(); }
    inline constexpr auto begin() const noexcept -> T const * {
      return data.begin();
    }
    inline auto end() noexcept -> T * { return data.end(); }
    inline constexpr auto end() const noexcept -> T const * {
      return data.end();
    }

    ////////////////////////////////////////////////////////////////////////////
    /// Data Members
    ////////////////////////////////////////////////////////////////////////////

    /**
     * Anonymous union to allow access to members using different names
     */
    union {
      std::enable_if_t<is_vec_type<T>::value, std::array<T, 2>> data;
      struct {
        T x;
        T y;
      };
      struct {
        T r;
        T g;
      };
      struct {
        T w;
        T h;
      };
    };
  };

  /**
   * Compute the component wise product of rhs and lhs.
   *
   * @tparam U The type of the components of lhs
   * @tparam T The component type of the rhs
   * @tparam N The number of components in rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the product of lhs and each component of rhs
   */
  template <typename U, typename T, std::size_t N>
  inline constexpr auto operator*(U const lhs,
                                  Vector<T, N> rhs) noexcept->Vector<T, N> {
    return rhs *= lhs;
  }

  /**
   * Compute the component wise product of rhs and lhs.
   *
   * @tparam U The type of the components of rhs
   * @tparam T The component type of the lhs
   * @tparam N The number of components of the lhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the product of lhs and each component of rhs
   */
  template <typename U, typename T, std::size_t N>
  inline constexpr auto operator*(Vector<T, N> lhs,
                                  U const rhs) noexcept->Vector<T, N> {
    return lhs *= rhs;
  }

  /**
   * Compute the component wise quotients of rhs and lhs.
   *
   * @tparam U The type of the components of lhs
   * @tparam T The component type of the rhs
   * @tparam N The number of components in rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the quotients of lhs and each component of rhs
   */
  template <typename U, typename T, std::size_t N>
  inline constexpr auto operator/(U const lhs,
                                  Vector<T, N> rhs) noexcept->Vector<T, N> {
    return rhs /= lhs;
  }

  /**
   * Compute the component wise quotients of rhs and lhs.
   *
   * @tparam U The type of the components of rhs
   * @tparam T The component type of the lhs
   * @tparam N The number of components of the lhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the quotients of lhs and each component of rhs
   */
  template <typename U, typename T, std::size_t N>
  inline constexpr auto operator/(Vector<T, N> lhs,
                                  U const rhs) noexcept->Vector<T, N> {
    return lhs /= rhs;
  }

} // namespace cagey::math
