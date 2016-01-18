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

#include <cagey-math/detail/BasePoint.hh>
#include <cagey-math/MathFwd.hh>

namespace cagey::math {

  /**
  * Vector Class, Has specializations for lengths of 2, 3, 4
  */
  template <typename T, std::size_t N>
  class Vector : public BasePoint<Vector, T, N> {
  public:
    /** @cond doxygen has some issues with static assert */
    static_assert(N != 0, "Vector cannot have zero elements");
    static_assert(std::is_arithmetic<T>::value,
                  "Underlying type must be a number");
    /** @endcond */

    /// The underlying type of this Vector
    using Type = T;

    /// The number of elements in this Vector
    const static std::size_t Size = N;

    /**
    * Construct a Vector with all elements initialized to Zero
    */
    constexpr Vector() noexcept = default;

    /**
    * Construct a Vector with all elements initialized to the given value
    *
    * @param v the value to assign to all elements of this Vector
    */
    explicit Vector(T const v) noexcept : BasePoint<math::Vector, T, N>{v} {};

    /**
    * Construct a Vector using the given pointer.  Note: It assumed the given
    * pointer contains N values;
    */
    constexpr explicit Vector(T *const v) noexcept
        : BasePoint<math::Vector, T, N>{v} {};

    /**
    * Construct a Vector using the values from the given std::array
    *
    * @param vals vals[0] is assigned to data[0] etc. etc.
    */
    constexpr explicit Vector(std::array<T, Size> const &vals)
        : BasePoint<math::Vector, T, N>{vals} {};

    /**
    * Conversion Copy Constructor.  Construct a Vector using a Vector with a
    * different
    * underlying type.  Only simple type conversion is performed
    */
    template <typename U>
    constexpr explicit Vector(Vector<U, Size> const &other)
        : BasePoint<math::Vector, U, N>{other} {};

  public:
    /// Array containing Vector elements
    std::array<T, N> data;
  };

  /**
  * Vector two element specialization
  */
  template <typename T> class Vector<T, 2> : public BasePoint<Vector, T, 2> {
    /** @cond doxygen has issues with static_assert */
    static_assert(std::is_arithmetic<T>::value,
                  "Underlying type must be a number");
    /** @endcond */
  public:
    /// The number of elements in this BasePoint
    const static std::size_t Size = 2;

    /**
    * Construct a Vector with all elements initialized to Zero
    */
    constexpr Vector() noexcept = default;

    /**
    * Construct a Vector with all elements initialized to the given value
    *
    * @param v the value to assign to all elements of this Vector
    */
    constexpr explicit Vector(T const v) noexcept
        : BasePoint<math::Vector, T, Size>{v} {};

    /**
    * Construct a Vector with the given elements a and b are assigned to x and y
    * respectively
    *
    * @param a value to assign to x
    * @param b value to assign to y
    */
    constexpr Vector(T const a, T const b) noexcept
        : BasePoint<math::Vector, T, Size>{a, b} {};

    /**
    * Construct a Vector using the given pointer.  Note: It assumed the given
    * pointer contains two values;
    *
    * @param v point to an array of two values
    */
    explicit Vector(T *const v) noexcept
        : BasePoint<math::Vector, T, Size>{v} {};

    /**
    * Construct a Vector using the values from the given std::array
    *
    * @param vals vals[0] is assigned to data[0] etc. etc.
    */
    constexpr explicit Vector(std::array<T, Size> const &vals)
        : BasePoint<math::Vector, T, Size>{vals} {};

    /**
    * Conversion Copy Constructor.  Construct a Vector using a Vector with a
    * different
    * underlying type.  Only simple type conversion is performed
    */
    template <typename U>
    constexpr explicit Vector(Vector<U, Size> const &other)
        : BasePoint<math::Vector, T, Size>{other} {};
  };

  /**
  * Vector three element specialization
  */
  template <typename T> class Vector<T, 3> : public BasePoint<Vector, T, 3> {
    /** @cond doxygen has issues with static_assert */
    static_assert(std::is_arithmetic<T>::value,
                  "Underlying type must be a number");
    /** @endcond */
  public:
    /// The number of elements in this BasePoint
    const static std::size_t Size = 3;

    /**
    * Construct a Vector with all elements initialized to Zero
    */
    constexpr Vector() noexcept = default;

    /**
    * Construct a Vector with all elements initialized to the given value
    *
    * @param v the value to assign to all elements of this Vector
    */
    constexpr explicit Vector(T const v) noexcept
        : BasePoint<math::Vector, T, Size>{v} {};

    /**
    * Construct a Vector with the given elements a, b and c are assigned to x, y
    * and z respectively
    *
    * @param a value to assign to x
    * @param b value to assign to y
    * @param c value to assign to z
    */
    constexpr Vector(T const a, T const b, T const c) noexcept
        : BasePoint<math::Vector, T, Size>{a, b, c} {};

    /**
    * Construct a Vector using the given pointer.  Note: It assumed the given
    * pointer contains three values;
    *
    * @param v point to an array of three values
    */
    explicit Vector(T *const v) noexcept
        : BasePoint<math::Vector, T, Size>{v} {};

    /**
    * Construct a Vector using the values from the given std::array
    *
    * @param vals vals[0] is assigned to data[0] etc. etc.
    */
    constexpr explicit Vector(std::array<T, Size> const &vals)
        : BasePoint<math::Vector, T, Size>{vals} {};

    /**
    * Conversion Copy Constructor.  Construct a Vector using a Vector with a
    * different
    * underlying type.  Only simple type conversion is performed
    */
    template <typename U>
    constexpr explicit Vector(Vector<U, Size> const &other)
        : BasePoint<math::Vector, T, Size>{other} {};
  };

  /**
  * Vector three element specialization
  */
  template <typename T> class Vector<T, 4> : public BasePoint<Vector, T, 4> {
    /** @cond doxygen has issues with static_assert */
    static_assert(std::is_arithmetic<T>::value,
                  "Underlying type must be a number");
    /** @endcond */
  public:
    /// The number of elements in this BasePoint
    const static std::size_t Size = 4;

    /**
    * Construct a Vector with all elements initialized to Zero
    */
    constexpr Vector() noexcept = default;

    /**
    * Construct a Vector with all elements initialized to the given value
    *
    * @param v the value to assign to all elements of this Vector
    */
    constexpr explicit Vector(T const v) noexcept
        : BasePoint<math::Vector, T, Size>{v} {};

    /**
    * Construct a Vector with the given elements a,b,c,d are assigned to x,y,z
    * and w respectively
    *
    * @param a value to assign to x
    * @param b value to assign to y
    * @param c value to assign to z
    * @param d value to assign to w
    */
    constexpr Vector(T const a, T const b, T const c, T const d) noexcept
        : BasePoint<math::Vector, T, Size>{a, b, c, d} {};

    /**
    * Construct a Vector using the given pointer.  Note: It assumed the given
    * pointer contains four values;
    *
    * @param v pointer to an array of four values
    */
    explicit Vector(T *const v) noexcept
        : BasePoint<math::Vector, T, Size>{v} {};

    /**
    * Construct a Vector using the values from the given std::array
    *
    * @param vals vals[0] is assigned to data[0] etc. etc.
    */
    constexpr explicit Vector(std::array<T, Size> const &vals)
        : BasePoint<math::Vector, T, Size>{vals} {};

    /**
    * Conversion Copy Constructor.  Construct a Vector using a Vector with a
    * different
    * underlying type.  Only simple type conversion is performed
    */
    template <typename U>
    explicit Vector(Vector<U, Size> const &other)
        : BasePoint<math::Vector, T, Size>{other} {};
  };

  // // Some short forms
  // template <typename T> using Vec2 = Vector<T, 2>;
  // template <typename T> using Vec3 = Vector<T, 3>;
  // template <typename T> using Vec4 = Vector<T, 4>;
  //
  // using Vec2u = Vector<unsigned, 2>;
  // using Vec2i = Vector<int, 2>;
  // using Vec2f = Vector<float, 2>;
  // using Vec2d = Vector<double, 2>;
  //
  // using Vec3u = Vector<unsigned, 3>;
  // using Vec3i = Vector<int, 3>;
  // using Vec3f = Vector<float, 3>;
  // using Vec3d = Vector<double, 3>;
  //
  // using Vec4u = Vector<unsigned, 4>;
  // using Vec4i = Vector<int, 4>;
  // using Vec4f = Vector<float, 4>;
  // using Vec4d = Vector<double, 4>;

  /**
   * Return the length(magnitude) of the vector
   *
   * Note: involves a square root
   */
  template <typename T, std::size_t S> auto length(Vector<T, S> const &rhs)->T {
    using std::sqrt;
    return sqrt(dot(rhs, rhs));
  }

  /**
   * Perform a fuzzy equals between the given Vectors
   *
   * @param lhs a Vector
   * @param rhs a Vector
   */
  template <typename T, std::size_t S>
  auto equals(Vector<T, S> const &lhs, Vector<T, S> const &rhs)->bool {
    return std::equal(lhs.begin(), rhs.begin(), rhs.begin(),
                      [](T r, T l) { return math::equals(l, r); });
  }

  // template<typename T, std::size_t S>
  // auto equals(Vector<T, S> const & lhs, Vector<T, S> const & rhs, T const
  // epsilon = std::numeric_limits<T>::epsilon()) -> bool {
  //  return std::equal(lhs.begin(), lhs.end(), rhs.begin(),
  //      [epsilon] (T r, T l) { using std::abs; return static_cast<T>(abs(l -
  //      r)) <= epsilon; });
  //}

  /**
   * Return the dot product between the given Vectors
   *
   * @param lhs a vector
   * @param rhs a vector
   */
  template <typename T, std::size_t S>
  auto dot(Vector<T, S> const &lhs, Vector<T, S> const &rhs)->T {
    return std::inner_product(lhs.begin(), rhs.begin(), rhs.begin(), T{0});
  }

  /**
   * Return the absolute value of the dot product between the given Vectors
   *
   * @param lhs a vector
   * @param rhs a vector
   */
  template <typename T, std::size_t S>
  auto dotAbsolute(Vector<T, S> const &lhs, Vector<T, S> const &rhs)->T {
    return std::inner_product(lhs.begin(), lhs.end(), lhs.begin(), T{0},
                              std::plus<T>(),
                              [](T l, T r) -> T { return std::abs(l * r); });
  }

  /**
   * Return the cross product of the given Vectors. Specialized for Vec2
   *
   * @param lhs a vector
   * @param rhs a vector
   * @return the value representing the cross product of the given Vectors
   */
  template <typename T> auto cross(Vec2<T> const rhs, Vec2<T> const &lhs)->T {
    return lhs.x * rhs.y - lhs.y * rhs.x;
  }

  /**
   * Return the cross product of the given Vectors. Specialized for Vec3
   *
   * @param lhs a vector
   * @param rhs a vector
   * @return a vector which is the cross product of the given Vectors
   */
  template <typename T>
  auto cross(Vec3<T> const rhs, Vec3<T> const &lhs)->Vector<T, 3> {
    // clang-format off
    return Vec3<T>{lhs.y * rhs.z - lhs.z * rhs.y,
                   lhs.z * rhs.x - lhs.x * rhs.z,
                   lhs.x * rhs.y - lhs.y * rhs.x};
    // clang-format on
  }

  /**
   * Normalize the given Vector or make a unit ector.
   * If the length is zero returns the given Vector unmodified
   *
   * @param vec the vector to normalize
   * @return a normalized copy of the given vector
   */
  template <typename T, std::size_t S>
  auto normalize(Vector<T, S> const vec)->Vector<T, S> {
    T len = length(vec);
    if (len > 0) {
      vec *= (T{1} / len);
    } else {
      // bad things happen... zero length vector;
    }
    return vec;
  }

  /**
   * Returns the length of the given vector squared.  use this
   * when you want to avoid a sqrt
   *
   * @param vec the Vector to determine the length
   * @return the squared length of the given Vector
   */
  template <typename T, std::size_t S>
  inline auto lengthSquared(Vector<T, S> const &vec)->T {
    return cagey::math::dot(vec, vec);
  }

  /**
  * Returns true if the given Vector has zero length.
  *
  * @param vec the Vector to check for zero length
  * @return true if the given Vector is zero length
  */
  template <typename T, std::size_t S>
  inline auto isZeroLength(Vector<T, S> const &vec)->bool {
    T epsilon = std::numeric_limits<T>::epsilon();
    return std::abs(lengthSquared(vec)) < (epsilon * epsilon);
  }

  /**
   * Returns the distance between the given vectors.  Note this method
   * involves a square root
   *
   * @param lhs a Vector
   * @param rhs a Vector
   * @return the distance between the given Vectors
   */
  template <typename T, std::size_t S>
  inline auto distance(Vector<T, S> const &lhs, Vector<T, S> const &rhs)->T {
    return length(lhs - rhs);
  }

  /**
   * Returns the distance between the given vectors squared.
   *
   * @param lhs a Vector
   * @param rhs a Vector
   * @return the distance between the given Vectors, squared.
   */
  template <typename T, std::size_t S>
  inline auto distanceSquared(Vector<T, S> const &lhs, Vector<T, S> const &rhs)
      ->T {
    return lengthSquared(lhs - rhs);
  }

} // namespace cagey::math

//#pragma clang diagnostic pop
