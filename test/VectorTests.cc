#include "gtest/gtest.h"
#include <cagey-math/detail/Vector.hh>
#include <cstdint>

using namespace cagey::math;

TEST(VectorTest, VectorTypeTest)
{
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
