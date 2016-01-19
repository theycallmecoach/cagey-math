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

namespace cagey::math::detail::vector {
  template <typename T, std::size_t N, std::size_t... I>
  inline constexpr auto operatorUnaryMinus(const Vector<T, N> &v,
                                           std::index_sequence<I...>)noexcept
      ->Vector<decltype(-std::declval<T>()), N> {
    return {-v[I]...};
  }
}

// namespace cagey::math::detail {
//
//   template <typename T, typename U, std::size_t N, std::size_t... I>
//   inline constexpr auto additionOperatorScalarVector(
//       T const lhs, Vector<U, N> const &rhs,
//       std::index_sequence<I...>)noexcept
//       ->std::enable_if_t<
//           is_vec_type<T>::value,
//           Vector<decltype(std::declval<T>() + std::declval<U>()), N>> {
//     return {lhs + rhs[I]...};
//   }
//
//   template <typename T, typename U, std::size_t N, std::size_t... I>
//   inline constexpr auto additionOperatorVectorScalar(
//       Vector<U, N> const &lhs, T const &rhs,
//       std::index_sequence<I...>)noexcept
//       ->std::enable_if_t<
//           is_vec_type<T>::value,
//           Vector<decltype(std::declval<T>() + std::declval<U>()), N>> {
//     return {lhs[I] + rhs...};
//   }
//
//   template <typename T, typename U, std::size_t N, std::size_t... I>
//   inline constexpr auto additionOperatorVector(
//       Vector<T, N> const &lhs, Vector<U, N> const &rhs,
//       std::index_sequence<I...>)noexcept
//       ->Vector<decltype(std::declval<T>() + std::declval<U>()), 2> {
//     return {lhs[I] + rhs[I]...};
//   }
//
//   template <typename T, typename U, std::size_t N, std::size_t... I>
//   inline constexpr auto subtractionOperatorScalarVector(
//       T const lhs, Vector<U, N> const &rhs,
//       std::index_sequence<I...>)noexcept
//       ->std::enable_if_t<
//           is_vec_type<T>::value,
//           Vector<decltype(std::declval<T>() - std::declval<U>()), N>> {
//     return {lhs - rhs[I]...};
//   }
//
//   template <typename T, typename U, std::size_t N, std::size_t... I>
//   inline constexpr auto subtractionOperatorVectorScalar(
//       Vector<U, N> const &lhs, T const &rhs,
//       std::index_sequence<I...>)noexcept
//       ->std::enable_if_t<
//           is_vec_type<T>::value,
//           Vector<decltype(std::declval<T>() - std::declval<U>()), N>> {
//     return {lhs[I] - rhs...};
//   }
//
//   template <typename T, typename U, std::size_t N, std::size_t... I>
//   inline constexpr auto subtractionOperatorVector(
//       Vector<T, N> const &lhs, Vector<U, N> const &rhs,
//       std::index_sequence<I...>)noexcept
//       ->Vector<decltype(std::declval<T>() - std::declval<U>()), 2> {
//     return {lhs[I] - rhs[I]...};
//   }
//
//   template <typename T, std::size_t N, std::size_t... I>
//   inline constexpr auto unaryMinusOperatorVector(
//       const Vector<T, N> &v, std::index_sequence<I...>)noexcept
//       ->Vector<decltype(-std::declval<T>()), 2> {
//     return {-v[I]...};
//   }
//
//   template <typename T, typename U, std::size_t N, std::size_t... I>
//   inline constexpr auto multiplicationOperatorScalarVector(
//       T const lhs, Vector<U, N> const &rhs,
//       std::index_sequence<I...>)noexcept
//       ->std::enable_if_t<
//           is_vec_type<T>::value,
//           Vector<decltype(std::declval<T>() * std::declval<U>()), N>> {
//     return {lhs * rhs[I]...};
//   }
//
//   template <typename T, typename U, std::size_t N, std::size_t... I>
//   inline constexpr auto multiplicationOperatorVectorScalar(
//       Vector<U, N> const &lhs, T const &rhs,
//       std::index_sequence<I...>)noexcept
//       ->std::enable_if_t<
//           is_vec_type<T>::value,
//           Vector<decltype(std::declval<T>() * std::declval<U>()), N>> {
//     return {lhs[I] * rhs...};
//   }
//
//   template <typename T, typename U, std::size_t N, std::size_t... I>
//   inline constexpr auto multiplicationOperatorVector(
//       Vector<T, N> const &lhs, Vector<U, N> const &rhs,
//       std::index_sequence<I...>)noexcept
//       ->Vector<decltype(std::declval<T>() * std::declval<U>()), 2> {
//     return {lhs[I] * rhs[I]...};
//   }
//
//   template <typename T, typename U, std::size_t N, std::size_t... I>
//   inline constexpr auto divisionOperatorScalarVector(
//       T const lhs, Vector<U, N> const &rhs,
//       std::index_sequence<I...>)noexcept
//       ->std::enable_if_t<
//           is_vec_type<T>::value,
//           Vector<decltype(std::declval<T>() / std::declval<U>()), N>> {
//     return {lhs / rhs[I]...};
//   }
//
//   template <typename T, typename U, std::size_t N, std::size_t... I>
//   inline constexpr auto divisionOperatorVectorScalar(
//       Vector<U, N> const &lhs, T const &rhs,
//       std::index_sequence<I...>)noexcept
//       ->std::enable_if_t<
//           is_vec_type<T>::value,
//           Vector<decltype(std::declval<T>() / std::declval<U>()), N>> {
//     return {lhs[I] / rhs...};
//   }
//
//   template <typename T, typename U, std::size_t N, std::size_t... I>
//   inline constexpr auto divisionOperatorVector(
//       Vector<T, N> const &lhs, Vector<U, N> const &rhs,
//       std::index_sequence<I...>)noexcept
//       ->Vector<decltype(std::declval<T>() / std::declval<U>()), 2> {
//     return {lhs[I] / rhs[I]...};
//   }
//
//   template <typename T, typename U, std::size_t N>
//   inline constexpr auto pairCompare(Vector<T, N> const &lhs,
//                                     Vector<U, N> const &rhs, std::size_t i) {
//     return lhs[i] == rhs[i];
//   }
//
//   template <typename T, typename U, std::size_t N, std::size_t... I>
//   inline constexpr auto equalityOperatorVector(
//       Vector<T, N> const &lhs, Vector<U, N> const &rhs,
//       std::index_sequence<I...>)noexcept->bool {
//     return true && pairCompare(lhs, rhs, I...);
//   }
// } // namespace cagey::math::detail
