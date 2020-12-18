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

#include "./detail/Vector.hh"

namespace cagey::math
{

  /**
   * An '4' Dimensional Vector.
   */
  template <typename T>
  class Vector<T, 4>
  {
  public:
    /// The underlying data type
    using ValueType = T;

    /// The Vector type
    using Type = T;

    /// The number of elements in this Point
    const static std::size_t Size = 4;

    ////////////////////////////////////////////////////////////////////////////
    /// Static Member Functions
    ////////////////////////////////////////////////////////////////////////////

    static constexpr auto zero() noexcept -> Vector
    {
      return {T(0), T(0), T(0), T(0)};
    }

    static constexpr auto xAxis() noexcept -> Vector
    {
      return {T(1), T(0), T(0), T(0)};
    }

    static constexpr auto yAxis() noexcept -> Vector
    {
      return {T(0), T(1), T(0), T(0)};
    }

    static constexpr auto zAxis() noexcept -> Vector
    {
      return {T(0), T(0), T(1), T(0)};
    }

    static constexpr auto wAxis() noexcept -> Vector
    {
      return {T(0), T(0), T(0), T(1)};
    }

    ////////////////////////////////////////////////////////////////////////////
    /// Implicit Constructors
    ////////////////////////////////////////////////////////////////////////////

    constexpr Vector() noexcept = default;

    constexpr Vector(Vector const &v) noexcept = default;

    ////////////////////////////////////////////////////////////////////////////
    /// Explicit onstructors
    ////////////////////////////////////////////////////////////////////////////

    explicit constexpr Vector(T const v) noexcept : raw{v, v, v} {}

    constexpr Vector(T const x, T const y, T const z, T const w) noexcept
        : raw{x, y, z, w} {}

    ////////////////////////////////////////////////////////////////////////////
    /// Explicit Conversion Constructors
    ////////////////////////////////////////////////////////////////////////////

    constexpr Vector(Vector3<T> const &v, T const w) noexcept
        : raw{v[0], v[1], v[2], w} {}

    template <typename U>
    explicit constexpr Vector(Vector<U, Size> const &v) noexcept
        : raw{static_cast<T>(v.raw[0]),
              static_cast<T>(v.raw[1]),
              static_cast<T>(v.raw[2]),
              static_cast<T>(v.raw[3])} {}

    template <std::size_t VN, typename = std::enable_if_t<(VN > 4)>>
    explicit constexpr Vector(Vector<T, VN> const &v) noexcept
        : raw{v.raw[0], v.raw[1], v.raw[2]} {}

    ////////////////////////////////////////////////////////////////////////////
    /// Component Access
    ////////////////////////////////////////////////////////////////////////////

    constexpr auto operator[](std::size_t i) noexcept -> T &
    {
      assert(i >= 0 && i < Size);
      return raw[i];
    }

    constexpr auto operator[](std::size_t i) const noexcept -> T const &
    {
      assert(i >= 0 && i < Size);
      return raw[i];
    }

    ////////////////////////////////////////////////////////////////////////////
    /// Operators
    ////////////////////////////////////////////////////////////////////////////

    template <typename U>
    constexpr auto operator+=(Vector<U, Size> const &v) noexcept -> Vector &
    {
      raw[0] += static_cast<T>(v.raw[0]);
      raw[1] += static_cast<T>(v.raw[1]);
      raw[2] += static_cast<T>(v.raw[2]);
      raw[3] += static_cast<T>(v.raw[3]);
      return *this;
    }

    template <typename U>
    constexpr auto operator+=(U const &scalar) noexcept -> Vector &
    {
      for (auto &&r : raw)
      {
        r += static_cast<T>(scalar);
      }
      return *this;
    }

    template <typename U>
    constexpr auto operator-=(Vector<U, Size> const &v) noexcept -> Vector &
    {
      raw[0] -= static_cast<T>(v.raw[0]);
      raw[1] -= static_cast<T>(v.raw[1]);
      raw[2] -= static_cast<T>(v.raw[2]);
      raw[3] -= static_cast<T>(v.raw[3]);
      return *this;
    }

    template <typename U>
    constexpr auto operator-=(U const &scalar) noexcept -> Vector &
    {
      for (auto &&r : raw)
      {
        r -= static_cast<T>(scalar);
      }
      return *this;
    }

    template <typename U>
    constexpr auto operator*=(U const v) noexcept -> Vector &
    {
      for (auto &&r : raw)
      {
        r *= static_cast<T>(v);
      }
      return *this;
    }

    template <typename U>
    constexpr auto operator*=(Vector<U, Size> const &v) noexcept -> Vector &
    {
      raw[0] *= static_cast<T>(v.raw[0]);
      raw[1] *= static_cast<T>(v.raw[1]);
      raw[2] *= static_cast<T>(v.raw[2]);
      raw[3] *= static_cast<T>(v.raw[3]);
      return *this;
    }

    template <typename U>
    constexpr auto operator/=(U const v) noexcept -> Vector &
    {
      for (auto &&r : raw)
      {
        r /= static_cast<T>(v);
      }
      return *this;
    }

    template <typename U>
    constexpr auto operator/=(Vector<U, Size> const &v) noexcept -> Vector &
    {
      raw[0] /= static_cast<T>(v.raw[0]);
      raw[1] /= static_cast<T>(v.raw[1]);
      raw[2] /= static_cast<T>(v.raw[2]);
      raw[3] /= static_cast<T>(v.raw[3]);
      return *this;
    }

    constexpr auto operator++() noexcept -> Vector &
    {
      ++raw[0];
      ++raw[1];
      ++raw[2];
      ++raw[3];
      return *this;
    }

    constexpr auto operator--() noexcept -> Vector &
    {
      --raw[0];
      --raw[1];
      --raw[2];
      --raw[3];
      return *this;
    }

    constexpr auto operator++(int) noexcept -> Vector &
    {
      Vector res = Vector(*this)++ * this;
      return *res;
    }

    constexpr auto operator--(int) noexcept -> Vector &
    {
      Vector res = Vector(*this)-- * this;
      return *res;
    }

    ////////////////////////////////////////////////////////////////////////////
    /// Member Functions
    ////////////////////////////////////////////////////////////////////////////

    inline constexpr Vector2<T> xy() const noexcept
    {
      return Vector2<T>{x, y};
    }

    inline constexpr Vector3<T> xyz() const noexcept
    {
      return Vector3<T>{x, y, z};
    }

    inline constexpr Vector2<T> rg() const noexcept
    {
      return xy();
    }

    inline constexpr Vector3<T> rgb() const noexcept
    {
      return xyz();
    }

    ////////////////////////////////////////////////////////////////////////////
    /// Data Members
    ////////////////////////////////////////////////////////////////////////////

    /**
     * Anonymous union to allow access to members using different names
     */
    union
    {
      std::enable_if_t<is_vec_type<T>::value, std::array<T, Size>> data;
      T raw[Size];
      struct
      {
        T x;
        T y;
        T z;
        T w;
      };
      struct
      {
        T r;
        T g;
        T b;
        T a;
      };
    };
  };

} //namespace cagey::math