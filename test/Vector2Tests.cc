#include "gtest/gtest.h"
#include <cagey-math/Vector.hh>
#include <cstdint>

using namespace cagey::math;

TEST(Vector2Test, Vector2SizeTest) {
  ASSERT_EQ(sizeof(Vec2<short>), sizeof(short[2]));
  ASSERT_EQ(sizeof(Vec2f), sizeof(float[2]));
  ASSERT_EQ(sizeof(Vec2d), sizeof(double[2]));
  ASSERT_EQ(sizeof(Vec2i), sizeof(int[2]));
  ASSERT_EQ(sizeof(Vec2u), sizeof(unsigned int[2]));
}

TEST(Vector2Test, Vector2AlignTest) {
  ASSERT_EQ(alignof(Vec2<short>), alignof(short[2]));
  ASSERT_EQ(alignof(Vec2f), alignof(float[2]));
  ASSERT_EQ(alignof(Vec2d), alignof(double[2]));
  ASSERT_EQ(alignof(Vec2i), alignof(int[2]));
  ASSERT_EQ(alignof(Vec2u), alignof(unsigned int[2]));
}

TEST(Vector2Test, Vector2ComponentTypeTest) {
  ASSERT_EQ((std::is_same<typename Vec2<short>::Type, short>::value), true);
  ASSERT_EQ((std::is_same<typename Vec2<float>::Type, float>::value), true);
  ASSERT_EQ((std::is_same<typename Vec2<double>::Type, double>::value), true);
  ASSERT_EQ((std::is_same<typename Vec2<int>::Type, int>::value), true);
  ASSERT_EQ(
      (std::is_same<typename Vec2<unsigned int>::Type, unsigned int>::value),
      true);
}

TEST(Vector2Test, Vector2ComponentCountTest) {
  constexpr auto v2s = Vec2<short>::Size;
  constexpr auto v2f = Vec2f::Size;
  constexpr auto v2d = Vec2d::Size;
  constexpr auto v2i = Vec2i::Size;
  constexpr auto v2u = Vec2u::Size;
  ASSERT_EQ(v2s, 2);
  ASSERT_EQ(v2f, 2);
  ASSERT_EQ(v2d, 2);
  ASSERT_EQ(v2i, 2);
  ASSERT_EQ(v2u, 2);
}

TEST(Vector2Test, DefaultConstructorTest) { Vec2f v; }

TEST(Vector2Test, ScalarConstructorTest) {
  constexpr Vec2d v{4.8};
  constexpr Vec2d v2{4};
  ASSERT_DOUBLE_EQ(v[0], 4.8);
  ASSERT_DOUBLE_EQ(v[1], 4.8);
}

TEST(Vector2Test, ComponentConstructorTest) {
  constexpr Vec2d v{4.8, 5.6};
  ASSERT_DOUBLE_EQ(v[0], 4.8);
  ASSERT_DOUBLE_EQ(v[1], 5.6);
}

TEST(Vector2Test, BeginTest) {
  const Vec2d cvd{1.2};
  const double *cdata = cvd.begin();
  ASSERT_EQ(cdata, static_cast<const void *>(&cvd));
}

TEST(Vector2Test, EndTest) {
  constexpr Vec2d v{4.8, 5.6};
  ASSERT_EQ(v.end(), (&v[1] + 1));
}

TEST(Vector2Test, ExplicitConversionConstructorTest) {
  constexpr Vec2d vd{4.8f, 5.6f};
  constexpr Vec2f vf{vd};
  ASSERT_DOUBLE_EQ(vf[0], 4.8f);
  ASSERT_DOUBLE_EQ(vf[1], 5.6f);
}

// // TEST(Vector2Test, ImplicitConversionConstructorTest) {
// //   constexpr Vec2f vf{4.8f, 5.6f};
// //   constexpr Vec2d vd = vf;
// //   ASSERT_DOUBLE_EQ(vd[0], 4.8f);
// //   ASSERT_DOUBLE_EQ(vd[1], 5.6f);
// // }
//
// // TEST(Vector2Test, ZeroTest) {
// //   constexpr auto v = Vec2f::zero();
// //   ASSERT_EQ(v, Vec2f{0.0f});
// // }
//
TEST(Vector2Test, XAxisTest) {
  constexpr auto v = Vec2f::xAxis();
  ASSERT_EQ(v, Vec2f(1.0f, 0.0f));
}

TEST(Vector2Test, YAxisTest) {
  constexpr auto v = Vec2f::yAxis();
  ASSERT_EQ(v, Vec2f(0.0f, 1.0f));
}

TEST(Vector2Test, ArrayIndexOperatorTest) {
  constexpr Vec2d vd{1.3, 5.3};
  auto vd0 = vd[0];
  auto vd1 = vd[1];
  ASSERT_DOUBLE_EQ(vd0, 1.3);
  ASSERT_DOUBLE_EQ(vd1, 5.3);

  const auto cvd = vd;
  const auto &cv0 = cvd[0];
  const auto &cv1 = cvd[1];
  ASSERT_EQ(&cv0, cvd.begin() + 0);
  ASSERT_EQ(&cv1, cvd.begin() + 1);

  auto v = vd;
  auto &v0 = v[0];
  auto &v1 = v[1];
  ASSERT_EQ(&v0, v.begin() + 0);
  ASSERT_EQ(&v1, v.begin() + 1);
}

TEST(Vector2Test, ReadFieldTest) {
  const Vec2d cvd{1.2, 8.9};
  ASSERT_DOUBLE_EQ(cvd.x, 1.2);
  ASSERT_DOUBLE_EQ(cvd.w, 1.2);
  ASSERT_DOUBLE_EQ(cvd.y, 8.9);
  ASSERT_DOUBLE_EQ(cvd.h, 8.9);
}

TEST(Vector2Test, WriteFieldTest) {
  Vec2d cvd{1.2, 8.9};
  cvd.x = 3.4;
  cvd.y = 2.3;
  ASSERT_DOUBLE_EQ(cvd.x, 3.4);
  ASSERT_DOUBLE_EQ(cvd.y, 2.3);
  ASSERT_DOUBLE_EQ(cvd.w, 3.4);
  ASSERT_DOUBLE_EQ(cvd.h, 2.3);
}

// // TEST(Vector2Test, PreIncrementOperatorTest) {
// //   Vec2i vi{1, 2};
// //   ASSERT_EQ(&(++vi), &vi);
// //   ASSERT_EQ(vi[0], 2);
// //   ASSERT_EQ(vi[1], 3);
// // }
// //
// // TEST(Vector2Test, PostIncrementOperatorTest) {
// //   Vec2i vi{1, 2};
// //   ASSERT_EQ(vi++, Vec2i(1, 2));
// //   ASSERT_EQ(vi[0], 2);
// //   ASSERT_EQ(vi[1], 3);
// // }

TEST(Vector2Test, AdditionAssignmentOperatorTest) {
  // Vec2d v1{1.2, 3.4};
  // ASSERT_EQ(&(v1 += 5), &v1);
  // ASSERT_DOUBLE_EQ(v1[0], 1.2 + 5);
  // ASSERT_DOUBLE_EQ(v1[1], 3.4 + 5);

  Vec2d v2{1.2, 3.4};
  ASSERT_EQ(&(v2 += Vec2d(5.0, 6.0)), &v2);
  ASSERT_DOUBLE_EQ(v2[0], 1.2 + 5.0);
  ASSERT_DOUBLE_EQ(v2[1], 3.4 + 6.0);
}

// // TEST(Vector2Test, SubtractionAssignmentOperatorTest) {
// //   // Vec2d v1{3.2, 3.7};
// //   // ASSERT_EQ(&(v1 -= 1), &v1);
// //   // ASSERT_DOUBLE_EQ(v1[0], 3.2 - 1);
// //   // ASSERT_DOUBLE_EQ(v1[1], 3.7 - 1);
// //
// //   Vec2d v2{8.9, 9.0};
// //   ASSERT_EQ(&(v2 -= Vec2i(5, 6)), &v2);
// //   ASSERT_DOUBLE_EQ(v2[0], 8.9 - 5);
// //   ASSERT_DOUBLE_EQ(v2[1], 9.0 - 6);
// // }
//
TEST(Vector2Test, MultiplicationAssignmentOperatorTest) {
  Vec2d v1{2.3, 2.4};
  ASSERT_EQ(&(v1 *= 2), &v1);
  ASSERT_DOUBLE_EQ(v1[0], 2.3 * 2);
  ASSERT_DOUBLE_EQ(v1[1], 2.4 * 2);

  // Vec2d v2{8.9, 9.0};
  // ASSERT_EQ(&(v2 *= Vec2i(5, 6)), &v2);
  // ASSERT_DOUBLE_EQ(v2[0], 8.9 * 5);
  // ASSERT_DOUBLE_EQ(v2[1], 9.0 * 6);
}
//
TEST(Vector2Test, DivisionAssignmentOperatorTest) {
  Vec2d v1{2.3, 2.4};
  ASSERT_EQ(&(v1 /= 2), &v1);
  ASSERT_DOUBLE_EQ(v1[0], 2.3 / 2);
  ASSERT_DOUBLE_EQ(v1[1], 2.4 / 2);

  // Vec2d v2{8.9, 9.0};
  // ASSERT_EQ(&(v2 /= Vec2i(5, 6)), &v2);
  // ASSERT_DOUBLE_EQ(v2[0], 8.9 / 5);
  // ASSERT_DOUBLE_EQ(v2[1], 9.0 / 6);
}

TEST(Vector2Test, AdditionOperatorTest) {
  // constexpr auto v1 = 1 + Vec2d(2.3, 4.5);
  // ASSERT_DOUBLE_EQ(v1[0], 1 + 2.3);
  // ASSERT_DOUBLE_EQ(v1[1], 1 + 4.5);
  //
  // constexpr auto v2 = Vec2d(1.2, 3.4) + 5;
  // ASSERT_DOUBLE_EQ(v2[0], 1.2 + 5);
  // ASSERT_DOUBLE_EQ(v2[1], 3.4 + 5);

  constexpr auto v3 = Vec2d(1.2, 3.4) + Vec2d(5.0, 6.0);
  ASSERT_DOUBLE_EQ(v3[0], 1.2 + 5);
  ASSERT_DOUBLE_EQ(v3[1], 3.4 + 6);
}

TEST(Vector2Test, SubtractionOperatorTest) {
  // constexpr auto v1 = 1 - Vec2d(2.3, 4.5);
  // ASSERT_DOUBLE_EQ(v1[0], 1 - 2.3);
  // ASSERT_DOUBLE_EQ(v1[1], 1 - 4.5);
  //
  // constexpr auto v2 = Vec2d(1.2, 3.4) - 5;
  // ASSERT_DOUBLE_EQ(v2[0], 1.2 - 5);
  // ASSERT_DOUBLE_EQ(v2[1], 3.4 - 5);

  constexpr auto v3 = Vec2d(1.2, 3.4) - Vec2d(5.0, 6.0);
  ASSERT_DOUBLE_EQ(v3[0], 1.2 - 5);
  ASSERT_DOUBLE_EQ(v3[1], 3.4 - 6);
}

TEST(Vector2Test, MultiplicationOperatorTest) {
  constexpr auto v1 = 1.0 * Vec2d(2.3, 4.5);
  ASSERT_DOUBLE_EQ(v1[0], 1 * 2.3);
  ASSERT_DOUBLE_EQ(v1[1], 1 * 4.5);

  constexpr auto v2 = Vec2d(1.2, 3.4) * 5.0;
  ASSERT_DOUBLE_EQ(v2[0], 1.2 * 5.0);
  ASSERT_DOUBLE_EQ(v2[1], 3.4 * 5.0);

  // constexpr auto v3 = Vec2d(1.2, 3.4) * Vec2i(5, 6);
  // ASSERT_DOUBLE_EQ(v3[0], 1.2 * 5);
  // ASSERT_DOUBLE_EQ(v3[1], 3.4 * 6);
}
//
// TEST(Vector2Test, DivisionOperatorTest) {
//   constexpr auto v1 = 1 / Vec2d(2.3, 4.5);
//   ASSERT_DOUBLE_EQ(v1[0], 1 / 2.3);
//   ASSERT_DOUBLE_EQ(v1[1], 1 / 4.5);
//
//   constexpr auto v2 = Vec2d(1.2, 3.4) / 5;
//   ASSERT_DOUBLE_EQ(v2[0], 1.2 / 5);
//   ASSERT_DOUBLE_EQ(v2[1], 3.4 / 5);
//
//   constexpr auto v3 = Vec2d(1.2, 3.4) / Vec2i(5, 6);
//   ASSERT_DOUBLE_EQ(v3[0], 1.2 / 5);
//   ASSERT_DOUBLE_EQ(v3[1], 3.4 / 6);
// }
//
TEST(Vector2Test, VectorDotProductTest) {
  constexpr auto x = dot(Vec2d(1.2, 3.4), Vec2d(7, 8));
  ASSERT_DOUBLE_EQ(x, 1.2 * 7 + 3.4 * 8);
}

TEST(Vector2Test, LengthProductTest) {
  ASSERT_DOUBLE_EQ(length(Vec2d(1.2, 3.4)),
                   std::sqrt(lengthSquared(Vec2d(1.2, 3.4))));

  constexpr auto x = dot(Vec2d(1.2, 3.4), Vec2d(7, 8));
  ASSERT_DOUBLE_EQ(x, 1.2 * 7 + 3.4 * 8);
}

TEST(Vector2Test, LengthSquaredProductTest) {
  constexpr auto x = lengthSquared(Vec2d(1.2, 3.4));
  ASSERT_DOUBLE_EQ(x, 1.2 * 1.2 + 3.4 * 3.4);
}

TEST(Vector2Test, NormalizeTest) {
  const Vec2d v(1.2, 3.4);
  ASSERT_EQ(normalize(v), v * (1 / length(v)));
}
