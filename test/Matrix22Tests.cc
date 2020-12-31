#include "gtest/gtest.h"
#include <cagey-math/Matrix22.hh>
#include <cagey-math/Vector2.hh>
#include <cagey-math/MatrixFunc.hh>
#include <cstdint>

using namespace cagey::math;

TEST(Matrix22Test, Matrix22SizeTest)
{
  ASSERT_EQ(sizeof(Matrix22<short>), sizeof(short[4]));
  ASSERT_EQ(sizeof(Matrix22f), sizeof(float[4]));
  ASSERT_EQ(sizeof(Matrix22d), sizeof(double[4]));
  ASSERT_EQ(sizeof(Matrix22i), sizeof(int[4]));
  ASSERT_EQ(sizeof(Matrix22u), sizeof(unsigned int[4]));
}

TEST(Matrix22Test, DefaultConstructorTest)
{
  Matrix22f m;
  ASSERT_EQ(sizeof(m), sizeof(float[4]));
}

TEST(Matrix22Test, SingleValueConstructorTest)
{
  Matrix22f m{1.0};
  ASSERT_FLOAT_EQ(m[0][0], 1.0f);
  ASSERT_FLOAT_EQ(m[0][1], 1.0f);
  ASSERT_FLOAT_EQ(m[1][0], 1.0f);
  ASSERT_FLOAT_EQ(m[1][1], 1.0f);

  Matrix22f m2{1.0f};
  ASSERT_FLOAT_EQ(m2[0][0], 1.0f);
  ASSERT_FLOAT_EQ(m2[0][1], 1.0f);
  ASSERT_FLOAT_EQ(m2[1][0], 1.0f);
  ASSERT_FLOAT_EQ(m2[1][1], 1.0f);

  Matrix22i m3{1};
  ASSERT_FLOAT_EQ(m3[0][0], 1);
  ASSERT_FLOAT_EQ(m3[0][1], 1);
  ASSERT_FLOAT_EQ(m3[1][0], 1);
  ASSERT_FLOAT_EQ(m3[1][1], 1);
}

TEST(Matrix22Test, FillTest)
{
  Matrix22f m = Matrix22f::fill(1.0f);
  ASSERT_FLOAT_EQ(m[0][0], 1.0f);
  ASSERT_FLOAT_EQ(m[0][1], 1.0f);
  ASSERT_FLOAT_EQ(m[1][0], 1.0f);
  ASSERT_FLOAT_EQ(m[1][1], 1.0f);

  Matrix22f m2 = Matrix22f::fill(1.0);
  ASSERT_FLOAT_EQ(m2[0][0], 1.0f);
  ASSERT_FLOAT_EQ(m2[0][1], 1.0f);
  ASSERT_FLOAT_EQ(m2[1][0], 1.0f);
  ASSERT_FLOAT_EQ(m2[1][1], 1.0f);

  Matrix22i m3 = Matrix22i::fill(1);
  ASSERT_EQ(m3[0][0], 1);
  ASSERT_EQ(m3[0][1], 1);
  ASSERT_EQ(m3[1][0], 1);
  ASSERT_EQ(m3[1][1], 1);
}

TEST(Matrix22Test, ZeroTest)
{
  Matrix22f m = Matrix22f::zero();
  ASSERT_FLOAT_EQ(m[0][0], 0.0f);
  ASSERT_FLOAT_EQ(m[0][1], 0.0f);
  ASSERT_FLOAT_EQ(m[1][0], 0.0f);
  ASSERT_FLOAT_EQ(m[1][1], 0.0f);

  Matrix22f m2 = Matrix22f::zero();
  ASSERT_FLOAT_EQ(m2[0][0], 0.0f);
  ASSERT_FLOAT_EQ(m2[0][1], 0.0f);
  ASSERT_FLOAT_EQ(m2[1][0], 0.0f);
  ASSERT_FLOAT_EQ(m2[1][1], 0.0f);

  Matrix22i m3 = Matrix22i::zero();
  ASSERT_EQ(m3[0][0], 0);
  ASSERT_EQ(m3[0][1], 0);
  ASSERT_EQ(m3[1][0], 0);
  ASSERT_EQ(m3[1][1], 0);
}

TEST(Matrix22Test, VectorConstructorTest)
{
  Matrix22f m{{1.0, 1.0}, {2.0, 2.0}};
  ASSERT_FLOAT_EQ(m[0][0], 1.0f);
  ASSERT_FLOAT_EQ(m[0][1], 1.0f);
  ASSERT_FLOAT_EQ(m[1][0], 2.0f);
  ASSERT_FLOAT_EQ(m[1][1], 2.0f);
}

TEST(Matrix22Test, ArrayConstructorTest)
{
  auto data = std::array<float, 4>{1.0f, 0.0f, 0.0f, 1.0f};
  Matrix22f m{data};

  ASSERT_FLOAT_EQ(m[0][0], 1.0f);
  ASSERT_FLOAT_EQ(m[0][1], 0.0f);
  ASSERT_FLOAT_EQ(m[1][0], 0.0f);
  ASSERT_FLOAT_EQ(m[1][1], 1.0f);
}

TEST(Matrix22Test, ElementConstructorTest)
{
  Matrix22f m{1.0f, 3.0f, 5.0f, 1.0f};

  ASSERT_FLOAT_EQ(m[0][0], 1.0f);
  ASSERT_FLOAT_EQ(m[0][1], 3.0f);
  ASSERT_FLOAT_EQ(m[1][0], 5.0f);
  ASSERT_FLOAT_EQ(m[1][1], 1.0f);
}

TEST(Matrix22Test, CopyConstructorTest)
{
  Matrix22f m = Matrix22f::identity();
  Matrix22f m1{m};
  ASSERT_TRUE(m1 == m);
}

TEST(Matrix22Test, IdentityTest)
{
  Matrix22f m = Matrix22f::identity();
  ASSERT_FLOAT_EQ(m[0][0], 1.0f);
  ASSERT_FLOAT_EQ(m[0][1], 0.0f);
  ASSERT_FLOAT_EQ(m[1][0], 0.0f);
  ASSERT_FLOAT_EQ(m[1][1], 1.0f);
}

TEST(Matrix22Test, EqualityTest)
{
  Matrix22f m = Matrix22f::identity();
  Matrix22f m2 = Matrix22f::identity();
  ASSERT_TRUE(m == m2);
}

TEST(Matrix22Test, InequalityTest)
{
  Matrix22f m3 = Matrix22f::fill(2);
  Matrix22f m4 = Matrix22f::identity();
  ASSERT_TRUE(m3 != m4);
}

TEST(Matrix22Test, CopyAssignmentOperator)
{
  Matrix22f m3 = Matrix22f::fill(2);
  Matrix22f m4;
  m4 = m3;
  ASSERT_TRUE(m3 == m4);
}

TEST(Matrix22Test, ScaleTest)
{
  auto m1 = Matrix22f::fill(2);
  auto m2 = m1 * 3.0f;
  auto m3 = Matrix22f::fill(6);
  ASSERT_DOUBLE_EQ(m3[0][0], m2[0][0]);
  ASSERT_DOUBLE_EQ(m3[0][1], m2[0][1]);
  ASSERT_DOUBLE_EQ(m3[1][0], m2[1][0]);
  ASSERT_DOUBLE_EQ(m3[1][1], m2[1][1]);
  auto m4 = 3.0f * m1;
  ASSERT_TRUE(m4 == m3);
}

TEST(Matrix22Test, ScaleAssignTest)
{
  auto m2 = Matrix22f::fill(2);
  m2 *= 3.0f;
  Matrix22f m3 = Matrix22f::fill(6);
  ASSERT_DOUBLE_EQ(m3[0][0], m2[0][0]);
  ASSERT_DOUBLE_EQ(m3[0][1], m2[0][1]);
  ASSERT_DOUBLE_EQ(m3[1][0], m2[1][0]);
  ASSERT_DOUBLE_EQ(m3[1][1], m2[1][1]);
}

TEST(Matrix22Test, DivideTest)
{
  Matrix22f m1 = Matrix22f::fill(6);
  Matrix22f m2 = m1 / 3.0f;
  Matrix22f m3 = Matrix22f::fill(2);
  ASSERT_DOUBLE_EQ(m3[0][0], m2[0][0]);
  ASSERT_DOUBLE_EQ(m3[0][1], m2[0][1]);
  ASSERT_DOUBLE_EQ(m3[1][0], m2[1][0]);
  ASSERT_DOUBLE_EQ(m3[1][1], m2[1][1]);
  // Matrix22f m4 = 3.0f / m1;
  // ASSERT_TRUE(m4 == m3);
}

TEST(Matrix22Test, DivideAssignTest)
{
  Matrix22f m2 = Matrix22f::fill(2);
  m2 *= 3.0f;
  Matrix22f m3 = Matrix22f::fill(6);
  ASSERT_DOUBLE_EQ(m3[0][0], m2[0][0]);
  ASSERT_DOUBLE_EQ(m3[0][1], m2[0][1]);
  ASSERT_DOUBLE_EQ(m3[1][0], m2[1][0]);
  ASSERT_DOUBLE_EQ(m3[1][1], m2[1][1]);
}

TEST(Matrix22Test, AddTest)
{
  Matrix22f m1 = Matrix22f::fill(2);
  Matrix22f m2 = m1 + 3.0f;
  Matrix22f m3 = Matrix22f::fill(5);
  ASSERT_DOUBLE_EQ(m3[0][0], m2[0][0]);
  ASSERT_DOUBLE_EQ(m3[0][1], m2[0][1]);
  ASSERT_DOUBLE_EQ(m3[1][0], m2[1][0]);
  ASSERT_DOUBLE_EQ(m3[1][1], m2[1][1]);
  Matrix22f m4 = 3.0f + m1;
  ASSERT_TRUE(m4 == m3);
}

TEST(Matrix22Test, AddAssignTest)
{
  Matrix22f m2 = Matrix22f::fill(2);
  m2 += 3.0f;
  Matrix22f m3 = Matrix22f::fill(5);
  ASSERT_DOUBLE_EQ(m3[0][0], m2[0][0]);
  ASSERT_DOUBLE_EQ(m3[0][1], m2[0][1]);
  ASSERT_DOUBLE_EQ(m3[1][0], m2[1][0]);
  ASSERT_DOUBLE_EQ(m3[1][1], m2[1][1]);
}

TEST(Matrix22Test, MinusTest)
{
  Matrix22f m1 = Matrix22f::fill(2);
  Matrix22f m2 = m1 - 3.0f;
  Matrix22f m3 = Matrix22f::fill(-1);
  ASSERT_DOUBLE_EQ(m3[0][0], m2[0][0]);
  ASSERT_DOUBLE_EQ(m3[0][1], m2[0][1]);
  ASSERT_DOUBLE_EQ(m3[1][0], m2[1][0]);
  ASSERT_DOUBLE_EQ(m3[1][1], m2[1][1]);
  Matrix22f m4 = 3.0f - m1;
  ASSERT_TRUE(m4 == m3);
}

TEST(Matrix22Test, MinusAssignTest)
{
  auto m2 = Matrix22f::fill(2);
  m2 -= 3.0f;
  auto m3 = Matrix22f::fill(-1);
  ASSERT_DOUBLE_EQ(m3[0][0], m2[0][0]);
  ASSERT_DOUBLE_EQ(m3[0][1], m2[0][1]);
  ASSERT_DOUBLE_EQ(m3[1][0], m2[1][0]);
  ASSERT_DOUBLE_EQ(m3[1][1], m2[1][1]);
}

TEST(Matrix22Test, transposeTest)
{
  auto m1 = Matrix22f{{1, 2}, {3, 4}};
  m1 = transpose(m1);
  ASSERT_DOUBLE_EQ(m1[0][0], 1);
  ASSERT_DOUBLE_EQ(m1[0][1], 3);
  ASSERT_DOUBLE_EQ(m1[1][0], 2);
  ASSERT_DOUBLE_EQ(m1[1][1], 4);
}

TEST(Matrix22Test, determinantTest)
{
  auto m1 = Matrix22f{{1, 2}, {3, 4}};
  auto det = determinant(m1);
  ASSERT_DOUBLE_EQ(det, -2);
}

TEST(Matrix22Test, MatrixVectorProductTest)
{
  auto m1 = Matrix22f{{1, 2}, {3, 4}};
  auto v1 = Vector2f{1, 2};
  auto r2 = m1 * v1;
  auto r3 = Vector2f{7, 10};
  ASSERT_DOUBLE_EQ(r2[0], r3[0]);
  ASSERT_DOUBLE_EQ(r2[1], r3[1]);
}

TEST(Matrix22Test, VectorMatrixProductTest)
{
  auto m1 = Matrix22f{{1, 2}, {3, 4}};
  auto v1 = Vector2f{1, 2};
  auto r2 = v1 * m1;
  auto r3 = Vector2f{5, 11};
  ASSERT_DOUBLE_EQ(r2[0], r3[0]);
  ASSERT_DOUBLE_EQ(r2[1], r3[1]);
}

TEST(Matrix22Test, MatrixMatrixProductTest)
{
  auto m1 = Matrix22f{1};
  auto m2 = Matrix22f{1};
  auto m3 = m1 * m2;
  auto m4 = Matrix22f{2};
  ASSERT_DOUBLE_EQ(m3[0][0], m4[0][0]);
  ASSERT_DOUBLE_EQ(m3[0][1], m4[0][1]);
  ASSERT_DOUBLE_EQ(m3[1][0], m4[1][0]);
  ASSERT_DOUBLE_EQ(m3[1][1], m4[1][1]);
}

TEST(Matrix22Test, MatrixInverseTest)
{
  auto m1 = Matrix22f::identity();
  auto m2 = inverse(m1);
  ASSERT_EQ(m1, m2);
  auto m3 = Matrix22f{{4, 2}, {7, 6}};
  auto m4 = inverse(m3);
  ASSERT_DOUBLE_EQ(m4[0][0], 0.6f);
  ASSERT_DOUBLE_EQ(m4[1][0], -0.7f);
  ASSERT_DOUBLE_EQ(m4[1][1], 0.4f);
  ASSERT_DOUBLE_EQ(m4[0][1], -0.2f);
}