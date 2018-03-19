////////////////////////////////////////////////////////////////////////////////
//
// cagey-engine - Toy 3D Engine
// Copyright (c) 2014 Kyle Girard <theycallmecoach@gmail.com>
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

#include <cagey-math/Degree.hh>
#include <cagey-math/Radian.hh>
#include <gtest/gtest.h>

using namespace cagey::math;

TEST(Degree, DefaultConstructor) {
  Degree<float> d;
  ASSERT_EQ(sizeof(d), sizeof(float));
}

TEST(Degree, ValueConstructor) {
  Degree<float> d{45.0f};

  EXPECT_FLOAT_EQ(45.0f, float(d));
}

TEST(Degree, CoversionCopyConstructor) {
  Degree<int> d{45};
  Degree<float> d2{d};

  EXPECT_FLOAT_EQ(45.0f, float(d2));
}

TEST(Degree, CopyConstructor) {
  Degree<float> d{45};
  Degree<float> d2{d};

  EXPECT_FLOAT_EQ(45.0f, float(d2));
}

TEST(Degree, CopyAssignmentConstructor) {
  Degree<float> d{45};
  Degree<float> d2{20};
  d2 = d;

  EXPECT_FLOAT_EQ(45.0f, float(d2));
}

TEST(Degree, RadianConversionConstructor) {
  Radian<float> d{1.0f};
  Degree<float> d2{d};
  EXPECT_TRUE(equals(float(d2), 57.295776f));
}

TEST(Degree, AddAssignOperator) {
  Degree<float> d{45.0f};
  Degree<float> d2{45.0f};
  d += d2;

  EXPECT_FLOAT_EQ(90.0f, float(d));
}

TEST(Degree, SubtractAssignOperator) {
  Degree<float> d{45.0f};
  Degree<float> d2{45.0f};
  d -= d2;

  EXPECT_FLOAT_EQ(0.0f, float(d));
}

TEST(Degree, MultiplicationAssignOperator) {
  Degree<float> d{45.0f};
  d *= 3.0f;

  EXPECT_FLOAT_EQ(135.0f, float(d));
}

TEST(Degree, DivideAssignOperator) {
  Degree<float> d{45.0f};
  d /= 3.0f;

  EXPECT_FLOAT_EQ(15.0f, float(d));
}

TEST(Degree, AddOperator) {
  Degree<float> d{45.0f};
  Degree<float> d2{45.0f};
  auto d3 = d + d2;

  EXPECT_FLOAT_EQ(90.0f, float(d3));
}

TEST(Degree, SubtractOperator) {
  Degree<float> d{45.0f};
  Degree<float> d2{45.0f};
  auto d3 = d - d2;

  EXPECT_FLOAT_EQ(0.0f, float(d3));
}

TEST(Degree, MultiplicationOperator) {
  Degree<float> d{45.0f};
  auto d2 = d * 3.0f;
  auto d3 = 2.0f * d;

  EXPECT_FLOAT_EQ(135.0f, float(d2));
  EXPECT_FLOAT_EQ(90.0f, float(d3));
}

TEST(Degree, DivideOperator) {
  Degree<float> d{45.0f};
  auto d2 = d / 2.0f;

  EXPECT_FLOAT_EQ(22.5f, float(d2));
}

TEST(Degree, EqualityOperator) {
  Degree<int> d{45};
  Degree<int> d2{45};

  EXPECT_TRUE(d == d2);
}

TEST(Degree, InequalityOperator) {
  Degree<int> d{45};
  Degree<int> d3{30};

  EXPECT_TRUE(d != d3);
}

TEST(Degree, LessThanOperator) {
  Degree<int> d{45};
  Degree<int> d3{30};

  EXPECT_TRUE(d3 < d);
}

TEST(Degree, LessThanEqualOperator) {
  Degree<int> d{45};
  Degree<int> d3{30};

  EXPECT_TRUE(d3 <= d);
  EXPECT_TRUE(d <= d);
}

TEST(Degree, GreaterThanOperator) {
  Degree<int> d{45};
  Degree<int> d3{30};

  EXPECT_TRUE(d > d3);
}

TEST(Degree, GreaterThanEqualOperator) {
  Degree<int> d{45};
  Degree<int> d3{30};

  EXPECT_TRUE(d >= d3);
  EXPECT_TRUE(d >= d);
}

TEST(Degree, LiteralOperator) {
  auto a = 45.0_deg;
  auto b = 45.3_degf;

  EXPECT_FLOAT_EQ(45.0, double(a));
  EXPECT_TRUE(equals(45.3f, float(b)));
}

TEST(Degree, equals) {
  Degree<float> d{45.0f};
  Degree<float> d2{45.0f};
  EXPECT_TRUE(equals(d, d2));
  EXPECT_FALSE(equals(d, Degree<float>{30}));
}
