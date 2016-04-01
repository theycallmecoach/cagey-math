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
#include <cagey-math/detail/ConstExprUtil.hh>

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
    /// Static Member Functions
    ////////////////////////////////////////////////////////////////////////////
    /**
     * Returns a Vector with each component set to 0.
     *
     * @return A Vector with each component set to 0
     */
    inline static constexpr auto zero() noexcept -> Vector;

    /**
     * Returns a Vector with the first component set to 1 and all other
     * components set to 0.
     *
     * Note: Function only available when N >= 2.
     *
     * @return A Vector with the first component set to 1 and all other
     * components set to 0.
     */
    inline static constexpr auto x_axis() noexcept -> Vector;

    /**
     * Returns a Vector with the second component set to 1 and all other
     * components set to 0.
     *
     * Note: Function only available when N > 1.
     *
     * @return A Vector with the second component set to 1 and all other
     * components set to 0.
     */
    inline static constexpr auto y_axis() noexcept -> Vector;

    /**
     * Returns a Vector with the third component set to 1 and all other
     * components set to 0.
     *
     * Note: Function only available when N > 2.
     *
     * @return A Vector with the third component set to 1 and all other
     * components set to 0.
     */
    inline static constexpr auto z_axis() noexcept -> Vector;

    /**
     * Returns a Vector with the forth component set to 1 and all other
     * components set to 0.
     *
     * Note: Function only available when N > 3.
     *
     * @return A Vector with the forth component set to 1 and all other
     * components set to 0.
     */
    inline static constexpr auto w_axis() noexcept -> Vector;

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
    template <typename... U,
              typename V = typename std::enable_if<sizeof...(U) + 1 == N, T>::type>
    inline constexpr Vector(T first, U... next)
        : data{first, next...} {}


    inline constexpr Vector(Vec2<T> const & xy, T const & z) noexcept
      : data{xy.x, xy.y, z} {}

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
    inline constexpr auto operator[](std::size_t i) noexcept -> T &;

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
    inline constexpr auto begin() noexcept -> T *;

    /**
     * Returns an iterator pointing to the first component
     *
     * @return A pointer to this Vectors data
     */
    inline constexpr auto begin() const noexcept -> T const *;

    /**
     * Returns an iterator pointing to the last component
     *
     * @return A pointer to this Vectors data
     */
    inline constexpr auto end() noexcept -> T *;

    /**
     * Returns an iterator pointing to the last component
     *
     * @return A pointer to this Vectors data
     */
    inline constexpr auto end() const noexcept -> T const *;

    /**
     * @brief Returns a copy of this Vector's first two components
     * @return a copy of this Vector's first two components
     */
    inline constexpr Vec2<T> xy() const noexcept;

    /**
     * @brief Returns a copy of this Vector's first three components
     * @return a copy of this Vector's first three components
     */
    inline constexpr Vec3<T> xyz() const noexcept;

    /**
     * @brief Returns a copy of this Vector's first two components
     * @return a copy of this Vector's first two components
     */
    inline constexpr Vec2<T> rg() const noexcept;

    /**
     * @brief Returns a copy of this Vector's first three components
     * @return a copy of this Vector's first three components
     */
    inline constexpr Vec3<T> rgb() const noexcept;

    ////////////////////////////////////////////////////////////////////////////
    /// Data Members
    ////////////////////////////////////////////////////////////////////////////

    /// Data representation
    /**
     * Anonymous union to allow access to members using different names
     */
    union {
      std::enable_if_t<is_vec_type<T>::value, std::array<T, N>> data;
      T raw[N];
    };

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
    /// Static Member Functions
    ////////////////////////////////////////////////////////////////////////////

    static constexpr auto zero() noexcept -> Vector { return {T(0), T(0)}; }

    static constexpr auto x_axis() noexcept -> Vector { return {T(1), T(0)}; }

    static constexpr auto y_axis() noexcept -> Vector { return {T(0), T(1)}; }

    ////////////////////////////////////////////////////////////////////////////
    /// Constructors
    ////////////////////////////////////////////////////////////////////////////

    inline constexpr Vector() noexcept = default;

    inline explicit constexpr Vector(T const v) noexcept : raw{v, v} {}

    inline constexpr Vector(T const x, T const y) noexcept : raw{x, y} {}

    template <typename U, std::size_t S>
    inline explicit constexpr Vector(Vector<U, S> const &v) noexcept
        : raw{T(v.raw[0]), T(v.raw[1])} {}

    ////////////////////////////////////////////////////////////////////////////
    /// Operators
    ////////////////////////////////////////////////////////////////////////////

    inline constexpr auto operator[](std::size_t i) noexcept -> T & {
      return raw[i];
    }

    inline constexpr auto operator[](std::size_t i) const noexcept
        -> T const & {
      return raw[i];
    }

    inline constexpr auto operator+=(Vector const &v) noexcept -> Vector & {
      raw[0] += v.raw[0];
      raw[1] += v.raw[1];
      return *this;
    }

    inline constexpr auto operator-=(Vector const &v) noexcept -> Vector & {
      raw[0] -= v.raw[0];
      raw[1] -= v.raw[1];
      return *this;
    }

    inline constexpr auto operator*=(T const v) noexcept -> Vector & {
      raw[0] *= v;
      raw[1] *= v;
      return *this;
    }

    inline constexpr auto operator/=(T const v) noexcept -> Vector & {
      raw[0] /= v;
      raw[1] /= v;
      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    /// Member Functions
    ////////////////////////////////////////////////////////////////////////////
    inline constexpr auto begin() noexcept -> T * { return &raw[0]; }

    inline constexpr auto begin() const noexcept -> T const * {
      return &raw[0];
    }

    inline constexpr auto end() noexcept -> T * { return &raw[0] + Size; }

    inline constexpr auto end() const noexcept -> T const * {
      return &raw[0] + Size;
    }

    ////////////////////////////////////////////////////////////////////////////
    /// Data Members
    ////////////////////////////////////////////////////////////////////////////

    /**
     * Anonymous union to allow access to members using different names
     */
    union {
      std::enable_if_t<is_vec_type<T>::value, std::array<T, Size>> data;
      T raw[Size];
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
   * An '3' Dimensional Vector.
   */
  template <typename T> class Vector<T, 3> {
  public:
    /// The underlying data type
    using Type = T;

    /// The number of elements in this Point
    const static std::size_t Size = 3;

    ////////////////////////////////////////////////////////////////////////////
    /// Static Member Functions
    ////////////////////////////////////////////////////////////////////////////

    static constexpr auto zero() noexcept -> Vector {
      return {T(0), T(0), T(0)};
    }

    static constexpr auto x_axis() noexcept -> Vector {
      return {T(1), T(0), T(0)};
    }

    static constexpr auto y_axis() noexcept -> Vector {
      return {T(0), T(1), T(0)};
    }

    static constexpr auto zAxis() noexcept -> Vector {
      return {T(0), T(0), T(1)};
    }

    ////////////////////////////////////////////////////////////////////////////
    /// Constructors
    ////////////////////////////////////////////////////////////////////////////

    inline constexpr Vector() noexcept = default;

    inline explicit constexpr Vector(T const v) noexcept : raw{v, v, v} {}

    inline constexpr Vector(T const x, T const y, T const z) noexcept
        : raw{x, y, z} {};

    inline constexpr Vector(Vec2<T> const &v, T const z) noexcept
        : raw{v[0], v[1], z} {};

    template <typename U, std::size_t S>
    inline explicit constexpr Vector(Vector<U, S> const &v) noexcept
        : raw{T(v.raw[0]), T(v.raw[1]), T(v.raw[2])} {}


    template <std::size_t VN, typename = std::enable_if_t<(VN > 3)>>
    inline explicit constexpr Vector(Vector<T, VN> const & v) noexcept
        : raw{v.raw[0], v.raw[1], v.raw[2]} {}


    ////////////////////////////////////////////////////////////////////////////
    /// Operators
    ////////////////////////////////////////////////////////////////////////////

    inline constexpr auto operator[](std::size_t i) noexcept -> T & {
      return raw[i];
    }

    inline constexpr auto operator[](std::size_t i) const noexcept
        -> T const & {
      return raw[i];
    }

    inline constexpr auto operator+=(Vector const &v) noexcept -> Vector & {
      raw[0] += v.raw[0];
      raw[1] += v.raw[1];
      raw[2] += v.raw[2];
      return *this;
    }

    inline constexpr auto operator-=(Vector const &v) noexcept -> Vector & {
      raw[0] -= v.raw[0];
      raw[1] -= v.raw[1];
      raw[2] -= v.raw[2];
      return *this;
    }

    inline constexpr auto operator*=(T const v) noexcept -> Vector & {
      raw[0] *= v;
      raw[1] *= v;
      raw[2] *= v;
      return *this;
    }

    inline constexpr auto operator/=(T const v) noexcept -> Vector & {
      raw[0] /= v;
      raw[1] /= v;
      raw[2] /= v;
      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    /// Member Functions
    ////////////////////////////////////////////////////////////////////////////
    inline constexpr auto begin() noexcept -> T * { return &raw[0]; }

    inline constexpr auto begin() const noexcept -> T const * {
      return &raw[0];
    }

    inline constexpr auto end() noexcept -> T * { return &raw[0] + Size; }

    inline constexpr auto end() const noexcept -> T const * {
      return &raw[0] + Size;
    }

    inline constexpr Vec2<T> xy() const noexcept {
      return Vec2<T>{x, y};
    }

    inline constexpr Vec3<T> xyz() const noexcept {
      return Vec3<T>{x, y, z};
    }

    inline constexpr Vec2<T> rg() const noexcept {
      return xy();
    }

    inline constexpr Vec3<T> rgb() const noexcept {
      return xyz();
    }

    ////////////////////////////////////////////////////////////////////////////
    /// Data Members
    ////////////////////////////////////////////////////////////////////////////

    /**
     * Anonymous union to allow access to members using different names
     */
    union {
      std::enable_if_t<is_vec_type<T>::value, std::array<T, Size>> data;
      T raw[Size];
      struct {
        T x;
        T y;
        T z;
      };
      struct {
        T r;
        T g;
        T b;
      };
    };
  };

  /**
   * An '4' Dimensional Vector.
   */
  template <typename T> class Vector<T, 4> {
  public:
    /// The underlying data type
    using Type = T;

    /// The number of elements in this Point
    const static std::size_t Size = 4;

    ////////////////////////////////////////////////////////////////////////////
    /// Static Member Functions
    ////////////////////////////////////////////////////////////////////////////

    static constexpr auto zero() noexcept -> Vector {
      return {T(0), T(0), T(0), T(0)};
    }

    static constexpr auto x_axis() noexcept -> Vector {
      return {T(1), T(0), T(0), T(0)};
    }

    static constexpr auto y_axis() noexcept -> Vector {
      return {T(0), T(1), T(0), T(0)};
    }

    static constexpr auto z_axis() noexcept -> Vector {
      return {T(0), T(0), T(1), T(0)};
    }

    static constexpr auto w_axis() noexcept -> Vector {
      return {T(0), T(0), T(0), T(1)};
    }

    ////////////////////////////////////////////////////////////////////////////
    /// Constructors
    ////////////////////////////////////////////////////////////////////////////

    inline constexpr Vector() noexcept = default;

    inline explicit constexpr Vector(T const v) noexcept : raw{v, v, v} {}

    inline constexpr Vector(T const x, T const y, T const z, T const w) noexcept
        : raw{x, y, z, w} {}

    inline constexpr Vector(Vec3<T> const &v, T const w) noexcept
        : raw{v[0], v[1], v[2], w} {}

    template <typename U, std::size_t S>
    inline explicit constexpr Vector(Vector<U, S> const &v) noexcept
        : raw{T(v.raw[0]), T(v.raw[1]), T(v.raw[2]), T(v.raw[3])} {}

    ////////////////////////////////////////////////////////////////////////////
    /// Operators
    ////////////////////////////////////////////////////////////////////////////

    inline constexpr auto operator[](std::size_t i) noexcept -> T & {
      return raw[i];
    }

    inline constexpr auto operator[](std::size_t i) const noexcept
        -> T const & {
      return raw[i];
    }

    inline constexpr auto operator+=(Vector const &v) noexcept -> Vector & {
      raw[0] += v.raw[0];
      raw[1] += v.raw[1];
      raw[2] += v.raw[2];
      raw[3] += v.raw[3];
      return *this;
    }

    inline constexpr auto operator-=(Vector const &v) noexcept -> Vector & {
      raw[0] -= v.raw[0];
      raw[1] -= v.raw[1];
      raw[2] -= v.raw[2];
      raw[3] -= v.raw[3];
      return *this;
    }

    inline constexpr auto operator*=(T const v) noexcept -> Vector & {
      raw[0] *= v;
      raw[1] *= v;
      raw[2] *= v;
      raw[3] *= v;
      return *this;
    }

    inline constexpr auto operator/=(T const v) noexcept -> Vector & {
      raw[0] /= v;
      raw[1] /= v;
      raw[2] /= v;
      raw[3] /= v;
      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    /// Member Functions
    ////////////////////////////////////////////////////////////////////////////
    inline constexpr auto begin() noexcept -> T * { return &raw[0]; }

    inline constexpr auto begin() const noexcept -> T const * {
      return &raw[0];
    }

    inline constexpr auto end() noexcept -> T * { return &raw[0] + Size; }

    inline constexpr auto end() const noexcept -> T const * {
      return &raw[0] + Size;
    }

    ////////////////////////////////////////////////////////////////////////////
    /// Data Members
    ////////////////////////////////////////////////////////////////////////////

    /**
     * Anonymous union to allow access to members using different names
     */
    union {
      std::enable_if_t<is_vec_type<T>::value, std::array<T, Size>> data;
      T raw[Size];
      struct {
        T x;
        T y;
        T z;
        T w;
      };
      struct {
        T r;
        T g;
        T b;
        T a;
      };
    };
  };

  /**
   * Compute the component wise sum of rhs and lhs.
   *
   * @tparam T The component type of the rhs and lhs
   * @tparam N The number of components in rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the component wise sum of lhs and rhs
   */
  template <typename T, std::size_t N>
  inline constexpr auto operator+(Vector<T, N> lhs,
                                  Vector<T, N> const &rhs) noexcept {
    return lhs += rhs;
  }

  /**
   * Compute the component wise difference of rhs and lhs.
   *
   * @tparam T The component type of the rhs and lhs
   * @tparam N The number of components in rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the component wise difference of lhs and rhs
   */
  template <typename T, std::size_t N>
  inline constexpr auto operator-(Vector<T, N> lhs,
                                  Vector<T, N> const &rhs) noexcept {
    return lhs -= rhs;
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
      Vector<T, N> const &v) noexcept->Vector<T, N> {
    return detail::vector::operatorUnaryMinus(v, Indices());
  }

  /**
   * Compute the component wise product of rhs and lhs.
   *
   * @tparam T The component type of the rhs and lhs
   * @tparam N The number of components in rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the product of lhs and each component of rhs
   */
  template <typename T, std::size_t N>
  inline constexpr auto operator*(T const lhs,
                                  Vector<T, N> rhs) noexcept->Vector<T, N> {
    return rhs *= lhs;
  }

  /**
   * Compute the component wise product of rhs and lhs.
   *
   * @tparam T The component type of the rhs and lhs
   * @tparam N The number of components of the lhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the product of lhs and each component of rhs
   */
  template <typename T, std::size_t N>
  inline constexpr auto operator*(Vector<T, N> lhs,
                                  T const rhs) noexcept->Vector<T, N> {
    return lhs *= rhs;
  }

  /**
   * Compute the component wise quotients of rhs and lhs.
   *
   * @tparam T The component type of the rhs and lhs3
   * @tparam N The number of components in rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the quotients of lhs and each component of rhs
   */
  template <typename T, std::size_t N,
            typename Indices = std::make_index_sequence<N>>
  inline constexpr auto operator/(
      T const lhs, Vector<T, N> const &rhs) noexcept->Vector<T, N> {
    return detail::vector::operatorDivision(lhs, rhs, Indices());
  }

  /**
   * Compute the component wise quotients of rhs and lhs.
   *
   * @tparam T The component type of the rhs and lhs
   * @tparam N The number of components of the lhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return the quotients of lhs and each component of rhs
   */
  template <typename T, std::size_t N>
  inline constexpr auto operator/(Vector<T, N> lhs,
                                  T const rhs) noexcept->Vector<T, N> {
    return lhs /= rhs;
  }

  /**
   * Determines if two Vectors are equal.
   *
   * @tparam T The component type of the lhs and rhs
   * @tparam N The number of components of both lhs and rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return true if lhs and rhs are equal
   */
  template <typename T, std::size_t N>
  inline auto operator==(Vector<T, N> const &lhs,
                         Vector<T, N> const &rhs) noexcept->bool {
    return detail::equal(std::begin(lhs), std::end(lhs), std::begin(rhs));
  }

  /**
   * Determines the inequality of if two Vectors.
   *
   * @tparam T The component type of the lhs and rhs
   * @tparam N The number of components of both lhs and rhs
   *
   * @param lhs the left-hand operand
   * @param rhs the right-hand operand
   * @return true if lhs and rhs are not equal
   */
  template <typename T, std::size_t N>
  inline constexpr auto operator!=(Vector<T, N> const &lhs,
                                   Vector<T, N> const &rhs) noexcept->bool {
    return !(lhs == rhs);
  }

  /**
   * Computes the dot product of lhs and rhs.
   *
   * @tparam T The type of the components of lhs
   * @tparam N The number of component of vec
   *
   * @param lhs A Vector
   * @param rhs A Vector
   *
   * @return The dot product of lhs and rhs
   */
  template <typename T, std::size_t N>
  inline constexpr auto dot(Vector<T, N> const &lhs,
                            Vector<T, N> const &rhs) noexcept->T {
    return detail::inner_product(lhs.begin(), lhs.end(), rhs.begin(), T(0));
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
    return sqrt(length_squared(vec));
  }

  /**
   * Computes the inverted length of vec.
   *
   * @tparam T The type of the components of vec
   * @tparam N The number of component of vec
   * @param vec A Vector
   *
   * @return The length of vec.
   */
  template <typename T, std::size_t N>
  inline auto length_inverted(Vector<T, N> const &vec) noexcept->T {
    return T{1} / length(vec);
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
  inline constexpr auto length_squared(Vector<T, N> const &vec) noexcept->T {
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
  inline auto is_zero_length(Vector<T, S> const &vec)->bool {
    T epsilon = std::numeric_limits<T>::epsilon();
    return std::abs(length_squared(vec)) < (epsilon * epsilon);
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
    return vec *= length_inverted(vec);
  }

  /**
   * Computes if the lhs and rhs are nearlyEqual within a tolerance of epsilon.
   *
   * @tparam T The type of the components of vec
   * @tparam N The number of component of vec
   *
   * @param lhs A Vector.
   * @param rhs A
   */
  template <typename T, std::size_t N>
  auto nearly_equal(Vector<T, N> const &lhs, Vector<T, N> const &rhs,
                   T const epsilon = std::numeric_limits<T>::epsilon())
      ->bool {
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), [epsilon](T r, T l) {
      using std::abs;
      return static_cast<T>(abs(l - r)) <= epsilon;
    });
  }

} // namespace cagey::math
