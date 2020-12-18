// #include "gtest/gtest.h"
// #include <cagey-math/Matrix22.hh>
// #include <cstdint>

// using namespace cagey::math;

// TEST(Matrix22Test, Matrix22SizeTest)
// {
//   ASSERT_EQ(sizeof(Mat22<short>), sizeof(short[4]));
//   ASSERT_EQ(sizeof(Mat22f), sizeof(float[4]));
//   ASSERT_EQ(sizeof(Mat22d), sizeof(double[4]));
//   ASSERT_EQ(sizeof(Mat22i), sizeof(int[4]));
//   ASSERT_EQ(sizeof(Mat22u), sizeof(unsigned int[4]));
// }

// TEST(Matrix22Test, DefaultConstructorTest)
// {
//   Mat22f m;
//   ASSERT_EQ(sizeof(m), sizeof(float[4]));
// }

// TEST(Matrix22Test, SingleValueConstructorTest)
// {
//   Mat22f m{1.0};
//   ASSERT_FLOAT_EQ(m[0][0], 1.0f);
//   ASSERT_FLOAT_EQ(m[0][1], 1.0f);
//   ASSERT_FLOAT_EQ(m[1][0], 1.0f);
//   ASSERT_FLOAT_EQ(m[1][1], 1.0f);

//   Mat22f m2{1.0f};
//   ASSERT_FLOAT_EQ(m2[0][0], 1.0f);
//   ASSERT_FLOAT_EQ(m2[0][1], 1.0f);
//   ASSERT_FLOAT_EQ(m2[1][0], 1.0f);
//   ASSERT_FLOAT_EQ(m2[1][1], 1.0f);

//   Mat22i m3{1};
//   ASSERT_FLOAT_EQ(m3[0][0], 1);
//   ASSERT_FLOAT_EQ(m3[0][1], 1);
//   ASSERT_FLOAT_EQ(m3[1][0], 1);
//   ASSERT_FLOAT_EQ(m3[1][1], 1);
// }

// TEST(Matrix22Test, FillTest)
// {
//   Mat22f m = Mat22f::fill(1.0f);
//   ASSERT_FLOAT_EQ(m[0][0], 1.0f);
//   ASSERT_FLOAT_EQ(m[0][1], 1.0f);
//   ASSERT_FLOAT_EQ(m[1][0], 1.0f);
//   ASSERT_FLOAT_EQ(m[1][1], 1.0f);

//   Mat22f m2 = Mat22f::fill(1.0);
//   ASSERT_FLOAT_EQ(m2[0][0], 1.0f);
//   ASSERT_FLOAT_EQ(m2[0][1], 1.0f);
//   ASSERT_FLOAT_EQ(m2[1][0], 1.0f);
//   ASSERT_FLOAT_EQ(m2[1][1], 1.0f);

//   Mat22i m3 = Mat22i::fill(1);
//   ASSERT_EQ(m3[0][0], 1);
//   ASSERT_EQ(m3[0][1], 1);
//   ASSERT_EQ(m3[1][0], 1);
//   ASSERT_EQ(m3[1][1], 1);
// }

// TEST(Matrix22Test, ZeroTest)
// {
//   Mat22f m = Mat22f::zero();
//   ASSERT_FLOAT_EQ(m[0][0], 0.0f);
//   ASSERT_FLOAT_EQ(m[0][1], 0.0f);
//   ASSERT_FLOAT_EQ(m[1][0], 0.0f);
//   ASSERT_FLOAT_EQ(m[1][1], 0.0f);

//   Mat22f m2 = Mat22f::zero();
//   ASSERT_FLOAT_EQ(m2[0][0], 0.0f);
//   ASSERT_FLOAT_EQ(m2[0][1], 0.0f);
//   ASSERT_FLOAT_EQ(m2[1][0], 0.0f);
//   ASSERT_FLOAT_EQ(m2[1][1], 0.0f);

//   Mat22i m3 = Mat22i::zero();
//   ASSERT_EQ(m3[0][0], 0);
//   ASSERT_EQ(m3[0][1], 0);
//   ASSERT_EQ(m3[1][0], 0);
//   ASSERT_EQ(m3[1][1], 0);
// }

// TEST(Matrix22Test, VectorConstructorTest)
// {
//   // Vec2f col0{1.0, 1.0};
//   // Vec2f col1{1.0, 1.0};
//   // Vec2f col2{1.0, 1.0};
//   Mat22f m{{1.0, 1.0}, {2.0, 2.0}};
//   //Mat22f m{col0, {2.0, 2.0} };
//   //  Mat22f m{col0, col1 };
//   //Mat22f m{col0, col1, col2 };
//   ASSERT_FLOAT_EQ(m[0][0], 1.0f);
//   ASSERT_FLOAT_EQ(m[0][1], 1.0f);
//   ASSERT_FLOAT_EQ(m[1][0], 2.0f);
//   ASSERT_FLOAT_EQ(m[1][1], 2.0f);
// }

// TEST(Matrix22Test, ArrayConstructorTest)
// {
//   auto data = std::array<float, 4>{1, 0, 0, 1};
//   Mat22f m{data};

//   ASSERT_FLOAT_EQ(m[0][0], 1.0f);
//   ASSERT_FLOAT_EQ(m[0][1], 0.0f);
//   ASSERT_FLOAT_EQ(m[1][0], 0.0f);
//   ASSERT_FLOAT_EQ(m[1][1], 1.0f);
// }

// TEST(Matrix22Test, CopyConstructorTest)
// {
//   Mat22f m = Mat22f::identity();
//   Mat22f m1{m};
//   ASSERT_TRUE(m1 == m);
// }

// TEST(Matrix22Test, IdentityTest)
// {
//   Mat22f m = Mat22f::identity();
//   ASSERT_FLOAT_EQ(m[0][0], 1.0f);
//   ASSERT_FLOAT_EQ(m[0][1], 0.0f);
//   ASSERT_FLOAT_EQ(m[1][0], 0.0f);
//   ASSERT_FLOAT_EQ(m[1][1], 1.0f);
// }

// TEST(Matrix22Test, EqualityTest)
// {
//   Mat22f m = Mat22f::identity();
//   Mat22f m2 = Mat22f::identity();
//   ASSERT_TRUE(m == m2);
// }

// TEST(Matrix22Test, InequalityTest)
// {
//   Mat22f m3 = Mat22f::fill(2);
//   Mat22f m4 = Mat22f::identity();
//   ASSERT_TRUE(m3 != m4);
// }

// TEST(Matrix22Test, ScaleTest)
// {
//   Mat22f m1 = Mat22f::fill(2);
//   Mat22f m2 = m1 * 3.0f;
//   Mat22f m3 = Mat22f::fill(6);
//   ASSERT_TRUE(m2 == m3);
// }
