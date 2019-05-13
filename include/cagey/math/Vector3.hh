// ////////////////////////////////////////////////////////////////////////////////
// //
// // cagey-math - C++-17 Vector Math Library
// // Copyright (c) 2019 Kyle Girard <theycallmecoach@gmail.com>
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
// ////////////////////////////////////////////////////////////////////////////////
// #pragma once

// #include <cmath>
// #include <cagey-math/MathFwd.hh>
// #include <cagey-math/detail/MetaUtil.hh>
// #include <cagey-math/detail/vec_type.hh>
// #include <cagey-math/detail/ConstExprUtil.hh>
// #include <cmath>

// namespace cagey::math {

//  /**
//    * An '3' Dimensional Vector.
//    */
//   template <typename T> class Vector<T, 3> {
//   public:
//     /// The underlying data type
//     using Type = T;

//     /// The number of elements in this Point
//     const static std::size_t Size = 3;

//     ////////////////////////////////////////////////////////////////////////////
//     /// Static Member Functions
//     ////////////////////////////////////////////////////////////////////////////

//     static constexpr auto zero() noexcept -> Vector {
//       return {T(0), T(0), T(0)};
//     }

//     static constexpr auto x_axis() noexcept -> Vector {
//       return {T(1), T(0), T(0)};
//     }

//     static constexpr auto y_axis() noexcept -> Vector {
//       return {T(0), T(1), T(0)};
//     }

//     static constexpr auto zAxis() noexcept -> Vector {
//       return {T(0), T(0), T(1)};
//     }

//     ////////////////////////////////////////////////////////////////////////////
//     /// Constructors
//     ////////////////////////////////////////////////////////////////////////////

//     inline constexpr Vector() noexcept = default;

//     inline explicit constexpr Vector(T const v) noexcept : raw{v, v, v} {}

//     inline constexpr Vector(T const x, T const y, T const z) noexcept
//         : raw{x, y, z} {};

//     inline constexpr Vector(Vec2<T> const &v, T const z) noexcept
//         : raw{v[0], v[1], z} {};

//     template <typename U, std::size_t S>
//     inline explicit constexpr Vector(Vector<U, S> const &v) noexcept
//         : raw{T(v.raw[0]), T(v.raw[1]), T(v.raw[2])} {}


//     template <std::size_t VN, typename = std::enable_if_t<(VN > 3)>>
//     inline explicit constexpr Vector(Vector<T, VN> const & v) noexcept
//         : raw{v.raw[0], v.raw[1], v.raw[2]} {}


//     ////////////////////////////////////////////////////////////////////////////
//     /// Operators
//     ////////////////////////////////////////////////////////////////////////////

//     inline constexpr auto operator[](std::size_t i) noexcept -> T & {
//       return raw[i];
//     }

//     inline constexpr auto operator[](std::size_t i) const noexcept
//         -> T const & {
//       return raw[i];
//     }

//     inline constexpr auto operator+=(Vector const &v) noexcept -> Vector & {
//       raw[0] += v.raw[0];
//       raw[1] += v.raw[1];
//       raw[2] += v.raw[2];
//       return *this;
//     }

//     inline constexpr auto operator-=(Vector const &v) noexcept -> Vector & {
//       raw[0] -= v.raw[0];
//       raw[1] -= v.raw[1];
//       raw[2] -= v.raw[2];
//       return *this;
//     }

//     inline constexpr auto operator*=(T const v) noexcept -> Vector & {
//       for (auto&& r : raw) {
//         r *= v;
//       }
//       return *this;
//     }

//     inline constexpr auto operator/=(T const v) noexcept -> Vector & {
//       for (auto&& r : raw) {
//         r /= v;
//       }
//       return *this;
//     }

//     ////////////////////////////////////////////////////////////////////////////
//     /// Member Functions
//     ////////////////////////////////////////////////////////////////////////////
 
//     inline constexpr Vec2<T> xy() const noexcept {
//       return Vec2<T>{x, y};
//     }

//     inline constexpr Vec3<T> xyz() const noexcept {
//       return Vec3<T>{x, y, z};
//     }

//     inline constexpr Vec2<T> rg() const noexcept {
//       return xy();
//     }

//     inline constexpr Vec3<T> rgb() const noexcept {
//       return xyz();
//     }

//     ////////////////////////////////////////////////////////////////////////////
//     /// Data Members
//     ////////////////////////////////////////////////////////////////////////////

//     /**
//      * Anonymous union to allow access to members using different names
//      */
//     union {
//       std::enable_if_t<is_vec_type<T>::value, std::array<T, Size>> data;
//       T raw[Size];
//       struct {
//         T x;
//         T y;
//         T z;
//       };
//       struct {
//         T r;
//         T g;
//         T b;
//       };
//     };
//   };

// } //namespace cagey::math