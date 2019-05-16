#include "gtest/gtest.h"
#include <cagey/math/Vector.hh>
#include <cstdint>

using namespace cagey::math;

TEST(VectorTest, VectorTypeTest) {
  ASSERT_EQ(detail::isVectorTypeValue<bool>, false);
  ASSERT_EQ(detail::isVectorTypeValue<float>, true);
  ASSERT_EQ(detail::isVectorTypeValue<double>, true);
  ASSERT_EQ(detail::isVectorTypeValue<std::int8_t>, true);
  ASSERT_EQ(detail::isVectorTypeValue<std::int16_t>, true);
  ASSERT_EQ(detail::isVectorTypeValue<std::int32_t>, true);
  ASSERT_EQ(detail::isVectorTypeValue<std::int64_t>, true);
  ASSERT_EQ(detail::isVectorTypeValue<std::uint8_t>, true);
  ASSERT_EQ(detail::isVectorTypeValue<std::uint16_t>, true);
  ASSERT_EQ(detail::isVectorTypeValue<std::uint32_t>, true);
  ASSERT_EQ(detail::isVectorTypeValue<std::uint64_t>, true);
}

TEST(VectorTest, ConstructorTest) { 
  Vec2f vv{}; 
  ASSERT_EQ(sizeof(vv), sizeof(float[2]));

  Vec2f v(0.0f); 
  ASSERT_EQ(sizeof(v), sizeof(float[2]));
  ASSERT_DOUBLE_EQ(v[0], 0.0f);
  ASSERT_DOUBLE_EQ(v[1], 0.0f);

  Vec2f v2(0.0f, 0.0f); 
  ASSERT_EQ(sizeof(v2), sizeof(float[2]));
  ASSERT_DOUBLE_EQ(v2[0], 0.0f);
  ASSERT_DOUBLE_EQ(v2[1], 0.0f);

  Vec3f v3(0.0f, 0.0f, 0.0f); 
  ASSERT_EQ(sizeof(v3), sizeof(float[3]));
  ASSERT_DOUBLE_EQ(v3[0], 0);
  ASSERT_DOUBLE_EQ(v3[1], 0);  
  ASSERT_DOUBLE_EQ(v3[2], 0);  

  Vec4f v4(0.0f, 0.0f, 0.0f, 0.0f); 
  ASSERT_EQ(sizeof(v4), sizeof(float[4]));
  ASSERT_DOUBLE_EQ(v4[0], 0);
  ASSERT_DOUBLE_EQ(v4[1], 0);  
  ASSERT_DOUBLE_EQ(v4[2], 0);    
  ASSERT_DOUBLE_EQ(v4[3], 0);    
}

TEST(VectorTest, ZeroTest) { 
  Vec2f v = Vec2f::Zero(); 
  ASSERT_EQ(sizeof(v), sizeof(float[2]));
  ASSERT_DOUBLE_EQ(v[0], 0.0f);
  ASSERT_DOUBLE_EQ(v[1], 0.0f);
}

TEST(VectorTest, UnitVectorTest) { 
  Vec2f v = Vec2f::UnitX(); 
  ASSERT_DOUBLE_EQ(v[0], 1.0f);
  ASSERT_DOUBLE_EQ(v[1], 0.0f);

  Vec3f v3 = Vec3f::UnitY(); 
  ASSERT_DOUBLE_EQ(v3[0], 0.0f);
  ASSERT_DOUBLE_EQ(v3[1], 1.0f);  
  ASSERT_DOUBLE_EQ(v3[2], 0.0f);

  v3 = Vec3f::UnitZ(); 
  ASSERT_DOUBLE_EQ(v3[0], 0.0f);
  ASSERT_DOUBLE_EQ(v3[1], 0.0f);  
  ASSERT_DOUBLE_EQ(v3[2], 1.0f);

  Vec4f v4 = Vec4f::UnitW(); 
  ASSERT_DOUBLE_EQ(v4[0], 0.0f);
  ASSERT_DOUBLE_EQ(v4[1], 0.0f);  
  ASSERT_DOUBLE_EQ(v4[2], 0.0f);
  ASSERT_DOUBLE_EQ(v4[3], 1.0f);
}

TEST(VectorTest, IndexTest) { 
  Vec3f v1 = Vec3f{1.0f}; 
  v1[0] = 2.0f;
  v1[1] = 2.0f;
  v1[2] = 2.0f;
  ASSERT_DOUBLE_EQ(v1[0], 2.0f);
  ASSERT_DOUBLE_EQ(v1[1], 2.0f);  
  ASSERT_DOUBLE_EQ(v1[2], 2.0f);
}

TEST(VectorTest, AssignTest) { 
  Vec3f v1 = Vec3f{1.0f}; 
  Vec3f v2 = Vec3f{2.0f}; 
  v1 = v2;
  ASSERT_DOUBLE_EQ(v1[0], 2.0f);
  ASSERT_DOUBLE_EQ(v1[1], 2.0f);  
  ASSERT_DOUBLE_EQ(v1[2], 2.0f);
}

TEST(VectorTest, AdditionTest) { 
  Vec3f v1 = Vec3f{1.0f}; 
  Vec3f v2 = Vec3f{2.0f}; 
  v1 += v2;
  ASSERT_DOUBLE_EQ(v1[0], 3.0f);
  ASSERT_DOUBLE_EQ(v1[1], 3.0f);  
  ASSERT_DOUBLE_EQ(v1[2], 3.0f);

  Vec2f v3 = Vec2f{1.0f};
  Vec2f v4 = Vec2f{2.0f};
  Vec2f v5 = v3 + v4;
  ASSERT_DOUBLE_EQ(v5[0], 3.0f);
  ASSERT_DOUBLE_EQ(v5[1], 3.0f); 
}

TEST(VectorTest, SubtractionTest) { 
  Vec3f v1 = Vec3f{1.0f}; 
  Vec3f v2 = Vec3f{2.0f}; 
  v1 -= v2;
  ASSERT_DOUBLE_EQ(v1[0], -1.0f);
  ASSERT_DOUBLE_EQ(v1[1], -1.0f);  
  ASSERT_DOUBLE_EQ(v1[2], -1.0f);

  Vec2f v3 = Vec2f{1.0f};
  Vec2f v4 = Vec2f{2.0f};
  Vec2f v5 = v3 - v4;
  ASSERT_DOUBLE_EQ(v5[0], -1.0f);
  ASSERT_DOUBLE_EQ(v5[1], -1.0f);   
}

TEST(VectorTest, ScaleTest) { 
  Vec3f v1 = Vec3f{1.0f}; 
  v1 *= 2.0f;
  ASSERT_DOUBLE_EQ(v1[0], 2.0f);
  ASSERT_DOUBLE_EQ(v1[1], 2.0f);  
  ASSERT_DOUBLE_EQ(v1[2], 2.0f);

  Vec3f v2 = Vec3f{10.0f}; 
  v2 /= 2.0f;
  ASSERT_DOUBLE_EQ(v2[0], 5.0f);
  ASSERT_DOUBLE_EQ(v2[1], 5.0f);  
  ASSERT_DOUBLE_EQ(v2[2], 5.0f);  

  Vec3f v3 = Vec3f{2.0f}; 
  v3 = v3 * 2.0f;
  ASSERT_DOUBLE_EQ(v3[0], 4.0f);
  ASSERT_DOUBLE_EQ(v3[1], 4.0f);  
  ASSERT_DOUBLE_EQ(v3[2], 4.0f);  

  Vec3f v4 = Vec3f{2.0f}; 
  v4 = v4 / 2.0f;
  ASSERT_DOUBLE_EQ(v4[0], 1.0f);
  ASSERT_DOUBLE_EQ(v4[1], 1.0f);  
  ASSERT_DOUBLE_EQ(v4[2], 1.0f);  

  Vec3f v5 = Vec3f{2.0f}; 
  v5 = 2.0f * v5;
  ASSERT_DOUBLE_EQ(v5[0], 4.0f);
  ASSERT_DOUBLE_EQ(v5[1], 4.0f);  
  ASSERT_DOUBLE_EQ(v5[2], 4.0f);  

  Vec3f v6 = Vec3f{2.0f}; 
  v6 = 2.0f / v6;
  ASSERT_DOUBLE_EQ(v6[0], 1.0f);
  ASSERT_DOUBLE_EQ(v6[1], 1.0f);  
  ASSERT_DOUBLE_EQ(v6[2], 1.0f);    
}

TEST(VectorTest, NegateTest) { 
  Vec3f v{1.0f};
  Vec3f v1 = -v;
  ASSERT_DOUBLE_EQ(v1[0], -1.0f);
  ASSERT_DOUBLE_EQ(v1[1], -1.0f);  
  ASSERT_DOUBLE_EQ(v1[2], -1.0f);  
}

TEST(VectorTest, EqualsTest) { 
  Vec3i v{1};
  Vec3i v1{1};
  Vec3i v2{2};
  ASSERT_TRUE(v == v1);
  ASSERT_TRUE(v != v2);
}

TEST(VectorTest, xyTest) { 
  Vector<float, 3> v{1.0f};
  v.xy();
}

TEST(VectorTest, xyzTest) { 
  Vec4f v{1.0f};
  Vec3f v1 = v.xyz();
  ASSERT_DOUBLE_EQ(v1[0], 1.0f);
  ASSERT_DOUBLE_EQ(v1[1], 1.0f);  
  ASSERT_DOUBLE_EQ(v1[2], 1.0f);   
}

TEST(VectorTest, beginTest) { 
  using std::begin;
  Vec4f v{1.0f};
  ASSERT_EQ(&v[0], begin(v));

  const Vec4f v2{2.0f};
  ASSERT_EQ(&v2[0], begin(v2));
}


TEST(VectorTest, endTest) { 
  using std::end;
  Vec4f v{1.0f};
  //one past the end
  ASSERT_EQ(&v[0]+4, end(v));

  const Vec2f v2{2.0f};
  ASSERT_EQ(&v2[0]+2, end(v2));
}

TEST(VectorTest, VectorDotProductTest) {
  auto x = dot(Vec3d{1.2, 3.4, 2.5}, Vec3d{7.0, 8.0, 9.0});
  ASSERT_DOUBLE_EQ(x, 1.2 * 7 + 3.4 * 8 + 2.5 * 9);
}

TEST(VectorTest, CrossProductTest) {
  auto x = cross(Vec3f{5.0f, 1.0f, 4.0f}, Vec3f{-1.0f, 0.0f, 2.0f});
  auto y = Vec3f{2.0f, -14.0f, 1.0f};
  ASSERT_TRUE(fuzzyEquals(x, y));
}

TEST(VectorTest, LengthProductTest) {
  ASSERT_DOUBLE_EQ(length(Vec3d{1.2, 3.4, 2.5}),
                   std::sqrt(lengthSquared(Vec3d{1.2, 3.4, 2.5})));

  auto x = dot(Vec3d(1.2, 3.4, 2.5), Vec3d(7.0, 8.0, 2.5));
  ASSERT_DOUBLE_EQ(x, 1.2 * 7 + 3.4 * 8 + 2.5 * 2.5);
}

TEST(VectorTest, LengthSquaredProductTest) {
  auto x = lengthSquared(Vec3d(1.2, 3.4, 2.5));
  ASSERT_DOUBLE_EQ(x, 1.2 * 1.2 + 3.4 * 3.4 + 2.5 * 2.5);
}

