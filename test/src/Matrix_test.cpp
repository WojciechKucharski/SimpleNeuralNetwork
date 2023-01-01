#include "SimpleNeuralNetwork/Matrix.hpp"

#include <gtest/gtest.h>

TEST(TmpAddTest1, CheckConstructor1)
{
  Matrix a{5,5,2};
  ASSERT_EQ(a(3,4), 2);
  EXPECT_TRUE(true);
}

TEST(TmpAddTest2, CheckConstructor2)
{
  Matrix a{{2,1},{1,1}};
  ASSERT_EQ(a(0,0), 2);
  EXPECT_TRUE(true);
}

TEST(TmpAddTest3, CheckConstructor3)
{
  Matrix a{5,5,-1,1};
  ASSERT_LE(a.maxValue(), 2);
  EXPECT_TRUE(true);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
