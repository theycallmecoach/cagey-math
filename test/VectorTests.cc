#include "gtest/gtest.h"
#include <cagey/math/Vector.hh>
#include <cstdint>

using namespace cagey::math;

TEST(VectorTest, VectorTypeTest) {
  ASSERT_EQ(is_vec_type<bool>::value, false);
  ASSERT_EQ(is_vec_type<float>::value, true);
  ASSERT_EQ(is_vec_type<double>::value, true);
  ASSERT_EQ(is_vec_type<std::int8_t>::value, true);
  ASSERT_EQ(is_vec_type<std::int16_t>::value, true);
  ASSERT_EQ(is_vec_type<std::int32_t>::value, true);
  ASSERT_EQ(is_vec_type<std::int64_t>::value, true);
  ASSERT_EQ(is_vec_type<std::uint8_t>::value, true);
  ASSERT_EQ(is_vec_type<std::uint16_t>::value, true);
  ASSERT_EQ(is_vec_type<std::uint32_t>::value, true);
  ASSERT_EQ(is_vec_type<std::uint64_t>::value, true);
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

TEST(VectorTest, AdditionTest) { 
  Vec3f v1 = Vec3f{1.0f}; 
  Vec3f v2 = Vec3f{2.0f}; 
  v1 += v2;
  ASSERT_DOUBLE_EQ(v1[0], 3.0f);
  ASSERT_DOUBLE_EQ(v1[1], 3.0f);  
  ASSERT_DOUBLE_EQ(v1[2], 3.0f);
}

TEST(VectorTest, SubtractionTest) { 
  Vec3f v1 = Vec3f{1.0f}; 
  Vec3f v2 = Vec3f{2.0f}; 
  v1 -= v2;
  ASSERT_DOUBLE_EQ(v1[0], -1.0f);
  ASSERT_DOUBLE_EQ(v1[1], -1.0f);  
  ASSERT_DOUBLE_EQ(v1[2], -1.0f);
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
}
