//=============================================================================
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
//=============================================================================

#pragma once

#include <cstdint>
#include <type_traits>

namespace cagey::math
{

  template <typename T>
  struct is_vec_type : public std::integral_constant<bool, false>
  {
  };

  template <>
  struct is_vec_type<float> : public std::integral_constant<bool, true>
  {
  };

  template <>
  struct is_vec_type<double> : public std::integral_constant<bool, true>
  {
  };

  template <>
  struct is_vec_type<std::int8_t> : public std::integral_constant<bool, true>
  {
  };

  template <>
  struct is_vec_type<std::int16_t> : public std::integral_constant<bool, true>
  {
  };

  template <>
  struct is_vec_type<std::int32_t> : public std::integral_constant<bool, true>
  {
  };

  template <>
  struct is_vec_type<std::int64_t> : public std::integral_constant<bool, true>
  {
  };

  template <>
  struct is_vec_type<std::uint8_t> : public std::integral_constant<bool, true>
  {
  };

  template <>
  struct is_vec_type<std::uint16_t> : public std::integral_constant<bool, true>
  {
  };

  template <>
  struct is_vec_type<std::uint32_t> : public std::integral_constant<bool, true>
  {
  };

  template <>
  struct is_vec_type<std::uint64_t> : public std::integral_constant<bool, true>
  {
  };
} // namespace cagey::math
