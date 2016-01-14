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
#include <utility>

namespace cagey::math {

  template <typename T> struct Vector<T, 2> {
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
    };

    using Type = T;

    static constexpr std::size_t Size = 2;

    //==================================================================
    // CONSTRUCTORS
    //==================================================================

    Vector() noexcept = default;

    explicit constexpr Vector(T x) noexcept : data({{x, x}}) {}

    constexpr Vector(T x, T y) noexcept : data({{x, y}}) {}

    template <int VN, typename = std::enable_if_t<(VN > 2)>>
    explicit constexpr Vector(Vector<T, VN> const &v) noexcept
        : data({{v[0], v[1]}}) {}

    template <typename U>
    explicit constexpr Vector(Vector<U, 2> const &v) noexcept
        : data({{T(v[0]), T(v[1])}}) {}

    template <typename U> constexpr operator Vector<U, 2>() const noexcept {
      return {this->data[0], this->data[1]};
    }

    //==================================================================
    // STATIC
    //==================================================================

    static constexpr auto zero() noexcept -> Vector<T, 2> {
      return {T(0), T(0)};
    }

    static constexpr auto xAxis() noexcept -> Vector<T, 2> {
      return {T(1), T(0)};
    }

    static constexpr auto yAxis() noexcept -> Vector<T, 2> {
      return {T(0), T(1)};
    }

    //==================================================================
    // OPERATORS
    //==================================================================

    template <typename I>
    inline constexpr auto operator[](I i) const noexcept -> T const & {
      return this->data[i];
    }

    template <typename I>
    inline constexpr auto operator[](I const &i) noexcept -> T & {
      return this->data[i];
    }

    auto inline operator++() noexcept -> Vector<T, 2> & {
      ++this->data[0];
      ++this->data[1];
      return *this;
    }

    auto inline operator++(int) noexcept -> Vector<T, 2> {
      return {this->data[0]++, this->data[1]++};
    }

    auto inline operator--() noexcept -> Vector<T, 2> & {
      --this->data[0];
      --this->data[1];
      return *this;
    }

    auto inline operator--(int) noexcept -> Vector<T, 2> {
      return {this->data[0]--, this->data[1]--};
    }

    template <typename U>
    auto operator+=(U const &x) noexcept
        -> std::enable_if_t<is_vec_type<U>::value, Vector<T, 2> &> {
      this->data[0] += x;
      this->data[1] += x;
      return *this;
    }

    template <typename U>
    auto operator+=(Vector<U, 2> const &v) noexcept -> Vector<T, 2> & {
      this->data[0] += v[0];
      this->data[1] += v[1];
      return *this;
    }

    template <typename U>
    auto operator-=(U const &x) noexcept
        -> std::enable_if_t<is_vec_type<U>::value, Vector<T, 2> &> {
      this->data[0] -= x;
      this->data[1] -= x;
      return *this;
    }

    template <typename U>
    auto operator-=(Vector<U, 2> const &v) noexcept -> Vector<T, 2> & {
      this->data[0] -= v[0];
      this->data[1] -= v[1];
      return *this;
    }

    template <typename U>
    auto operator*=(U const &x) noexcept
        -> std::enable_if_t<is_vec_type<U>::value, Vector<T, 2> &> {
      this->data[0] *= x;
      this->data[1] *= x;
      return *this;
    }

    template <typename U>
    auto operator*=(Vector<U, 2> const &v) noexcept -> Vector<T, 2> & {
      this->data[0] *= v[0];
      this->data[1] *= v[1];
      return *this;
    }

    template <typename U>
    inline auto operator/=(U x) noexcept
        -> std::enable_if_t<is_vec_type<U>::value, Vector<T, 2> &> {
      this->data[0] /= x;
      this->data[1] /= x;
      return *this;
    }

    template <typename U>
    inline auto operator/=(Vector<U, 2> const &v) noexcept -> Vector<T, 2> & {
      this->data[0] /= v[0];
      this->data[1] /= v[1];
      return *this;
    }

    //==================================================================
    // MEMBMER FUNCTIONS
    //==================================================================

    auto constexpr begin() const noexcept -> const T * {
      return this->data.begin();
    }

    auto constexpr begin() noexcept -> T * { return this->data.begin(); }

    auto constexpr end() const noexcept -> const T * {
      return this->data.end();
    }

    auto constexpr end() noexcept -> T * { return this->data.end(); }
  };

  namespace detail {

  template <typename T, typename U>
  inline constexpr auto vectorAdditionOperatorVectorScalar(
      Vector<T, 2> const &lhs, U const &rhs) noexcept
      -> Vector<decltype(std::declval<T>() + std::declval<U>()), 2> {
    return {lhs[0] + rhs, lhs[1] + rhs};
  }

  template <typename T, typename U>
  inline constexpr auto vectorAdditionOperator(Vector<T, 2> const &lhs,
                                               Vector<U, 2> const &rhs) noexcept
      -> Vector<decltype(std::declval<T>() + std::declval<U>()), 2> {
    return {lhs[0] + rhs[0], lhs[1] + rhs[1]};
  }

  template <typename T, typename U>
  inline constexpr auto vectorSubtractionOperatorScalarVector(
      T const lhs, Vector<U, 2> const &rhs) noexcept
      -> Vector<decltype(std::declval<T>() - std::declval<U>()), 2> {
    return {lhs - rhs[0], lhs - rhs[1]};
  }

  template <typename T, typename U>
  inline constexpr auto vectorSubtractionOperatorVectorScalar(
      Vector<T, 2> const &lhs, U const &rhs) noexcept
      -> Vector<decltype(std::declval<T>() - std::declval<U>()), 2> {
    return {lhs[0] - rhs, lhs[1] - rhs};
  }

  template <typename T, typename U>
  inline constexpr auto vectorSubtractionOperator(
      Vector<T, 2> const &lhs, Vector<U, 2> const &rhs) noexcept
      -> Vector<decltype(std::declval<T>() - std::declval<U>()), 2> {
    return {lhs[0] - rhs[0], lhs[1] - rhs[1]};
  }

  template <typename T, typename U>
  inline constexpr auto vectorMultiplicationOperatorScalarVector(
      T const &lhs, Vector<U, 2> const &rhs) noexcept
      -> Vector<decltype(std::declval<T>() * std::declval<U>()), 2> {
    return {lhs * rhs[0], lhs * rhs[1]};
  }

  template <typename T, typename U>
  inline constexpr auto vectorMultiplicationOperatorVectorScalar(
      Vector<T, 2> const &lhs, U const &rhs) noexcept
      -> Vector<decltype(std::declval<T>() * std::declval<U>()), 2> {
    return {lhs[0] * rhs, lhs[1] * rhs};
  }

  template <typename T, typename U>
  inline constexpr auto vectorMultiplicationOperator(
      Vector<T, 2> const &lhs, Vector<U, 2> const &rhs) noexcept
      -> Vector<decltype(std::declval<T>() * std::declval<U>()), 2> {
    return {lhs[0] * rhs[0], lhs[1] * rhs[1]};
  }

  template <typename T, typename U>
  inline constexpr auto vectorDivisionOperatorScalarVector(
      T const &lhs, Vector<U, 2> const &rhs) noexcept
      -> Vector<decltype(std::declval<T>() / std::declval<U>()), 2> {
    return {lhs / rhs[0], lhs / rhs[1]};
  }

  template <typename T, typename U>
  inline constexpr auto vectorDivisionOperatorVectorScalar(
      Vector<T, 2> const &lhs, U const &rhs) noexcept
      -> Vector<decltype(std::declval<T>() / std::declval<U>()), 2> {
    return {lhs[0] / rhs, lhs[1] / rhs};
  }

  template <typename T, typename U>
  inline constexpr auto vectorDivisionOperator(Vector<T, 2> const &lhs,
                                               Vector<U, 2> const &rhs) noexcept
      -> Vector<decltype(std::declval<T>() / std::declval<U>()), 2> {
    return {lhs[0] / rhs[0], lhs[1] / rhs[1]};
  }

  template <typename T>
  inline constexpr auto vectorUnaryMinusOperator(const Vector<T, 2> &v) noexcept
      -> Vector<decltype(-std::declval<T>()), 2> {
    return {-v[0], -v[1]};
  }

  template <typename T, typename U, std::size_t N>
  inline constexpr auto vectorEqualityOperator(Vector<T, N> const &lhs,
                                               Vector<U, N> const &rhs) noexcept
      -> bool {
    return lhs[0] == rhs[0] && lhs[1] == rhs[1];
  }

  template <typename T, typename U, std::size_t N>
  inline constexpr auto dot(Vector<T, N> const &lhs,
                            Vector<U, N> const &rhs) noexcept
      -> decltype(std::declval<T>() * std::declval<U>()) {
    return lhs[0] * rhs[0] + lhs[1] * rhs[1];
  }

  } // namespace detail
} // namespace cagey::math
