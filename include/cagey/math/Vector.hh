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
#include <algorithm>
#include <type_traits>
#include <cagey/math/MathFwd.hh>
#include <cagey/math/detail/TypeTraits.hh>
#include <cagey/math/detail/MetaUtil.hh>
#include <cagey/math/detail/ConstExprUtil.hh>

namespace cagey::math {

  /**
   * An 'N' - Dimensional Vector.
   */
  template <typename T, std::size_t N> class Vector {
    static_assert(N >= 2 , "Vector must have at least two elements");

  public:
    /// The underlying data type
    using Type = T;

    /// The number of elements in this Vector
    enum : std::size_t {
      Size = N
    };

    ////////////////////////////////////////////////////////////////////////////
    /// Static Member Functions
    ////////////////////////////////////////////////////////////////////////////

    /**
     * Returns a Vector with each component set to 0.
     *
     * @return A Vector with each component set to 0
     */
    inline static constexpr auto Zero() noexcept -> Vector {
      return Vector<T, N>{T(0.0)};
    }

    /**
     * Returns a Vector with the first component set to 1 and all other
     * components set to 0.
     *
     * Note: Function only available when N >= 2.
     *
     * @return A Vector with the first component set to 1 and all other
     * components set to 0.
     */
    inline static constexpr auto UnitX() noexcept -> Vector {
      Vector<T, N> v = Vector<T,N>::Zero();
      v[0] = T(1);
      return v;
    }

    /**
     * Returns a Vector with the second component set to 1 and all other
     * components set to 0.
     *
     * Note: Function only available when N >= 2.
     *
     * @return A Vector with the second component set to 1 and all other
     * components set to 0.
     */
    inline static constexpr auto UnitY() noexcept -> Vector {
      Vector<T, N> v = Vector<T,N>::Zero();
      v[1] = T(1);
      return v;
    }

    /**
     * Returns a Vector with the third component set to 1 and all other
     * components set to 0.
     *
     * Note: Function only available when N >= 3.
     *
     * @return A Vector with the third component set to 1 and all other
     * components set to 0.
     */
    inline static constexpr auto UnitZ() noexcept -> Vector {
      Vector<T, N> v = Vector<T,N>::Zero();
      v[2] = T(1);
      return v;
    }

    /**
     * Returns a Vector with the forth component set to 1 and all other
     * components set to 0.
     *
     * Note: Function only available when N >= 4.
     *
     * @return A Vector with the forth component set to 1 and all other
     * components set to 0.
     */
    inline static constexpr auto UnitW() noexcept -> Vector {
      Vector<T, N> v = Vector<T,N>::Zero();
      v[3] = T(1);
      return v;
    }

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
    template <typename U, 
              typename V = typename std::enable_if<std::is_same<T, U>::value && N != 1, T>::type,
              typename Indices = std::make_index_sequence<N>>
    inline explicit constexpr Vector(U const v) noexcept
        : Vector(Indices{}, v) {}

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
    inline constexpr auto operator[](std::size_t i) noexcept -> T & {
      return raw[i];
    }

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
    inline constexpr auto operator[](std::size_t i) const noexcept -> T const & {
      return raw[i];
    }

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
    inline constexpr auto operator+=(Vector const &v) noexcept -> Vector & {
      std::transform(data.begin(), data.end(), begin(v), data.begin(), std::plus<>());
      return *this;
    }

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
    inline constexpr auto operator-=(Vector const &v) noexcept -> Vector & {
      std::transform(data.begin(), data.end(), begin(v), data.begin(), std::minus<>());
      return *this;
    }

    /**
     * Multiplies each component of this Vector by x.
     *
     * @tparam U The type of parameter x.
     *
     * @param x The value to multiply against each component of this Vector
     *
     * @return A reference to this Vector.
     */
    inline constexpr auto operator*=(T const x) noexcept -> Vector & {
      std::transform(data.begin(), data.end(), data.begin(), [x](auto& a) { return a * x;});
      return *this;
    }

    /**
     * Divides each component of this Vector by x.
     *
     * @tparam U The type of parameter x.
     *
     * @param x The value to use to divide each component of this Vector
     *
     * @return A reference to this Vector.
     */
    inline constexpr auto operator/=(T const x) noexcept -> Vector & {
      std::transform(data.begin(), data.end(), data.begin(), [x](auto& a) { return a / x;});
      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    /// Member Functions
    ////////////////////////////////////////////////////////////////////////////

    /**
     * @brief Returns a copy of this Vector's first two components
     * @return a copy of this Vector's first two components
     */
    inline constexpr Vec2<T> xy() const noexcept {
      return Vec2<T>(data[0], data[1]);
    }

    /**
     * @brief Returns a copy of this Vector's first three components
     * @return a copy of this Vector's first three components
     */
    inline constexpr Vec3<T> xyz() const noexcept{
      return Vec3<T>(data[0], data[1], data[2]);
    }

    ////////////////////////////////////////////////////////////////////////////
    /// Data Members
    ////////////////////////////////////////////////////////////////////////////

    /// Data representation
    /**
     * Anonymous union to allow access to members using different names
     */
    union {
      std::enable_if_t<detail::isVectorTypeValue<T>, std::array<T, N>> data;
      std::enable_if_t<detail::isVectorTypeValue<T>, T[N]> raw;
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

  namespace detail {
    template <typename T, std::size_t N, std::size_t... I>
    inline constexpr auto metaNegate(const Vector<T, N> &v,
                                     std::index_sequence<I...>) noexcept
      -> Vector<decltype(-std::declval<T>()), N> {
      return {-v[I]...};
    }

    template <typename T, typename U, std::size_t N, std::size_t... I>
    inline constexpr auto metaDivide(U const &lhs, Vector<T, N> const &rhs,
                                         std::index_sequence<I...>)noexcept
      -> Vector<decltype(std::declval<T>() / std::declval<U>()), N> {
      return {lhs / rhs[I]...};
    }
  }

  /**
   * Overload std::begin()
   */
  template <typename T, std::size_t N>
  inline constexpr auto begin(Vector<T, N> const & v) -> decltype(&v.raw[0]) {
    return &v.raw[0];
  }
  
  /**
   * Overload std::begin()
   */
  template <typename T, std::size_t N>
  inline constexpr auto begin(Vector<T, N> & v) -> decltype(&v.raw[0]) {
    return &v.raw[0];
  }
 
  /**
   * Overload std::end()
   */
  template <typename T, std::size_t N>
  inline constexpr auto end(Vector<T, N> const & v) -> decltype(&v.raw[0]) {
    return &v.raw[0] + Vector<T, N>::Size;
  }
  
  /**
   * Overload std::end()
   */
  template <typename T, std::size_t N>
  inline constexpr auto end(Vector<T, N> & v) -> decltype(&v.raw[0]) {
    return &v.raw[0] + Vector<T, N>::Size;
  }


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
                                  Vector<T, N> const &rhs) noexcept -> Vector<T, N> {
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
                                  Vector<T, N> const &rhs) noexcept -> Vector<T, N> {
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
      Vector<T, N> const &v) noexcept -> Vector<T, N> {
    return detail::metaNegate(v, Indices());
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
                                  T const rhs) noexcept -> Vector<T, N> {
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
      T const lhs, Vector<T, N> const &rhs) noexcept -> Vector<T, N> {
    return detail::metaDivide(lhs, rhs, Indices());
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
                                  T const rhs) noexcept -> Vector<T, N> {
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
    using std::begin;
    using std::end;
    return detail::equal(begin(lhs), end(lhs), begin(rhs));
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
                            Vector<T, N> const &rhs) noexcept -> T {
    using std::begin;
    return detail::inner_product(begin(lhs), end(lhs), begin(rhs), T(0));
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
  inline auto length(Vector<T, N> const &vec) noexcept -> T {
    using std::sqrt;
    return sqrt(lengthSquared(vec));
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
  inline auto lengthInverted(Vector<T, N> const &vec) noexcept -> T {
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
  inline constexpr auto lengthSquared(Vector<T, N> const &vec) noexcept -> T {
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
  inline auto isZeroLength(Vector<T, S> const &vec) -> bool {
    T epsilon = std::numeric_limits<T>::epsilon();
    using std::abs;
    return abs(lengthSquared(vec)) < (epsilon * epsilon);
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
    return vec *= lengthInverted(vec);
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
  auto fuzzyEquals(Vector<T, N> const &lhs, Vector<T, N> const &rhs,
                   T const epsilon = std::numeric_limits<T>::epsilon())
      ->bool {
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), [epsilon](T r, T l) {
      using std::abs;
      return static_cast<T>(abs(l - r)) <= epsilon;
    });
  }

} // namespace cagey::math
