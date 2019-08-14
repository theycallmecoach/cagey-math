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

#include <type_traits> //for std::is_arithmetic
#include <array>       //for std::array
#include <utility>     //for std::index_sequence
#include <algorithm>   //for std::transform, std::negate, std::equal
#include <numeric>     //for std::numeric_limits
#include <iostream>

namespace cagey::math {

  template <template <typename, std::size_t> class D, typename T, std::size_t N>
  class BasePoint {
  public:
    /** @cond doxygen has some issues with static assert */
    static_assert(N != 0, "BasePoint cannot have zero elements");
    static_assert(std::is_arithmetic<T>::value,
                  "Underlying type must be a number");
    /** @endcond */

    /// The underlying type of this Point
    using Type = T;

    /// The number of elements in this Point
    const static std::size_t Size = N;

    /**
    * Construct a Point with all elements initialized to Zero
    */
    constexpr BasePoint() noexcept;

    /**
    * Construct a Point with all elements initialized to the given value
    *
    * @param v the value to assign to all elements of this Point
    */
    explicit BasePoint(T const v) noexcept;

    /**
    * Construct a Point using the given pointer.  Note: It assumed the given
    * pointer contains N values;
    */
    explicit BasePoint(T *const v) noexcept;

    /**
    * Construct a Point using the values from the given std::array
    *
    * @param vals vals[0] is assigned to data[0] etc. etc.
    */
    constexpr explicit BasePoint(std::array<T, Size> const &vals) noexcept;

    /**
    * Conversion Copy Constructor.  Construct a Point using a Point with a
    * different
    * underlying type.  Only simple type conversion is performed
    */
    template <typename U, typename I = std::make_index_sequence<Size>>
    constexpr explicit BasePoint(BasePoint<D, U, Size> const &other) noexcept;

    /**
    * Index operator
    *
    * @param i index into this Point
    * @return a reference to the element at index i
    */
    constexpr auto operator[](std::size_t i) noexcept -> T &;

    /**
    * Index operator
    *
    * @param i index into this Point
    * @return a reference to the element at index i
    */
    constexpr auto operator[](std::size_t i) const noexcept -> T const &;

    /**
    * Return an iterator to the first element of this Point
    *
    * @return an iterator pointing to the begining of this Point
    */
    constexpr auto begin() noexcept -> T *;

    /**
    * Return an iterator to the first element of this Point
    *
    * @return an iterator pointing to the begining of this Point
    */
    constexpr auto begin() const noexcept -> T *;

    /**
    * Return an iterator to the end of this Point.
    *
    * @return an iterator pointing to the end of this Point
    */
    constexpr auto end() noexcept -> T *;

    /**
    * Return an iterator to the end of this Point.
    *
    * @return an iterator pointing to the end of this Point
    */
    constexpr auto end() const noexcept -> T *;

  private:
    template <class U, std::size_t... I>
    constexpr explicit BasePoint(BasePoint<D, U, Size> const &other,
                                 std::index_sequence<I...>) noexcept;

  public:
    /// Array containing Point elements
    std::array<T, N> data;
  };

  /**
  * Point two element specialization
  */
  template <template <typename, std::size_t> class D, typename T>
  class BasePoint<D, T, 2> {
    /** @cond doxygen has issues with static_assert */
    static_assert(std::is_arithmetic<T>::value,
                  "Underlying type must be a number");
    /** @endcond */
  public:
    /// The underlying type of this Point
    using Type = T;

    /// The number of elements in this Point
    const static std::size_t Size = 2;

    /**
    * Construct a Point with all elements initialized to Zero
    */
    constexpr BasePoint() noexcept;

    /**
    * Construct a Point with all elements initialized to the given value
    *
    * @param v the value to assign to all elements of this Point
    */
    constexpr explicit BasePoint(T const v) noexcept;

    /**
    * Construct a Point with the given elements a and b are assigned to x and y
    * respectively
    */
    constexpr BasePoint(T const a, T const b) noexcept;

    /**
    * Construct a Point using the given pointer.  Note: It assumed the given
    * pointer contains two values;
    */
    explicit BasePoint(T *const v) noexcept;

    /**
    * Construct a Point using the values from the given std::array
    *
    * @param vals vals[0] is assigned to data[0] etc. etc.
    */
    constexpr explicit BasePoint(std::array<T, Size> const &vals) noexcept;

    /**
    * Conversion Copy Constructor.  Construct a Point using a Point with a
    * different
    * underlying type.  Only simple type conversion is performed
    */
    template <typename U>
    constexpr explicit BasePoint(BasePoint<D, U, Size> const &other) noexcept;

    /**
    * Index operator
    *
    * @param i index into this Point
    * @return a reference to the element at index i
    */
    constexpr auto operator[](std::size_t i) noexcept -> T &;

    /**
    * Index operator
    *
    * @param i index into this Point
    * @return a reference to the element at index i
    */
    constexpr auto operator[](std::size_t i) const noexcept -> T const &;

    /**
    * Return an iterator to the first element of this Point
    *
    * @return an iterator pointing to the begining of this Point
    */
    constexpr auto begin() noexcept -> T *;

    /**
    * Return an iterator to the first element of this Point
    *
    * @return an iterator pointing to the begining of this Point
    */
    constexpr auto begin() const noexcept -> T *;

    /**
    * Return an iterator to the end of this Point.
    *
    * @return an iterator pointing to the end of this Point
    */
    constexpr auto end() noexcept -> T *;

    /**
    * Return an iterator to the end of this Point.
    *
    * @return an iterator pointing to the end of this Point
    */
    constexpr auto end() const noexcept -> T *;

  public:
    /**
    * Anonymous union to allow access to members using different names
    */
    union {
      /// Data represented as a std::array
      std::array<T, 2> data;
      struct {
        T x; ///< The first element
        T y; ///<The second element
      };
      struct {
        T w; ///< Width
        T h; ///< Height
      };
    };
  };

  /**
  * Point three element specialization
  */
  template <template <typename, std::size_t> class D, typename T>
  class BasePoint<D, T, 3> {
    /** @cond doxygen has issues with static_assert */
    static_assert(std::is_arithmetic<T>::value,
                  "Underlying type must be a number");
    /** @endcond */
  public:
    /// The underlying type of this Point
    using Type = T;

    /// The number of elements in this Point
    const static std::size_t Size = 3;

    /**
    * Construct a Point with all elements initialized to Zero
    */
    constexpr BasePoint() noexcept;

    /**
    * Construct a Point with all elements initialized to the given value
    *
    * @param v the value to assign to all elements of this Point
    */
    constexpr explicit BasePoint(T const v) noexcept;

    /**
     * Construct a Vector with the given elements a,b,c -> x, y, z
     * @param a value to assign to x
     * @param b value to assign to y
     * @param c value to assign to z
     */
    constexpr BasePoint(T const a, T const b, T const c) noexcept;

    /**
    * Construct a Point using the given pointer.  Note: It assumed the given
    * pointer contains two values;
    */
    explicit BasePoint(T *const v) noexcept;

    /**
    * Construct a Point using the values from the given std::array
    *
    * @param vals vals[0] is assigned to data[0] etc. etc.
    */
    constexpr explicit BasePoint(std::array<T, Size> const &vals) noexcept;

    /**
    * Conversion Copy Constructor.  Construct a Point using a Point with a
    * different
    * underlying type.  Only simple type conversion is performed
    */
    template <typename U>
    constexpr explicit BasePoint(BasePoint<D, U, Size> const &other) noexcept;

    /**
    * Index operator
    *
    * @param i index into this Point
    * @return a reference to the element at index i
    */
    constexpr auto operator[](std::size_t i) noexcept -> T &;

    /**
    * Index operator
    *
    * @param i index into this Point
    * @return a reference to the element at index i
    */
    constexpr auto operator[](std::size_t i) const noexcept -> T const &;

    /**
    * Return an iterator to the first element of this Point
    *
    * @return an iterator pointing to the begining of this Point
    */
    constexpr auto begin() noexcept -> T *;

    /**
    * Return an iterator to the first element of this Point
    *
    * @return an iterator pointing to the begining of this Point
    */
    constexpr auto begin() const noexcept -> T *;

    /**
    * Return an iterator to the end of this Point.
    *
    * @return an iterator pointing to the end of this Point
    */
    constexpr auto end() noexcept -> T *;

    /**
    * Return an iterator to the end of this Point.
    *
    * @return an iterator pointing to the end of this Point
    */
    constexpr auto end() const noexcept -> T *;

  public:
    /**
    * Anonymous union to allow access to members using different names
    */
    union {
      /// Data represented as a std::array
      std::array<T, Size> data;
      struct {
        T x; ///< The first element
        T y; ///<The second element
        T z; ///<The third element
      };
      struct {
        T r; ///< First element
        T g; ///< Second element
        T b; ///< Third element
      };
    };
  };

  /**
  * Point four element specialization
  */
  template <template <typename, std::size_t> class D, typename T>
  class BasePoint<D, T, 4> {
    /** @cond doxygen has issues with static_assert */
    static_assert(std::is_arithmetic<T>::value,
                  "Underlying type must be a number");
    /** @endcond */
  public:
    /// The underlying type of this Point
    using Type = T;

    /// The number of elements in this Point
    const static std::size_t Size = 4;

    /**
    * Construct a Point with all elements initialized to Zero
    */
    constexpr BasePoint() noexcept;

    /**
    * Construct a Point with all elements initialized to the given value
    *
    * @param v the value to assign to all elements of this Point
    */
    constexpr explicit BasePoint(T const v) noexcept;

    /**
      * Construct a BasePoint with the given elements a,b,c, d -> x, y, z, w
      * @param a value to assign to x
      * @param b value to assign to y
      * @param c value to assign to z
      * @param d value to assign to w
      */
    constexpr BasePoint(T const a, T const b, T const c, T const d) noexcept;

    /**
    * Construct a Point using the given pointer.  Note: It assumed the given
    * pointer contains two values;
    */
    explicit BasePoint(T *const v) noexcept;

    /**
    * Construct a Point using the values from the given std::array
    *
    * @param vals vals[0] is assigned to data[0] etc. etc.
    */
    constexpr explicit BasePoint(std::array<T, Size> const &vals) noexcept;

    /**
    * Conversion Copy Constructor.  Construct a Point using a Point with a
    * different
    * underlying type.  Only simple type conversion is performed
    */
    template <typename U>
    constexpr explicit BasePoint(BasePoint<D, U, Size> const &other) noexcept;

    /**
    * Index operator
    *
    * @param i index into this Point
    * @return a reference to the element at index i
    */
    constexpr auto operator[](std::size_t i) noexcept -> T &;

    /**
    * Index operator
    *
    * @param i index into this Point
    * @return a reference to the element at index i
    */
    constexpr auto operator[](std::size_t i) const noexcept -> T const &;

    /**
    * Return an iterator to the first element of this Point
    *
    * @return an iterator pointing to the begining of this Point
    */
    constexpr auto begin() noexcept -> T *;

    /**
    * Return an iterator to the first element of this Point
    *
    * @return an iterator pointing to the begining of this Point
    */
    constexpr auto begin() const noexcept -> T *;

    /**
    * Return an iterator to the end of this Point.
    *
    * @return an iterator pointing to the end of this Point
    */
    constexpr auto end() noexcept -> T *;

    /**
    * Return an iterator to the end of this Point.
    *
    * @return an iterator pointing to the end of this Point
    */
    constexpr auto end() const noexcept -> T *;

  public:
    /**
    * Anonymous union to allow access to members using different names
    */
    union {
      /// Data represented as a std::array
      std::array<T, Size> data;
      struct {
        T x; ///< The first element
        T y; ///<The second element
        T z; ///<The third element
        T w; ///<The fourth element
      };
      // Allow access to elements with a different name
      struct {
        T r; ///< First Element
        T g; ///< Second Element
        T b; ///< Third Element
        T a; ///< Fourth Element
      };
    };
  };

  /**
  * Swap the contents of the two BasePoints
  */
  template <template <typename, std::size_t> class D, typename T, std::size_t S>
  auto swap(BasePoint<D, T, S> & rhs, BasePoint<D, T, S> & lhs)->void {
    std::swap(rhs.data, lhs.data);
  }

  /**
  * Returns the smallest element in the given BasePoint
  *
  * @param vec the BasePoint to search for a small element
  * @return the smallest element of the given BasePoint
  */
  template <template <typename, std::size_t> class D, typename T, std::size_t S>
  inline auto min(BasePoint<D, T, S> const &vec)->T {
    return *std::min_element(std::begin(vec), std::end(vec));
  }

  /**
  * Returns the largest element in the given BasePoint
  *
  * @param vec the BasePoint to search for a large element
  * @return the largest element in the given BasePoint
  */
  template <template <typename, std::size_t> class D, typename T, std::size_t S>
  inline auto max(BasePoint<D, T, S> const &vec)->T {
    return *std::max_element(std::begin(vec), std::end(vec));
  }

  /**
  * Returns the sum of all the elements in the given BasePoint
  *
  * @param vec the BasePoint to search for a large element
  * @return the num of all of the elements of the given BasePoint
  */
  template <template <typename, std::size_t> class D, typename T, std::size_t S>
  inline auto sum(BasePoint<D, T, S> const &vec)->T {
    return std::accumulate(std::begin(vec), std::end(vec), T(0));
  }

  ////////////////////////////////////////////////////////////////////////////////
  //// BasePoint() Impl
  ////////////////////////////////////////////////////////////////////////////////
  // template<template<typename,std::size_t> class D,typename T, std::size_t S>
  // inline constexpr BasePoint<D,T,S>::BasePoint() noexcept : data() {};
  //
  // template<template<typename,std::size_t> class D,typename T>
  // inline constexpr BasePoint<D,T,2>::BasePoint() noexcept : data() {};

  //////////////////////////////////////////////////////////////////////////////
  // BasePoint() Impl
  //////////////////////////////////////////////////////////////////////////////
  template <template <typename, std::size_t> class D, typename T, std::size_t S>
  inline constexpr BasePoint<D, T, S>::BasePoint() noexcept : data(){};

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr BasePoint<D, T, 2>::BasePoint() noexcept : data(){};

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr BasePoint<D, T, 3>::BasePoint() noexcept : data(){};

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr BasePoint<D, T, 4>::BasePoint() noexcept : data(){};

  //////////////////////////////////////////////////////////////////////////////
  // BasePoint(T) Impl
  //////////////////////////////////////////////////////////////////////////////

  template <template <typename, std::size_t> class D, typename T, std::size_t S>
  inline BasePoint<D, T, S>::BasePoint(T const v) noexcept {
    data.fill(v);
  }

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr BasePoint<D, T, 2>::BasePoint(T const v) noexcept
      : data{{v, v}} {}

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr BasePoint<D, T, 3>::BasePoint(T const v) noexcept
      : data{{v, v, v}} {}

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr BasePoint<D, T, 4>::BasePoint(T const v) noexcept
      : data{{v, v, v, v}} {}

  //////////////////////////////////////////////////////////////////////////////
  // BasePoint() Component Impl
  //////////////////////////////////////////////////////////////////////////////

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr BasePoint<D, T, 2>::BasePoint(T const a, T const b) noexcept
      : x{a},
        y{b} {}

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr BasePoint<D, T, 3>::BasePoint(T const a, T const b,
                                                 T const c) noexcept : x{a},
                                                                       y{b},
                                                                       z{c} {}

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr BasePoint<D, T, 4>::BasePoint(
      T const a, T const b, T const c, T const d) noexcept : x{a},
                                                             y{b},
                                                             z{c},
                                                             w{d} {}

  //////////////////////////////////////////////////////////////////////////////
  // BasePoint(T*) Impl
  //////////////////////////////////////////////////////////////////////////////

  template <template <typename, std::size_t> class D, typename T, std::size_t S>
  inline BasePoint<D, T, S>::BasePoint(T * const v) noexcept {
    std::copy(std::begin(v), std::end(v), data.begin());
  }

  template <template <typename, std::size_t> class D, typename T>
  inline BasePoint<D, T, 2>::BasePoint(T * const v) noexcept : x{v[0]},
                                                               y{v[1]} {}

  template <template <typename, std::size_t> class D, typename T>
  inline BasePoint<D, T, 3>::BasePoint(T * const v) noexcept : x{v[0]},
                                                               y{v[1]},
                                                               z{v[2]} {}

  template <template <typename, std::size_t> class D, typename T>
  inline BasePoint<D, T, 4>::BasePoint(T * const v) noexcept : x{v[0]},
                                                               y{v[1]},
                                                               z{v[2]},
                                                               w{v[3]} {}

  //////////////////////////////////////////////////////////////////////////////
  // BasePoint(std::array) Impl
  //////////////////////////////////////////////////////////////////////////////

  template <template <typename, std::size_t> class D, typename T, std::size_t S>
  inline constexpr BasePoint<D, T, S>::BasePoint(
      std::array<T, Size> const &vals) noexcept : data(vals) {}

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr BasePoint<D, T, 2>::BasePoint(
      std::array<T, Size> const &vals) noexcept : data(vals) {}

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr BasePoint<D, T, 3>::BasePoint(
      std::array<T, Size> const &vals) noexcept : data(vals) {}

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr BasePoint<D, T, 4>::BasePoint(
      std::array<T, Size> const &vals) noexcept : data(vals) {}

  //////////////////////////////////////////////////////////////////////////////
  // BasePoint(BasePoint<U>) Impl
  //////////////////////////////////////////////////////////////////////////////

  template <template <typename, std::size_t> class D, typename T, size_t S>
  template <typename U, typename I>
  inline constexpr BasePoint<D, T, S>::BasePoint(
      BasePoint<D, U, Size> const &other) noexcept : BasePoint(other, I()) {}

  template <template <typename, std::size_t> class D, typename T, size_t S>
  template <typename U, std::size_t... I>
  inline constexpr BasePoint<D, T, S>::BasePoint(
      BasePoint<D, U, Size> const &other, std::index_sequence<I...>)noexcept
      : data{{(T(other.data[I]))...}} {}

  template <template <typename, std::size_t> class D, typename T>
  template <typename U>
  inline constexpr BasePoint<D, T, 2>::BasePoint(
      BasePoint<D, U, Size> const &p) noexcept : data{{T(p.x), T(p.y)}} {}

  template <template <typename, std::size_t> class D, typename T>
  template <typename U>
  inline constexpr BasePoint<D, T, 3>::BasePoint(
      BasePoint<D, U, Size> const &other) noexcept
      : data{{T(other[0]), T(other[1]), T(other[2])}} {}

  template <template <typename, std::size_t> class D, typename T>
  template <typename U>
  inline constexpr BasePoint<D, T, 4>::BasePoint(
      BasePoint<D, U, Size> const &other) noexcept
      : data{{T(other[0]), T(other[1]), T(other[2]), T(other[3])}} {}

  //////////////////////////////////////////////////////////////////////////////
  // BasePoint::operator[] Impl
  //////////////////////////////////////////////////////////////////////////////

  template <template <typename, std::size_t> class D, typename T, std::size_t S>
  inline constexpr auto BasePoint<D, T, S>::operator[](
      std::size_t i) noexcept->T & {
    return this->data[i];
  }

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr auto BasePoint<D, T, 2>::operator[](
      std::size_t i) noexcept->T & {
    return this->data[i];
  }

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr auto BasePoint<D, T, 3>::operator[](
      std::size_t i) noexcept->T & {
    return this->data[i];
  }

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr auto BasePoint<D, T, 4>::operator[](
      std::size_t i) noexcept->T & {
    return this->data[i];
  }

  template <template <typename, std::size_t> class D, typename T, std::size_t S>
  inline constexpr auto BasePoint<D, T, S>::operator[](std::size_t i)
      const noexcept->T const & {
    return data[i];
  }

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr auto BasePoint<D, T, 2>::operator[](std::size_t i)
      const noexcept->T const & {
    return this->data[i];
  }

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr auto BasePoint<D, T, 3>::operator[](std::size_t i)
      const noexcept->T const & {
    return this->data[i];
  }

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr auto BasePoint<D, T, 4>::operator[](std::size_t i)
      const noexcept->T const & {
    return this->data[i];
  }

  //////////////////////////////////////////////////////////////////////////////
  // BasePoint::begin() Impl
  //////////////////////////////////////////////////////////////////////////////

  template <template <typename, std::size_t> class D, typename T, std::size_t S>
  inline constexpr auto BasePoint<D, T, S>::begin() noexcept->T * {
    return data.begin();
  }

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr auto BasePoint<D, T, 2>::begin() noexcept->T * {
    return data.begin();
  }

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr auto BasePoint<D, T, 3>::begin() noexcept->T * {
    return data.begin();
  }

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr auto BasePoint<D, T, 4>::begin() noexcept->T * {
    return data.begin();
  }

  template <template <typename, std::size_t> class D, typename T, std::size_t S>
  inline constexpr auto BasePoint<D, T, S>::begin() const noexcept->T * {
    return data.begin();
  }

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr auto BasePoint<D, T, 2>::begin() const noexcept->T * {
    return data.begin();
  }

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr auto BasePoint<D, T, 3>::begin() const noexcept->T * {
    return data.begin();
  }

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr auto BasePoint<D, T, 4>::begin() const noexcept->T * {
    return data.begin();
  }

  //////////////////////////////////////////////////////////////////////////////
  // BasePoint::end() Impl
  //////////////////////////////////////////////////////////////////////////////

  template <template <typename, std::size_t> class D, typename T, std::size_t S>
  inline constexpr auto BasePoint<D, T, S>::end() noexcept->T * {
    return data.end();
  }

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr auto BasePoint<D, T, 2>::end() noexcept->T * {
    return data.end();
  }

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr auto BasePoint<D, T, 3>::end() noexcept->T * {
    return data.end();
  }

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr auto BasePoint<D, T, 4>::end() noexcept->T * {
    return data.end();
  }

  template <template <typename, std::size_t> class D, typename T, std::size_t S>
  inline constexpr auto BasePoint<D, T, S>::end() const noexcept->T * {
    return data.end();
  }

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr auto BasePoint<D, T, 2>::end() const noexcept->T * {
    return data.end();
  }

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr auto BasePoint<D, T, 3>::end() const noexcept->T * {
    return data.end();
  }

  template <template <typename, std::size_t> class D, typename T>
  inline constexpr auto BasePoint<D, T, 4>::end() const noexcept->T * {
    return data.end();
  }

  //////////////////////////////////////////////////////////////////////////////
  // BasePoint::operator+= Impl
  //////////////////////////////////////////////////////////////////////////////

  template <template <typename, std::size_t> class D, typename T, std::size_t S>
  inline auto operator+=(BasePoint<D, T, S> & lhs, BasePoint<D, T, S> & rhs)
      ->void {
    std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(),
                   [](T l, T r) -> T { return l + r; });
  }

  //////////////////////////////////////////////////////////////////////////////
  // BasePoint::operator-= Impl
  //////////////////////////////////////////////////////////////////////////////

  template <template <typename, std::size_t> class D, typename T, std::size_t S>
  inline auto operator-=(BasePoint<D, T, S> & lhs, BasePoint<D, T, S> & rhs)
      ->void {
    std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(),
                   [](T l, T r) -> T { return l - r; });
  }

  //////////////////////////////////////////////////////////////////////////////
  // BasePoint::operator*= Impl
  //////////////////////////////////////////////////////////////////////////////

  template <template <typename, std::size_t> class D, typename T, std::size_t S>
  inline auto operator*=(BasePoint<D, T, S> & lhs, T value)->void {
    std::for_each(lhs.begin(), lhs.end(), [value](T &t) { t *= value; });
  }

  //////////////////////////////////////////////////////////////////////////////
  // BasePoint::operator/= Impl
  //////////////////////////////////////////////////////////////////////////////

  template <template <typename, std::size_t> class D, typename T, std::size_t S>
  inline auto operator/=(BasePoint<D, T, S> & lhs, T value)->void {
    std::for_each(lhs.begin(), lhs.end(), [value](T &t) { t /= value; });
  }

  //////////////////////////////////////////////////////////////////////////////
  // BasePoint::operator== Impl
  //////////////////////////////////////////////////////////////////////////////

  template <template <typename, std::size_t> class D, typename T, std::size_t S>
  auto operator==(BasePoint<D, T, S> const &rhs, BasePoint<D, T, S> const &lhs)
      ->BasePoint<D, T, S> {
    return rhs.data == rhs.data;
  }

  template <template <typename, std::size_t> class D, typename T, std::size_t S>
  auto operator!=(BasePoint<D, T, S> const &rhs, BasePoint<D, T, S> const &lhs)
      ->BasePoint<D, T, S> {
    return !(rhs.data == rhs.data);
  }

  //////////////////////////////////////////////////////////////////////////////
  // BasePoint::operator+ Impl
  //////////////////////////////////////////////////////////////////////////////
  template <template <typename, std::size_t> class D, typename T, std::size_t S>
  auto operator+(BasePoint<D, T, S> rhs, BasePoint<D, T, S> const &lhs)
      ->BasePoint<D, T, S> {
    rhs += lhs;
    return rhs;
  }

  //////////////////////////////////////////////////////////////////////////////
  // BasePoint::operator- Impl
  //////////////////////////////////////////////////////////////////////////////
  template <template <typename, std::size_t> class D, typename T, std::size_t S>
  auto operator-(BasePoint<D, T, S> vec)->BasePoint<D, T, S> {
    std::transform(vec.begin(), vec.end(), vec.begin(), std::negate<T>());
    return vec;
  }

  template <template <typename, std::size_t> class D, typename T, std::size_t S>
  auto operator-(BasePoint<D, T, S> rhs, BasePoint<D, T, S> const &lhs)
      ->BasePoint<D, T, S> {
    rhs -= lhs;
    return rhs;
  }

  //////////////////////////////////////////////////////////////////////////////
  // BasePoint::operator* Impl
  //////////////////////////////////////////////////////////////////////////////
  template <template <typename, std::size_t> class D, typename T, std::size_t S>
  auto operator*(BasePoint<D, T, S> rhs, T lhs)->BasePoint<D, T, S> {
    rhs *= lhs;
    return rhs;
  }

  //////////////////////////////////////////////////////////////////////////////
  // BasePoint::operator/ Impl
  //////////////////////////////////////////////////////////////////////////////
  template <template <typename, std::size_t> class D, typename T, std::size_t S>
  auto operator/(BasePoint<D, T, S> rhs, T lhs)->BasePoint<D, T, S> {
    rhs /= lhs;
    return rhs;
  }

  //////////////////////////////////////////////////////////////////////////////
  // BasePoint::operator<< Impl
  //////////////////////////////////////////////////////////////////////////////
  template <template <typename, std::size_t> class D, typename T, std::size_t S>
  std::ostream &operator<<(std::ostream & sink, BasePoint<D, T, S> const &vec) {
    sink << "( ";
    std::for_each(vec.begin(), vec.end() - 1,
                  [&sink](T &v) { sink << v << ", "; });
    sink << vec[S - 1] << " )";
    return sink;
  }

} // namespace cagey::math
