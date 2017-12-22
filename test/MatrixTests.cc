#include "gtest/gtest.h"
#include <cagey-math/Matrix.hh>
#include <cstdint>

using namespace cagey::math;

TEST(Matrix22Test, Matrix22SizeTest) {
  ASSERT_EQ(sizeof(Mat22<short>), sizeof(short[4]));
  ASSERT_EQ(sizeof(Mat22f), sizeof(float[4]));
  ASSERT_EQ(sizeof(Mat22d), sizeof(double[4]));
  ASSERT_EQ(sizeof(Mat22i), sizeof(int[4]));
  ASSERT_EQ(sizeof(Mat22u), sizeof(unsigned int[4]));
}


TEST(Matrix22Test, DefaultConstructorTest) { 
  Mat22f m; 
  ASSERT_FLOAT_EQ(m[0][0], 0);
  ASSERT_FLOAT_EQ(m[0][1], 0);
  ASSERT_FLOAT_EQ(m[1][1], 0);
  ASSERT_FLOAT_EQ(m[1][0], 0);
}
