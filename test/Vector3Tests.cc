#include "gtest/gtest.h"
#include <cagey-math/Vector2.hh>
#include <cagey-math/Vector3.hh>
#include <cagey-math/VectorFunc.hh>
#include <cstdint>

using namespace cagey::math;

TEST(Vector3Test, Vector3SizeTest)
{
  ASSERT_EQ(sizeof(Vector3<short>), sizeof(short[3]));
  ASSERT_EQ(sizeof(Vector3f), sizeof(float[3]));
  ASSERT_EQ(sizeof(Vector3d), sizeof(double[3]));
  ASSERT_EQ(sizeof(Vector3i), sizeof(int[3]));
  ASSERT_EQ(sizeof(Vector3u), sizeof(unsigned int[3]));
}

TEST(Vector3Test, Vector3AlignTest)
{
  ASSERT_EQ(alignof(Vector3<short>), alignof(short[3]));
  ASSERT_EQ(alignof(Vector3f), alignof(float[3]));
  ASSERT_EQ(alignof(Vector3d), alignof(double[3]));
  ASSERT_EQ(alignof(Vector3i), alignof(int[3]));
  ASSERT_EQ(alignof(Vector3u), alignof(unsigned int[3]));
}

TEST(Vector3Test, Vector3ComponentTypeTest)
{
  ASSERT_EQ((std::is_same<typename Vector3<short>::ElementType, short>::value), true);
  ASSERT_EQ((std::is_same<typename Vector3<float>::ElementType, float>::value), true);
  ASSERT_EQ((std::is_same<typename Vector3<double>::ElementType, double>::value), true);
  ASSERT_EQ((std::is_same<typename Vector3<int>::ElementType, int>::value), true);
  ASSERT_EQ((std::is_same<typename Vector3<unsigned int>::ElementType, unsigned int>::value), true);
}

TEST(Vector3Test, Vector3ComponentCountTest)
{
  constexpr auto v3s = Vector3<short>::Size;
  constexpr auto v3f = Vector3f::Size;
  constexpr auto v3d = Vector3d::Size;
  constexpr auto v3i = Vector3i::Size;
  constexpr auto v3u = Vector3u::Size;
  ASSERT_EQ(v3s, 3);
  ASSERT_EQ(v3f, 3);
  ASSERT_EQ(v3d, 3);
  ASSERT_EQ(v3i, 3);
  ASSERT_EQ(v3u, 3);
}

TEST(Vector3Test, DefaultConstructorTest)
{
  Vector3f v;
  ASSERT_EQ(sizeof(v), sizeof(float[3]));
}

TEST(Vector3Test, ScalarConstructorTest)
{
  constexpr Vector3d v{4.8};
  ASSERT_DOUBLE_EQ(v[0], 4.8);
  ASSERT_DOUBLE_EQ(v[1], 4.8);
  ASSERT_DOUBLE_EQ(v[2], 4.8);
}

TEST(Vector3Test, ComponentConstructorTest)
{
  constexpr Vector3d v{1.3, 4.8, 5.6};
  ASSERT_DOUBLE_EQ(v[0], 1.3);
  ASSERT_DOUBLE_EQ(v[1], 4.8);
  ASSERT_DOUBLE_EQ(v[2], 5.6);
}

TEST(Vector3Test, Vector2ConstructorTest)
{
  constexpr Vector3d v{{1.2, 4.8}, 5.6};
  ASSERT_DOUBLE_EQ(v[0], 1.2);
  ASSERT_DOUBLE_EQ(v[1], 4.8);
  ASSERT_DOUBLE_EQ(v[2], 5.6);
}

// TEST(Vector3Test, TruncateConstructorTest)
// {
//   constexpr Vec4d v{1.2, 4.8, 5.6, 6.7};
//   ASSERT_DOUBLE_EQ(v[0], 1.2);
//   ASSERT_DOUBLE_EQ(v[1], 4.8);
//   ASSERT_DOUBLE_EQ(v[2], 5.6);
// }

TEST(Vector3Test, ExplicitConversionConstructorTest)
{
  constexpr Vector3d vd{4.8f, 5.6f, 3.8f};
  constexpr Vector3f vf{vd};
  ASSERT_DOUBLE_EQ(vf[0], 4.8f);
  ASSERT_DOUBLE_EQ(vf[1], 5.6f);
  ASSERT_DOUBLE_EQ(vf[2], 3.8f);
}

// // TEST(Vector3Test, ImplicitConversionConstructorTest) {
// //   constexpr Vector3f vf{4.8f, 5.6f};
// //   constexpr Vector3d vd = vf;
// //   ASSERT_DOUBLE_EQ(vd[0], 4.8f);
// //   ASSERT_DOUBLE_EQ(vd[1], 5.6f);
// // }
TEST(Vector3Test, BeginTest)
{
  const Vector3d cvd{1.2};
  using std::begin;
  const double *cdata = begin(cvd);
  ASSERT_EQ(cdata, static_cast<const void *>(&cvd));
}

TEST(Vector3Test, EndTest)
{
  using std::end;
  constexpr Vector3d v{4.8, 5.6, 3.8};
  ASSERT_EQ(end(v), (&v[2] + 1));
}

TEST(Vector3Test, ZeroTest)
{
  constexpr auto v = Vector3f::zero();
  ASSERT_EQ(v, Vector3f{0.0f});
}

TEST(Vector3Test, XAxisTest)
{
  constexpr auto v = Vector3f::xAxis();
  ASSERT_EQ(v, Vector3f(1.0f, 0.0f, 0.0f));
}

TEST(Vector3Test, YAxisTest)
{
  constexpr auto v = Vector3f::yAxis();
  ASSERT_EQ(v, Vector3f(0.0f, 1.0f, 0.0f));
}

TEST(Vector3Test, ArrayIndexOperatorTest)
{
  using std::begin;
  constexpr Vector3d vd{1.3, 5.3, 2.8};
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
  ASSERT_EQ(&cv0, begin(cvd) + 0);
  ASSERT_EQ(&cv1, begin(cvd) + 1);
  ASSERT_EQ(&cv2, begin(cvd) + 2);

  auto v = vd;
  auto &v0 = v[0];
  auto &v1 = v[1];
  auto &v2 = v[2];
  ASSERT_EQ(&v0, begin(v) + 0);
  ASSERT_EQ(&v1, begin(v) + 1);
  ASSERT_EQ(&v2, begin(v) + 2);
}

TEST(Vector3Test, ReadFieldTest)
{
  const Vector3d cvd{1.2, 8.9, 2.5};
  ASSERT_DOUBLE_EQ(cvd.x, 1.2);
  ASSERT_DOUBLE_EQ(cvd.r, 1.2);
  ASSERT_DOUBLE_EQ(cvd.y, 8.9);
  ASSERT_DOUBLE_EQ(cvd.g, 8.9);
  ASSERT_DOUBLE_EQ(cvd.z, 2.5);
  ASSERT_DOUBLE_EQ(cvd.b, 2.5);
}

TEST(Vector3Test, WriteFieldTest)
{
  Vector3d cvd{1.2, 8.9, 2.5};
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

TEST(Vector3Test, CopyAssignmentOperator)
{
  Vector3d cvd{1, 8, 7};
  Vector3d cvd2{4, 5, 9};
  cvd2 = cvd;
  ASSERT_TRUE(cvd == cvd2);
}

TEST(Vector3Test, xyTest)
{
  Vector3d cvd{1.2, 8.9, 2.5};
  Vector2d v2 = cvd.xy();
  ASSERT_DOUBLE_EQ(v2.x, 1.2);
  ASSERT_DOUBLE_EQ(v2.y, 8.9);
}

TEST(Vector3Test, xyzTest)
{
  Vector3d cvd{1.2, 8.9, 2.5};
  Vector3d v3 = cvd.xyz();
  ASSERT_DOUBLE_EQ(v3.x, cvd.x);
  ASSERT_DOUBLE_EQ(v3.y, cvd.y);
  ASSERT_DOUBLE_EQ(v3.z, cvd.z);
}

TEST(Vector3Test, rgTest)
{
  Vector3d cvd{1.2, 8.9, 2.5};
  Vector2d v2 = cvd.rg();
  ASSERT_DOUBLE_EQ(v2.r, 1.2);
  ASSERT_DOUBLE_EQ(v2.g, 8.9);
}

TEST(Vector3Test, rgbTest)
{
  Vector3d cvd{1.2, 8.9, 2.5};
  Vector3d v3 = cvd.rgb();
  ASSERT_DOUBLE_EQ(v3.r, cvd.r);
  ASSERT_DOUBLE_EQ(v3.g, cvd.g);
  ASSERT_DOUBLE_EQ(v3.b, cvd.b);
}

// // TEST(Vector3Test, PreIncrementOperatorTest) {
// //   Vector3i vi{1, 2};
// //   ASSERT_EQ(&(++vi), &vi);
// //   ASSERT_EQ(vi[0], 2);
// //   ASSERT_EQ(vi[1], 3);
// // }
// //
// // TEST(Vector3Test, PostIncrementOperatorTest) {
// //   Vector3i vi{1, 2};
// //   ASSERT_EQ(vi++, Vector3i(1, 2));
// //   ASSERT_EQ(vi[0], 2);
// //   ASSERT_EQ(vi[1], 3);
// // }

TEST(Vector3Test, AdditionAssignmentOperatorTest)
{
  // Vector3d v1{1.2, 3.4};
  // ASSERT_EQ(&(v1 += 5), &v1);
  // ASSERT_DOUBLE_EQ(v1[0], 1.2 + 5);
  // ASSERT_DOUBLE_EQ(v1[1], 3.4 + 5);

  Vector3d v3{1.2, 3.4, 2.5};
  ASSERT_EQ(&(v3 += Vector3d(5.0, 6.0, 2.5)), &v3);
  ASSERT_DOUBLE_EQ(v3[0], 1.2 + 5.0);
  ASSERT_DOUBLE_EQ(v3[1], 3.4 + 6.0);
}

// // TEST(Vector3Test, SubtractionAssignmentOperatorTest) {
// //   // Vector3d v1{3.2, 3.7};
// //   // ASSERT_EQ(&(v1 -= 1), &v1);
// //   // ASSERT_DOUBLE_EQ(v1[0], 3.2 - 1);
// //   // ASSERT_DOUBLE_EQ(v1[1], 3.7 - 1);
// //
// //   Vector3d v3{8.9, 9.0};
// //   ASSERT_EQ(&(v3 -= Vector3i(5, 6)), &v3);
// //   ASSERT_DOUBLE_EQ(v3[0], 8.9 - 5);
// //   ASSERT_DOUBLE_EQ(v3[1], 9.0 - 6);
// // }
//
TEST(Vector3Test, MultiplicationAssignmentOperatorTest)
{
  Vector3d v1{2.3, 2.4, 2.5};
  ASSERT_EQ(&(v1 *= 2), &v1);
  ASSERT_DOUBLE_EQ(v1[0], 2.3 * 2);
  ASSERT_DOUBLE_EQ(v1[1], 2.4 * 2);

  // Vector3d v3{8.9, 9.0};
  // ASSERT_EQ(&(v3 *= Vector3i(5, 6)), &v3);
  // ASSERT_DOUBLE_EQ(v3[0], 8.9 * 5);
  // ASSERT_DOUBLE_EQ(v3[1], 9.0 * 6);
}
//
TEST(Vector3Test, DivisionAssignmentOperatorTest)
{
  Vector3d v1{2.3, 2.4, 2.5};
  ASSERT_EQ(&(v1 /= 2), &v1);
  ASSERT_DOUBLE_EQ(v1[0], 2.3 / 2);
  ASSERT_DOUBLE_EQ(v1[1], 2.4 / 2);

  // Vector3d v3{8.9, 9.0};
  // ASSERT_EQ(&(v3 /= Vector3i(5, 6)), &v3);
  // ASSERT_DOUBLE_EQ(v3[0], 8.9 / 5);
  // ASSERT_DOUBLE_EQ(v3[1], 9.0 / 6);
}

TEST(Vector3Test, AdditionOperatorTest)
{
  // constexpr auto v1 = 1 + Vector3d(2.3, 4.5);
  // ASSERT_DOUBLE_EQ(v1[0], 1 + 2.3);
  // ASSERT_DOUBLE_EQ(v1[1], 1 + 4.5);
  //
  // constexpr auto v3 = Vector3d(1.2, 3.4) + 5;
  // ASSERT_DOUBLE_EQ(v3[0], 1.2 + 5);
  // ASSERT_DOUBLE_EQ(v3[1], 3.4 + 5);

  constexpr auto v3 = Vector3d(1.2, 3.4, 2.5) + Vector3d(5.0, 6.0, 2.5);
  ASSERT_DOUBLE_EQ(v3[0], 1.2 + 5);
  ASSERT_DOUBLE_EQ(v3[1], 3.4 + 6);
}

TEST(Vector3Test, SubtractionOperatorTest)
{
  // constexpr auto v1 = 1 - Vector3d(2.3, 4.5);
  // ASSERT_DOUBLE_EQ(v1[0], 1 - 2.3);
  // ASSERT_DOUBLE_EQ(v1[1], 1 - 4.5);
  //
  // constexpr auto v3 = Vector3d(1.2, 3.4) - 5;
  // ASSERT_DOUBLE_EQ(v3[0], 1.2 - 5);
  // ASSERT_DOUBLE_EQ(v3[1], 3.4 - 5);

  auto v3 = Vector3d(1.2, 3.4, 2.5) - Vector3d(5.0, 6.0, 2.5);
  ASSERT_DOUBLE_EQ(v3[0], 1.2 - 5.0);
  ASSERT_DOUBLE_EQ(v3[1], 3.4 - 6.0);
}

TEST(Vector3Test, MultiplicationOperatorTest)
{
  constexpr auto v1 = 1.0 * Vector3d(2.3, 4.5, 2.5);
  ASSERT_DOUBLE_EQ(v1[0], 1.0 * 2.3);
  ASSERT_DOUBLE_EQ(v1[1], 1.0 * 4.5);

  constexpr auto v3 = Vector3d(1.2, 3.4, 2.5) * 5.0;
  ASSERT_DOUBLE_EQ(v3[0], 1.2 * 5.0);
  ASSERT_DOUBLE_EQ(v3[1], 3.4 * 5.0);

  // constexpr auto v3 = Vector3d(1.2, 3.4) * Vector3i(5, 6);
  // ASSERT_DOUBLE_EQ(v3[0], 1.2 * 5);
  // ASSERT_DOUBLE_EQ(v3[1], 3.4 * 6);
}
//
TEST(Vector3Test, DivisionOperatorTest)
{
  constexpr auto v1 = 1.0 / Vector3d{2.3, 4.5, 2.5};
  ASSERT_DOUBLE_EQ(v1[0], 1.0 / 2.3);
  ASSERT_DOUBLE_EQ(v1[1], 1.0 / 4.5);

  constexpr auto v3 = Vector3d{1.2, 3.4, 2.5} / 5.0;
  ASSERT_DOUBLE_EQ(v3[0], 1.2 / 5.0);
  ASSERT_DOUBLE_EQ(v3[1], 3.4 / 5.0);

  // constexpr auto v3 = Vector3d(1.2, 3.4) / Vector3d(5.0, 6.0);
  // ASSERT_DOUBLE_EQ(v3[0], 1.2 / 5);
  // ASSERT_DOUBLE_EQ(v3[1], 3.4 / 6);
}

TEST(Vector3Test, EqualityTest)
{
  auto v1 = Vector3d{1.2, 3.4, 2.5};
  auto v2 = Vector3d{1.2, 2.4, 2.5};
  auto v3 = Vector3d{1.2, 3.4, 2.5};
  ASSERT_TRUE(v1 == v3);
  ASSERT_TRUE(v2 != v3);
}

TEST(Vector3Test, VectorDotProductTest)
{
  constexpr auto x = dot(Vector3d{1.2, 3.4, 2.5}, Vector3d{7, 8, 9});
  ASSERT_DOUBLE_EQ(x, 1.2 * 7 + 3.4 * 8 + 2.5 * 9);
}

TEST(Vector3Test, LengthProductTest)
{
  ASSERT_DOUBLE_EQ(length(Vector3d{1.2, 3.4, 2.5}),
                   std::sqrt(lengthSquared(Vector3d{1.2, 3.4, 2.5})));

  constexpr auto x = dot(Vector3d(1.2, 3.4, 2.5), Vector3d(7, 8, 2.5));
  ASSERT_DOUBLE_EQ(x, 1.2 * 7 + 3.4 * 8 + 2.5 * 2.5);
}

TEST(Vector3Test, LengthSquaredProductTest)
{
  constexpr auto x = lengthSquared(Vector3d(1.2, 3.4, 2.5));
  ASSERT_DOUBLE_EQ(x, 1.2 * 1.2 + 3.4 * 3.4 + 2.5 * 2.5);
}

TEST(Vector3Test, NormalizeTest)
{
  const Vector3d v(1.2, 3.4, 2.5);
  ASSERT_EQ(normalize(v), v * (1 / length(v)));
}
