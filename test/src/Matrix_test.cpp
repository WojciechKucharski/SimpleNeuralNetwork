#include "SimpleNeuralNetwork/Matrix.hpp"

#include <gtest/gtest.h>

TEST(TC0, TC0)
{
  Matrix a;
  ASSERT_EQ(a.getCols(), 0);
  ASSERT_EQ(a.getRows(), 0);
  ASSERT_EQ(a.isEmpty(), 1);
}

TEST(TC1, TC1)
{
  Matrix a{5,5,2};
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 5; j ++){
      ASSERT_EQ(a(i,j), 2);
    }
    }
}

TEST(TC2, TC2)
{
  Matrix a{5,5,2};
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 5; j ++){
      a(i,j) = 0;
      ASSERT_EQ(a(i,j), 0);
    }
    }
}

TEST(TC3, TC3)
{
  Matrix a{{1,2},{3,4}};
  ASSERT_EQ(a(0,0), 1);
  ASSERT_EQ(a(0,1), 2);
  ASSERT_EQ(a(1,0), 3);
  ASSERT_EQ(a(1,1), 4);
}

TEST(TC4, TC4)
{
  Matrix a{5,5,-1,1};
  ASSERT_LE(a.maxValue(), 1);
  ASSERT_LE(-1, a.minValue());
}

TEST(TC5, TC5)
{
  Matrix b{5,5,2};
  Matrix a = b;
  b(0,0) = 0;
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 5; j ++){
      ASSERT_EQ(a(i,j), 2);
    }
    }
}

TEST(TC6, TC6)
{
  Matrix a{{{1,2,3},{1,2,3},{1,2,3}}};
  Matrix b{{{1,2,3},{1,2,3},{1,2,3}}};
  Matrix c{{{1,2,3},{1,2,3},{1,2,1}}};
  Matrix d{7,2,1};
  ASSERT_EQ(a==b, true);
  ASSERT_EQ(a==c, false);
  ASSERT_EQ(a==d, false);
}

TEST(TC7, TC7)
{
  Matrix a{{{1,2,3},{1,2,3},{1,2,3}}};
  Matrix b{{{1,2,3},{1,2,3},{1,2,3}}};
  Matrix c = a+b;
  Matrix d{{{2,4,6},{2,4,6},{2,4,6}}};
  ASSERT_EQ(c==d, true);
}

TEST(TC8, TC8)
{
  Matrix a{{{1,2,3},{1,2,3},{1,2,3}}};
  Matrix b{{{1,2,3},{1,2,3},{1,2,3}}};
  Matrix c = a-b;
  Matrix d{{{0,0,0},{0,0,0},{0,0,0}}};
  ASSERT_EQ(c==d, true);
}

TEST(TC9, TC9)
{
  Matrix a = {{0,0,0}};
  Matrix b = {{0},{0},{0}};
  Matrix ab = a*b;
  Matrix ba = b*a;
  Matrix tab = {{0}};
  Matrix tba = {{0,0,0},{0,0,0},{0,0,0}};
  ASSERT_EQ(ab, tab);
  ASSERT_EQ(ba, tba);
}

TEST(TC10, TC10)
{
  Matrix a = {{0,0,0},{0,0,0},{0,0,0}};
  Matrix b = {3,3,0};
  ASSERT_EQ(a, b);
}

TEST(TC11, TC11)
{
  Matrix a = {{0,0,0}};
  Matrix b = {{0},{0},{0}};
  ASSERT_TRUE(a==(b.transpose()));
  ASSERT_TRUE((a.transpose())==b);
}

TEST(TC12, TC12)
{
  Matrix a{10,10,0,10};
  a.normalise();
  ASSERT_TRUE(a.maxValue()<=1);
}

TEST(TC13, TC13)
{
  Matrix a{{{1,2,3},{1,2,3},{5,2,3}}};
  a.swapRows(1,2);
  Matrix b{{{1,2,3},{5,2,3},{1,2,3}}};
  ASSERT_TRUE(a==b);
}

TEST(TC14, TC14)
{
  Matrix a{{{1,2,3},{1,2,3},{1,2,3}}};
  a.addRows(2,1,-1);
  Matrix b{{{1,2,3},{1,2,3},{0,0,0}}};
  ASSERT_TRUE(a==b);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
