#include "gtest/gtest.h"
#include <cagey-math/Vector.hh>
#include <cstdint>

using namespace cagey::math;

TEST(Vector3Test, Vector3SizeTest) {
  ASSERT_EQ(sizeof(Vec3<short>), sizeof(short[3]));
  ASSERT_EQ(sizeof(Vec3f), sizeof(float[3]));
  ASSERT_EQ(sizeof(Vec3d), sizeof(double[3]));
  ASSERT_EQ(sizeof(Vec3i), sizeof(int[3]));
  ASSERT_EQ(sizeof(Vec3u), sizeof(unsigned int[3]));
}

TEST(Vector3Test, Vector3AlignTest) {
  ASSERT_EQ(alignof(Vec3<short>), alignof(short[3]));
  ASSERT_EQ(alignof(Vec3f), alignof(float[3]));
  ASSERT_EQ(alignof(Vec3d), alignof(double[3]));
  ASSERT_EQ(alignof(Vec3i), alignof(int[3]));
  ASSERT_EQ(alignof(Vec3u), alignof(unsigned int[3]));
}

TEST(Vector3Test, Vector3ComponentTypeTest) {
  ASSERT_EQ((std::is_same<typename Vec3<short>::Type, short>::value), true);
  ASSERT_EQ((std::is_same<typename Vec3<float>::Type, float>::value), true);
  ASSERT_EQ((std::is_same<typename Vec3<double>::Type, double>::value), true);
  ASSERT_EQ((std::is_same<typename Vec3<int>::Type, int>::value), true);
  ASSERT_EQ(
      (std::is_same<typename Vec3<unsigned int>::Type, unsigned int>::value),
      true);
}

TEST(Vector3Test, Vector3ComponentCountTest) {
  constexpr auto v3s = Vec3<short>::Size;
  constexpr auto v3f = Vec3f::Size;
  constexpr auto v3d = Vec3d::Size;
  constexpr auto v3i = Vec3i::Size;
  constexpr auto v3u = Vec3u::Size;
  ASSERT_EQ(v3s, 3);
  ASSERT_EQ(v3f, 3);
  ASSERT_EQ(v3d, 3);
  ASSERT_EQ(v3i, 3);
  ASSERT_EQ(v3u, 3);
}

TEST(Vector3Test, DefaultConstructorTest) { 
  Vec3f v; 
  ASSERT_EQ(sizeof(v), sizeof(float[3]));
}

TEST(Vector3Test, ScalarConstructorTest) {
  constexpr Vec3d v{4.8};
  ASSERT_DOUBLE_EQ(v[0], 4.8);
  ASSERT_DOUBLE_EQ(v[1], 4.8);
  ASSERT_DOUBLE_EQ(v[2], 4.8);
}

TEST(Vector3Test, ComponentConstructorTest) {
  constexpr Vec3d v{1.3, 4.8, 5.6};
  ASSERT_DOUBLE_EQ(v[0], 1.3);
  ASSERT_DOUBLE_EQ(v[1], 4.8);
  ASSERT_DOUBLE_EQ(v[2], 5.6);
}

TEST(Vector3Test, Vector2ConstructorTest) {
  constexpr Vec3d v{{1.2, 4.8}, 5.6};
  ASSERT_DOUBLE_EQ(v[0], 1.2);
  ASSERT_DOUBLE_EQ(v[1], 4.8);
  ASSERT_DOUBLE_EQ(v[2], 5.6);
}

TEST(Vector3Test, TruncateConstructorTest) {
  constexpr Vec4d v{1.2, 4.8, 5.6, 6.7};
  ASSERT_DOUBLE_EQ(v[0], 1.2);
  ASSERT_DOUBLE_EQ(v[1], 4.8);
  ASSERT_DOUBLE_EQ(v[2], 5.6);
}

TEST(Vector3Test, ExplicitConversionConstructorTest) {
  constexpr Vec3d vd{4.8f, 5.6f, 3.8f};
  constexpr Vec3f vf{vd};
  ASSERT_DOUBLE_EQ(vf[0], 4.8f);
  ASSERT_DOUBLE_EQ(vf[1], 5.6f);
  ASSERT_DOUBLE_EQ(vf[2], 3.8f);
}

// // TEST(Vector3Test, ImplicitConversionConstructorTest) {
// //   constexpr Vec3f vf{4.8f, 5.6f};
// //   constexpr Vec3d vd = vf;
// //   ASSERT_DOUBLE_EQ(vd[0], 4.8f);
// //   ASSERT_DOUBLE_EQ(vd[1], 5.6f);
// // }
TEST(Vector3Test, BeginTest) {
  const Vec3d cvd{1.2};
  const double *cdata = cvd.begin();
  ASSERT_EQ(cdata, static_cast<const void *>(&cvd));
}

TEST(Vector3Test, EndTest) {
  constexpr Vec3d v{4.8, 5.6, 3.8};
  ASSERT_EQ(v.end(), (&v[2] + 1));
}


TEST(Vector3Test, ZeroTest) {
  constexpr auto v = Vec3f::zero();
  ASSERT_EQ(v, Vec3f{0.0f});
}

TEST(Vector3Test, XAxisTest) {
  constexpr auto v = Vec3f::x_axis();
  ASSERT_EQ(v, Vec3f(1.0f, 0.0f, 0.0f));
}

TEST(Vector3Test, YAxisTest) {
  constexpr auto v = Vec3f::y_axis();
  ASSERT_EQ(v, Vec3f(0.0f, 1.0f, 0.0f));
}

TEST(Vector3Test, ArrayIndexOperatorTest) {
  constexpr Vec3d vd{1.3, 5.3, 2.8};
  auto vd0 = vd[0];
  auto vd1 = vd[1];
  auto vd2 = vd[2];
  ASSERT_DOUBLE_EQ(vd0, 1.3);
  ASSERT_DOUBLE_EQ(vd1, 5.3);
  ASSERT_DOUBLE_EQ(vd2, 2.8);

  const auto cvd = vd;
  const auto &cv0 = cvd[0];
  const auto &cv1 = cvd[1];
  const auto &cv2 = cvd[2];
  ASSERT_EQ(&cv0, cvd.begin() + 0);
  ASSERT_EQ(&cv1, cvd.begin() + 1);
  ASSERT_EQ(&cv2, cvd.begin() + 2);

  auto v = vd;
  auto &v0 = v[0];
  auto &v1 = v[1];
  auto &v2 = v[2];
  ASSERT_EQ(&v0, v.begin() + 0);
  ASSERT_EQ(&v1, v.begin() + 1);
  ASSERT_EQ(&v2, v.begin() + 2);
}

TEST(Vector3Test, ReadFieldTest) {
  const Vec3d cvd{1.2, 8.9, 2.5};
  ASSERT_DOUBLE_EQ(cvd.x, 1.2);
  ASSERT_DOUBLE_EQ(cvd.r, 1.2);
  ASSERT_DOUBLE_EQ(cvd.y, 8.9);
  ASSERT_DOUBLE_EQ(cvd.g, 8.9);
  ASSERT_DOUBLE_EQ(cvd.z, 2.5);
  ASSERT_DOUBLE_EQ(cvd.b, 2.5);
}

TEST(Vector3Test, WriteFieldTest) {
  Vec3d cvd{1.2, 8.9, 2.5};
  cvd.x = 3.4;
  cvd.y = 2.3;
  cvd.z = 2.3;
  ASSERT_DOUBLE_EQ(cvd.x, 3.4);
  ASSERT_DOUBLE_EQ(cvd.y, 2.3);
  ASSERT_DOUBLE_EQ(cvd.z, 2.3);
  ASSERT_DOUBLE_EQ(cvd.r, 3.4);
  ASSERT_DOUBLE_EQ(cvd.g, 2.3);
  ASSERT_DOUBLE_EQ(cvd.b, 2.3);
}

TEST(Vector3Test, xyTest) {
  Vec3d cvd{1.2, 8.9, 2.5};
  Vec2d v2 = cvd.xy();
  ASSERT_DOUBLE_EQ(v2.x, 1.2);
  ASSERT_DOUBLE_EQ(v2.y, 8.9);
}

TEST(Vector3Test, xyzTest) {
  Vec3d cvd{1.2, 8.9, 2.5};
  Vec3d v3 = cvd.xyz();
  ASSERT_DOUBLE_EQ(v3.x, cvd.x);
  ASSERT_DOUBLE_EQ(v3.y, cvd.y);
  ASSERT_DOUBLE_EQ(v3.z, cvd.z);
}

TEST(Vector3Test, rgTest) {
  Vec3d cvd{1.2, 8.9, 2.5};
  Vec2d v2 = cvd.rg();
  ASSERT_DOUBLE_EQ(v2.r, 1.2);
  ASSERT_DOUBLE_EQ(v2.g, 8.9);
}

TEST(Vector3Test, rgbTest) {
  Vec3d cvd{1.2, 8.9, 2.5};
  Vec3d v3 = cvd.rgb();
  ASSERT_DOUBLE_EQ(v3.r, cvd.r);
  ASSERT_DOUBLE_EQ(v3.g, cvd.g);
  ASSERT_DOUBLE_EQ(v3.b, cvd.b);
}


// // TEST(Vector3Test, PreIncrementOperatorTest) {
// //   Vec3i vi{1, 2};
// //   ASSERT_EQ(&(++vi), &vi);
// //   ASSERT_EQ(vi[0], 2);
// //   ASSERT_EQ(vi[1], 3);
// // }
// //
// // TEST(Vector3Test, PostIncrementOperatorTest) {
// //   Vec3i vi{1, 2};
// //   ASSERT_EQ(vi++, Vec3i(1, 2));
// //   ASSERT_EQ(vi[0], 2);
// //   ASSERT_EQ(vi[1], 3);
// // }

TEST(Vector3Test, AdditionAssignmentOperatorTest) {
  // Vec3d v1{1.2, 3.4};
  // ASSERT_EQ(&(v1 += 5), &v1);
  // ASSERT_DOUBLE_EQ(v1[0], 1.2 + 5);
  // ASSERT_DOUBLE_EQ(v1[1], 3.4 + 5);

  Vec3d v3{1.2, 3.4, 2.5};
  ASSERT_EQ(&(v3 += Vec3d(5.0, 6.0, 2.5)), &v3);
  ASSERT_DOUBLE_EQ(v3[0], 1.2 + 5.0);
  ASSERT_DOUBLE_EQ(v3[1], 3.4 + 6.0);
}

// // TEST(Vector3Test, SubtractionAssignmentOperatorTest) {
// //   // Vec3d v1{3.2, 3.7};
// //   // ASSERT_EQ(&(v1 -= 1), &v1);
// //   // ASSERT_DOUBLE_EQ(v1[0], 3.2 - 1);
// //   // ASSERT_DOUBLE_EQ(v1[1], 3.7 - 1);
// //
// //   Vec3d v3{8.9, 9.0};
// //   ASSERT_EQ(&(v3 -= Vec3i(5, 6)), &v3);
// //   ASSERT_DOUBLE_EQ(v3[0], 8.9 - 5);
// //   ASSERT_DOUBLE_EQ(v3[1], 9.0 - 6);
// // }
//
TEST(Vector3Test, MultiplicationAssignmentOperatorTest) {
  Vec3d v1{2.3, 2.4, 2.5};
  ASSERT_EQ(&(v1 *= 2), &v1);
  ASSERT_DOUBLE_EQ(v1[0], 2.3 * 2);
  ASSERT_DOUBLE_EQ(v1[1], 2.4 * 2);

  // Vec3d v3{8.9, 9.0};
  // ASSERT_EQ(&(v3 *= Vec3i(5, 6)), &v3);
  // ASSERT_DOUBLE_EQ(v3[0], 8.9 * 5);
  // ASSERT_DOUBLE_EQ(v3[1], 9.0 * 6);
}
//
TEST(Vector3Test, DivisionAssignmentOperatorTest) {
  Vec3d v1{2.3, 2.4, 2.5};
  ASSERT_EQ(&(v1 /= 2), &v1);
  ASSERT_DOUBLE_EQ(v1[0], 2.3 / 2);
  ASSERT_DOUBLE_EQ(v1[1], 2.4 / 2);

  // Vec3d v3{8.9, 9.0};
  // ASSERT_EQ(&(v3 /= Vec3i(5, 6)), &v3);
  // ASSERT_DOUBLE_EQ(v3[0], 8.9 / 5);
  // ASSERT_DOUBLE_EQ(v3[1], 9.0 / 6);
}

TEST(Vector3Test, AdditionOperatorTest) {
  // constexpr auto v1 = 1 + Vec3d(2.3, 4.5);
  // ASSERT_DOUBLE_EQ(v1[0], 1 + 2.3);
  // ASSERT_DOUBLE_EQ(v1[1], 1 + 4.5);
  //
  // constexpr auto v3 = Vec3d(1.2, 3.4) + 5;
  // ASSERT_DOUBLE_EQ(v3[0], 1.2 + 5);
  // ASSERT_DOUBLE_EQ(v3[1], 3.4 + 5);

  constexpr auto v3 = Vec3d(1.2, 3.4, 2.5) + Vec3d(5.0, 6.0, 2.5);
  ASSERT_DOUBLE_EQ(v3[0], 1.2 + 5);
  ASSERT_DOUBLE_EQ(v3[1], 3.4 + 6);
}

TEST(Vector3Test, SubtractionOperatorTest) {
  // constexpr auto v1 = 1 - Vec3d(2.3, 4.5);
  // ASSERT_DOUBLE_EQ(v1[0], 1 - 2.3);
  // ASSERT_DOUBLE_EQ(v1[1], 1 - 4.5);
  //
  // constexpr auto v3 = Vec3d(1.2, 3.4) - 5;
  // ASSERT_DOUBLE_EQ(v3[0], 1.2 - 5);
  // ASSERT_DOUBLE_EQ(v3[1], 3.4 - 5);

  constexpr auto v3 = Vec3d(1.2, 3.4, 2.5) - Vec3d(5.0, 6.0, 2.5);
  ASSERT_DOUBLE_EQ(v3[0], 1.2 - 5.0);
  ASSERT_DOUBLE_EQ(v3[1], 3.4 - 6.0);
}

TEST(Vector3Test, MultiplicationOperatorTest) {
  constexpr auto v1 = 1.0 * Vec3d(2.3, 4.5, 2.5);
  ASSERT_DOUBLE_EQ(v1[0], 1.0 * 2.3);
  ASSERT_DOUBLE_EQ(v1[1], 1.0 * 4.5);

  constexpr auto v3 = Vec3d(1.2, 3.4, 2.5) * 5.0;
  ASSERT_DOUBLE_EQ(v3[0], 1.2 * 5.0);
  ASSERT_DOUBLE_EQ(v3[1], 3.4 * 5.0);

  // constexpr auto v3 = Vec3d(1.2, 3.4) * Vec3i(5, 6);
  // ASSERT_DOUBLE_EQ(v3[0], 1.2 * 5);
  // ASSERT_DOUBLE_EQ(v3[1], 3.4 * 6);
}
//
TEST(Vector3Test, DivisionOperatorTest) {
  constexpr auto v1 = 1.0 / Vec3d{2.3, 4.5, 2.5};
  ASSERT_DOUBLE_EQ(v1[0], 1.0 / 2.3);
  ASSERT_DOUBLE_EQ(v1[1], 1.0 / 4.5);

  constexpr auto v3 = Vec3d{1.2, 3.4, 2.5} / 5.0;
  ASSERT_DOUBLE_EQ(v3[0], 1.2 / 5.0);
  ASSERT_DOUBLE_EQ(v3[1], 3.4 / 5.0);

  // constexpr auto v3 = Vec3d(1.2, 3.4) / Vec3d(5.0, 6.0);
  // ASSERT_DOUBLE_EQ(v3[0], 1.2 / 5);
  // ASSERT_DOUBLE_EQ(v3[1], 3.4 / 6);
}

TEST(Vector3Test, EqualityTest) {
  auto v1 = Vec3d{1.2, 3.4, 2.5};
  auto v2 = Vec3d{1.2, 2.4, 2.5};
  auto v3 = Vec3d{1.2, 3.4, 2.5};
  ASSERT_TRUE(v1 == v3);
  ASSERT_TRUE(v2 != v3);
}

TEST(Vector3Test, VectorDotProductTest) {
  constexpr auto x = dot(Vec3d{1.2, 3.4, 2.5}, Vec3d{7, 8, 9});
  ASSERT_DOUBLE_EQ(x, 1.2 * 7 + 3.4 * 8 + 2.5 * 9);
}

TEST(Vector3Test, LengthProductTest) {
  ASSERT_DOUBLE_EQ(length(Vec3d{1.2, 3.4, 2.5}),
                   std::sqrt(length_squared(Vec3d{1.2, 3.4, 2.5})));

  constexpr auto x = dot(Vec3d(1.2, 3.4, 2.5), Vec3d(7, 8, 2.5));
  ASSERT_DOUBLE_EQ(x, 1.2 * 7 + 3.4 * 8 + 2.5 * 2.5);
}

TEST(Vector3Test, LengthSquaredProductTest) {
  constexpr auto x = length_squared(Vec3d(1.2, 3.4, 2.5));
  ASSERT_DOUBLE_EQ(x, 1.2 * 1.2 + 3.4 * 3.4 + 2.5 * 2.5);
}

TEST(Vector3Test, NormalizeTest) {
  const Vec3d v(1.2, 3.4, 2.5);
  ASSERT_EQ(normalize(v), v * (1 / length(v)));
}
