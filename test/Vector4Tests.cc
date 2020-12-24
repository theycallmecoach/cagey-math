#include "gtest/gtest.h"
#include <cagey-math/Vector2.hh>
#include <cagey-math/Vector4.hh>
#include <cagey-math/VectorFunc.hh>
#include <cstdint>

using namespace cagey::math;

TEST(Vector4Test, Vector4SizeTest)
{
  ASSERT_EQ(sizeof(Vector4<short>), sizeof(short[4]));
  ASSERT_EQ(sizeof(Vector4f), sizeof(float[4]));
  ASSERT_EQ(sizeof(Vector4d), sizeof(double[4]));
  ASSERT_EQ(sizeof(Vector4i), sizeof(int[4]));
  ASSERT_EQ(sizeof(Vector4u), sizeof(unsigned int[4]));
}

TEST(Vector4Test, Vector4AlignTest)
{
  ASSERT_EQ(alignof(Vector4<short>), alignof(short[4]));
  ASSERT_EQ(alignof(Vector4f), alignof(float[4]));
  ASSERT_EQ(alignof(Vector4d), alignof(double[4]));
  ASSERT_EQ(alignof(Vector4i), alignof(int[4]));
  ASSERT_EQ(alignof(Vector4u), alignof(unsigned int[4]));
}

TEST(Vector4Test, Vector4ComponentTypeTest)
{
  ASSERT_EQ((std::is_same<typename Vector4<short>::ElementType, short>::value), true);
  ASSERT_EQ((std::is_same<typename Vector4<float>::ElementType, float>::value), true);
  ASSERT_EQ((std::is_same<typename Vector4<double>::ElementType, double>::value), true);
  ASSERT_EQ((std::is_same<typename Vector4<int>::ElementType, int>::value), true);
  ASSERT_EQ((std::is_same<typename Vector4<unsigned int>::ElementType, unsigned int>::value), true);
}

TEST(Vector4Test, Vector4ComponentCountTest)
{
  constexpr auto v4s = Vector4<short>::Size;
  constexpr auto v4f = Vector4f::Size;
  constexpr auto v4d = Vector4d::Size;
  constexpr auto v4i = Vector4i::Size;
  constexpr auto v4u = Vector4u::Size;
  ASSERT_EQ(v4s, 4);
  ASSERT_EQ(v4f, 4);
  ASSERT_EQ(v4d, 4);
  ASSERT_EQ(v4i, 4);
  ASSERT_EQ(v4u, 4);
}

TEST(Vector4Test, DefaultConstructorTest)
{
  Vector4f v;
  ASSERT_EQ(sizeof(v), sizeof(float[4]));
}

TEST(Vector4Test, ScalarConstructorTest)
{
  constexpr Vector4d v{4.8};
  ASSERT_DOUBLE_EQ(v[0], 4.8);
  ASSERT_DOUBLE_EQ(v[1], 4.8);
  ASSERT_DOUBLE_EQ(v[2], 4.8);
}

TEST(Vector4Test, ComponentConstructorTest)
{
  constexpr Vector4d v{1.3, 4.8, 5.6, 6.7};
  ASSERT_DOUBLE_EQ(v[0], 1.3);
  ASSERT_DOUBLE_EQ(v[1], 4.8);
  ASSERT_DOUBLE_EQ(v[2], 5.6);
  ASSERT_DOUBLE_EQ(v[3], 6.7);
}

TEST(Vector4Test, Vector2ConstructorTest)
{
  constexpr Vector4d v{{1.2, 4.8, 5.6}, 6.7};
  ASSERT_DOUBLE_EQ(v[0], 1.2);
  ASSERT_DOUBLE_EQ(v[1], 4.8);
  ASSERT_DOUBLE_EQ(v[2], 5.6);
  ASSERT_DOUBLE_EQ(v[3], 6.7);
}

// TEST(Vector4Test, TruncateConstructorTest)
// {
//   constexpr Vec4d v{1.2, 4.8, 5.6, 6.7};
//   ASSERT_DOUBLE_EQ(v[0], 1.2);
//   ASSERT_DOUBLE_EQ(v[1], 4.8);
//   ASSERT_DOUBLE_EQ(v[2], 5.6);
// }

TEST(Vector4Test, ExplicitConversionConstructorTest)
{
  constexpr Vector4d vd{4.8f, 5.6f, 3.8f, 9.7f};
  constexpr Vector4f vf{vd};
  ASSERT_DOUBLE_EQ(vf[0], 4.8f);
  ASSERT_DOUBLE_EQ(vf[1], 5.6f);
  ASSERT_DOUBLE_EQ(vf[2], 3.8f);
  ASSERT_DOUBLE_EQ(vf[3], 9.7f);
}

// // TEST(Vector4Test, ImplicitConversionConstructorTest) {
// //   constexpr Vector4f vf{4.8f, 5.6f};
// //   constexpr Vector4d vd = vf;
// //   ASSERT_DOUBLE_EQ(vd[0], 4.8f);
// //   ASSERT_DOUBLE_EQ(vd[1], 5.6f);
// // }
TEST(Vector4Test, BeginTest)
{
  const Vector4d cvd{1.2};
  using std::begin;
  const double *cdata = begin(cvd);
  ASSERT_EQ(cdata, static_cast<const void *>(&cvd));
}

TEST(Vector4Test, EndTest)
{
  using std::end;
  constexpr Vector4d v{4.8, 5.6, 3.8, 4.8};
  ASSERT_EQ(end(v), (&v[3] + 1));
}

TEST(Vector4Test, ZeroTest)
{
  constexpr auto v = Vector4f::zero();
  ASSERT_EQ(v, Vector4f{0.0f});
}

TEST(Vector4Test, XAxisTest)
{
  constexpr auto v = Vector4f::xAxis();
  ASSERT_EQ(v, Vector4f(1.0f, 0.0f, 0.0f, 0.0f));
}

TEST(Vector4Test, YAxisTest)
{
  constexpr auto v = Vector4f::yAxis();
  ASSERT_EQ(v, Vector4f(0.0f, 1.0f, 0.0f, 0.0f));
}

TEST(Vector4Test, ArrayIndexOperatorTest)
{
  using std::begin;
  constexpr Vector4d vd{1.3, 5.3, 2.8, 8.9};
  auto vd0 = vd[0];
  auto vd1 = vd[1];
  auto vd2 = vd[2];
  auto vd3 = vd[3];
  ASSERT_DOUBLE_EQ(vd0, 1.3);
  ASSERT_DOUBLE_EQ(vd1, 5.3);
  ASSERT_DOUBLE_EQ(vd2, 2.8);
  ASSERT_DOUBLE_EQ(vd3, 8.9);

  const auto cvd = vd;
  const auto &cv0 = cvd[0];
  const auto &cv1 = cvd[1];
  const auto &cv2 = cvd[2];
  const auto &cv3 = cvd[3];
  ASSERT_EQ(&cv0, begin(cvd) + 0);
  ASSERT_EQ(&cv1, begin(cvd) + 1);
  ASSERT_EQ(&cv2, begin(cvd) + 2);
  ASSERT_EQ(&cv3, begin(cvd) + 3);

  auto v = vd;
  auto &v0 = v[0];
  auto &v1 = v[1];
  auto &v2 = v[2];
  auto &v3 = v[3];
  ASSERT_EQ(&v0, begin(v) + 0);
  ASSERT_EQ(&v1, begin(v) + 1);
  ASSERT_EQ(&v2, begin(v) + 2);
  ASSERT_EQ(&v3, begin(v) + 3);
}

TEST(Vector4Test, ReadFieldTest)
{
  const Vector4d cvd{1.2, 8.9, 2.5, 8.9};
  ASSERT_DOUBLE_EQ(cvd.x, 1.2);
  ASSERT_DOUBLE_EQ(cvd.r, 1.2);
  ASSERT_DOUBLE_EQ(cvd.y, 8.9);
  ASSERT_DOUBLE_EQ(cvd.g, 8.9);
  ASSERT_DOUBLE_EQ(cvd.z, 2.5);
  ASSERT_DOUBLE_EQ(cvd.b, 2.5);
  ASSERT_DOUBLE_EQ(cvd.w, 8.9);
  ASSERT_DOUBLE_EQ(cvd.a, 8.9);
}

TEST(Vector4Test, WriteFieldTest)
{
  Vector4d cvd{1.2, 8.9, 2.5, 8.9};
  cvd.x = 3.4;
  cvd.y = 2.3;
  cvd.z = 2.3;
  cvd.w = 2.5;
  ASSERT_DOUBLE_EQ(cvd.x, 3.4);
  ASSERT_DOUBLE_EQ(cvd.y, 2.3);
  ASSERT_DOUBLE_EQ(cvd.z, 2.3);
  ASSERT_DOUBLE_EQ(cvd.w, 2.5);
  ASSERT_DOUBLE_EQ(cvd.r, 3.4);
  ASSERT_DOUBLE_EQ(cvd.g, 2.3);
  ASSERT_DOUBLE_EQ(cvd.b, 2.3);
  ASSERT_DOUBLE_EQ(cvd.a, 2.5);
}

TEST(Vector4Test, xyTest)
{
  Vector4d cvd{1.2, 8.9, 2.5, 7.8};
  Vector2d v2 = cvd.xy();
  ASSERT_DOUBLE_EQ(v2.x, 1.2);
  ASSERT_DOUBLE_EQ(v2.y, 8.9);
}

TEST(Vector4Test, xyzTest)
{
  Vector4d cvd{1.2, 8.9, 2.5, 7.9};
  Vector3d v3 = cvd.xyz();
  ASSERT_DOUBLE_EQ(v3.x, cvd.x);
  ASSERT_DOUBLE_EQ(v3.y, cvd.y);
  ASSERT_DOUBLE_EQ(v3.z, cvd.z);
}

TEST(Vector4Test, rgTest)
{
  Vector4d cvd{1.2, 8.9, 2.5, 8.9};
  Vector2d v2 = cvd.rg();
  ASSERT_DOUBLE_EQ(v2.r, 1.2);
  ASSERT_DOUBLE_EQ(v2.g, 8.9);
}

TEST(Vector4Test, rgbTest)
{
  Vector4d cvd{1.2, 8.9, 2.5, 3.5};
  Vector3d v3 = cvd.rgb();
  ASSERT_DOUBLE_EQ(v3.r, cvd.r);
  ASSERT_DOUBLE_EQ(v3.g, cvd.g);
  ASSERT_DOUBLE_EQ(v3.b, cvd.b);
}

// // TEST(Vector4Test, PreIncrementOperatorTest) {
// //   Vector4i vi{1, 2};
// //   ASSERT_EQ(&(++vi), &vi);
// //   ASSERT_EQ(vi[0], 2);
// //   ASSERT_EQ(vi[1], 3);
// // }
// //
// // TEST(Vector4Test, PostIncrementOperatorTest) {
// //   Vector4i vi{1, 2};
// //   ASSERT_EQ(vi++, Vector4i(1, 2));
// //   ASSERT_EQ(vi[0], 2);
// //   ASSERT_EQ(vi[1], 3);
// // }

TEST(Vector4Test, AdditionAssignmentOperatorTest)
{
  // Vector4d v1{1.2, 3.4};
  // ASSERT_EQ(&(v1 += 5), &v1);
  // ASSERT_DOUBLE_EQ(v1[0], 1.2 + 5);
  // ASSERT_DOUBLE_EQ(v1[1], 3.4 + 5);

  Vector4d v4{1.2, 3.4, 2.5, 4.6};
  ASSERT_EQ(&(v4 += Vector4d(5.0, 6.0, 2.5, 6.7)), &v4);
  ASSERT_DOUBLE_EQ(v4[0], 1.2 + 5.0);
  ASSERT_DOUBLE_EQ(v4[1], 3.4 + 6.0);
}

// // TEST(Vector4Test, SubtractionAssignmentOperatorTest) {
// //   // Vector4d v1{3.2, 3.7};
// //   // ASSERT_EQ(&(v1 -= 1), &v1);
// //   // ASSERT_DOUBLE_EQ(v1[0], 3.2 - 1);
// //   // ASSERT_DOUBLE_EQ(v1[1], 3.7 - 1);
// //
// //   Vector4d v3{8.9, 9.0};
// //   ASSERT_EQ(&(v3 -= Vector4i(5, 6)), &v3);
// //   ASSERT_DOUBLE_EQ(v3[0], 8.9 - 5);
// //   ASSERT_DOUBLE_EQ(v3[1], 9.0 - 6);
// // }
//
TEST(Vector4Test, MultiplicationAssignmentOperatorTest)
{
  Vector4d v1{2.3, 2.4, 2.5, 3.5};
  ASSERT_EQ(&(v1 *= 2), &v1);
  ASSERT_DOUBLE_EQ(v1[0], 2.3 * 2);
  ASSERT_DOUBLE_EQ(v1[1], 2.4 * 2);

  // Vector4d v3{8.9, 9.0};
  // ASSERT_EQ(&(v3 *= Vector4i(5, 6)), &v3);
  // ASSERT_DOUBLE_EQ(v3[0], 8.9 * 5);
  // ASSERT_DOUBLE_EQ(v3[1], 9.0 * 6);
}
//
TEST(Vector4Test, DivisionAssignmentOperatorTest)
{
  Vector4d v1{2.3, 2.4, 2.5, 5.7};
  ASSERT_EQ(&(v1 /= 2), &v1);
  ASSERT_DOUBLE_EQ(v1[0], 2.3 / 2);
  ASSERT_DOUBLE_EQ(v1[1], 2.4 / 2);

  // Vector4d v3{8.9, 9.0};
  // ASSERT_EQ(&(v3 /= Vector4i(5, 6)), &v3);
  // ASSERT_DOUBLE_EQ(v3[0], 8.9 / 5);
  // ASSERT_DOUBLE_EQ(v3[1], 9.0 / 6);
}

TEST(Vector4Test, AdditionOperatorTest)
{
  // constexpr auto v1 = 1 + Vector4d(2.3, 4.5);
  // ASSERT_DOUBLE_EQ(v1[0], 1 + 2.3);
  // ASSERT_DOUBLE_EQ(v1[1], 1 + 4.5);
  //
  // constexpr auto v3 = Vector4d(1.2, 3.4) + 5;
  // ASSERT_DOUBLE_EQ(v3[0], 1.2 + 5);
  // ASSERT_DOUBLE_EQ(v3[1], 3.4 + 5);

  constexpr auto v3 = Vector4d(1.2, 3.4, 2.5, 4.5) + Vector4d(5.0, 6.0, 2.5, 6.8);
  ASSERT_DOUBLE_EQ(v3[0], 1.2 + 5);
  ASSERT_DOUBLE_EQ(v3[1], 3.4 + 6);
}

TEST(Vector4Test, SubtractionOperatorTest)
{
  // constexpr auto v1 = 1 - Vector4d(2.3, 4.5);
  // ASSERT_DOUBLE_EQ(v1[0], 1 - 2.3);
  // ASSERT_DOUBLE_EQ(v1[1], 1 - 4.5);
  //
  // constexpr auto v3 = Vector4d(1.2, 3.4) - 5;
  // ASSERT_DOUBLE_EQ(v3[0], 1.2 - 5);
  // ASSERT_DOUBLE_EQ(v3[1], 3.4 - 5);

  auto v3 = Vector4d(1.2, 3.4, 2.5, 6.8) - Vector4d(5.0, 6.0, 2.5, 7.0);
  ASSERT_DOUBLE_EQ(v3[0], 1.2 - 5.0);
  ASSERT_DOUBLE_EQ(v3[1], 3.4 - 6.0);
}

TEST(Vector4Test, MultiplicationOperatorTest)
{
  constexpr auto v1 = 1.0 * Vector4d(2.3, 4.5, 2.5, 6.7);
  ASSERT_DOUBLE_EQ(v1[0], 1.0 * 2.3);
  ASSERT_DOUBLE_EQ(v1[1], 1.0 * 4.5);

  constexpr auto v3 = Vector4d(1.2, 3.4, 2.5, 8.0) * 5.0;
  ASSERT_DOUBLE_EQ(v3[0], 1.2 * 5.0);
  ASSERT_DOUBLE_EQ(v3[1], 3.4 * 5.0);

  // constexpr auto v3 = Vector4d(1.2, 3.4) * Vector4i(5, 6);
  // ASSERT_DOUBLE_EQ(v3[0], 1.2 * 5);
  // ASSERT_DOUBLE_EQ(v3[1], 3.4 * 6);
}
//
TEST(Vector4Test, DivisionOperatorTest)
{
  constexpr auto v1 = 1.0 / Vector4d{2.3, 4.5, 2.5, 6.7};
  ASSERT_DOUBLE_EQ(v1[0], 1.0 / 2.3);
  ASSERT_DOUBLE_EQ(v1[1], 1.0 / 4.5);

  constexpr auto v3 = Vector4d{1.2, 3.4, 2.5, 6.8} / 5.0;
  ASSERT_DOUBLE_EQ(v3[0], 1.2 / 5.0);
  ASSERT_DOUBLE_EQ(v3[1], 3.4 / 5.0);

  // constexpr auto v3 = Vector4d(1.2, 3.4) / Vector4d(5.0, 6.0);
  // ASSERT_DOUBLE_EQ(v3[0], 1.2 / 5);
  // ASSERT_DOUBLE_EQ(v3[1], 3.4 / 6);
}

TEST(Vector4Test, EqualityTest)
{
  auto v1 = Vector4d{1.2, 3.4, 2.5, 3.7};
  auto v2 = Vector4d{1.2, 2.4, 2.5, 3.7};
  auto v3 = Vector4d{1.2, 3.4, 2.5, 3.7};
  ASSERT_TRUE(v1 == v3);
  ASSERT_TRUE(v2 != v3);
}

TEST(Vector4Test, VectorDotProductTest)
{
  constexpr auto x = dot(Vector4d{1.2, 3.4, 2.5, 3.4}, Vector4d{7, 8, 9, 10});
  ASSERT_DOUBLE_EQ(x, 1.2 * 7 + 3.4 * 8 + 2.5 * 9 + 3.4 * 10);
}

TEST(Vector4Test, LengthProductTest)
{
  ASSERT_DOUBLE_EQ(length(Vector4d{1.2, 3.4, 2.5, 4.7}),
                   std::sqrt(lengthSquared(Vector4d{1.2, 3.4, 2.5, 4.7})));

  constexpr auto x = dot(Vector4d(1.2, 3.4, 2.5, 2.5), Vector4d(7, 8, 2.5, 2.5));
  ASSERT_DOUBLE_EQ(x, 1.2 * 7 + 3.4 * 8 + 2.5 * 2.5 + 2.5 * 2.5);
}

TEST(Vector4Test, LengthSquaredProductTest)
{
  constexpr auto x = lengthSquared(Vector4d(1.2, 3.4, 2.5, 2.6));
  ASSERT_DOUBLE_EQ(x, 1.2 * 1.2 + 3.4 * 3.4 + 2.5 * 2.5 + 2.6 * 2.6);
}

TEST(Vector4Test, NormalizeTest)
{
  const Vector4d v(1.2, 3.4, 2.5, 2.5);
  ASSERT_EQ(normalize(v), v * (1 / length(v)));
}
