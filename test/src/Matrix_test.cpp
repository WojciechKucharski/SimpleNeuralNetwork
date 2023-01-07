#include "SimpleNeuralNetwork/Matrix.hpp"
#include <cstdlib>
#include <gtest/gtest.h>

double tol = 0.001;

TEST(TC0, TC0)
{
  Matrix a;
  ASSERT_EQ(a.getCols(), 0);
  ASSERT_EQ(a.getRows(), 0);
  ASSERT_EQ(a.isEmpty(), 1);
  ASSERT_EQ(a.isValid(), 0);
  Matrix b = {3,3,3};
  Matrix c = {3,2,1};
  ASSERT_TRUE(b.isSquare());
  ASSERT_FALSE(c.isSquare());
  ASSERT_EQ(b.isEmpty(), 0);
  ASSERT_EQ(b.isValid(), 1);
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
  Matrix a = {3,3,1};
  Matrix b = {3,3,2};
  a = a * 2;
  ASSERT_TRUE(a==b);
}

TEST(TC101, TC101)
{
  Matrix a = {3,3,2};
  Matrix b = {3,3,3};
  a = a + 1;
  ASSERT_TRUE(a==b);
}

TEST(TC102, TC102)
{
  Matrix a = {3,3,1};
  Matrix b = {3,3,0};
  a = a - 1;
  ASSERT_TRUE(a==b);
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

TEST(TC141, TC141)
{
  Matrix a{{{1,2,3},{1,2,3},{1,2,3}}};
  a.mulRow(2, 2);
  Matrix b{{{1,2,3},{1,2,3},{2,4,6}}};
  ASSERT_TRUE(a==b);
}

TEST(TC15, TC15)
{
  Matrix a{3,3,1};
  double det = a.det();
  double realDet = 0;
  ASSERT_LE(abs(realDet-det), tol);
}

TEST(TC16, TC16)
{
  Matrix a{{{1,1,1},{1,1,2},{2,1,1}}};
  double det = a.det();
  double realDet = 1;
  ASSERT_LE(abs(realDet-det), tol);
}

TEST(TC17, TC17)
{
  Matrix a = {{0.86033026,0.80277411,0.23985895},
              {0.16578023,0.29882813,0.60257004},
              {0.43159065,0.48890888,0.0841036,}};
  double det = a.det();
  double realDet = -0.045747183704252264;
  ASSERT_LE(abs(realDet-det), tol);
}

TEST(TC18, TC18)
{
  Matrix a = {{0.4504897,0.02011534},
              {0.86118024,0.20210932}};
  double det = a.det();
  double realDet = 0.07372523508513454;
  ASSERT_LE(abs(realDet-det), tol);
}

TEST(TC19, TC19)
{
  Matrix a = {{0.62608542,0.62161827,0.98608784,0.13174803,0.52651388},
              {0.14826408,0.05140118,0.89620813,0.57197085,0.31077571},
              {0.67955787,0.99196868,0.76910558,0.38292731,0.89164895},
              {0.902972,0.63296968,0.35539502,0.05036292,0.84566413},
              {0.2078268,0.03903877,0.58439455,0.08770039,0.23954624}};
  double det = a.det();
  double realDet = -0.023511663587473874;
  ASSERT_LE(abs(realDet-det), tol);
}

TEST(TC20, TC20)
{
  Matrix a = {3,3,0};
  Matrix b = {3,4,0};
  Matrix c = {3,3,0,3};
  for(int i = 0; i < 3; i++) a(i,i) = 1;
  ASSERT_TRUE(a.isIdentity());
  ASSERT_FALSE(b.isIdentity());
  ASSERT_FALSE(c.isIdentity());
}

TEST(TC21, TC21)
{
  Matrix a = {3,3,1};
  Matrix b = {3,1,1};
  Matrix c = {1,3,1};
  a(2,2) = 2;
  b(2,0) = 2;
  c(0,2) = 2;
  ASSERT_TRUE(c == a.getRow(2));
  ASSERT_TRUE(b == a.getCol(2));
}

TEST(TC22, TC22)
{
  Matrix a = {3,3,3};
  ASSERT_EQ(a.sum(), 3*3*3);
  Matrix b = {5,1,2};
  ASSERT_EQ(b.sum(), 5*1*2);
}

TEST(TC23, TC23)
{
  Matrix a = {{0.86033026,0.80277411,0.23985895},
              {0.16578023,0.29882813,0.60257004},
              {0.43159065,0.48890888,0.0841036,}};
  Matrix b = a * a.reversed();
  ASSERT_TRUE(b.isIdentity());
}

TEST(TC24, TC24)
{
  Matrix a = {10001,10001,1};
  ASSERT_EQ(a(10000,1000), 1);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


/*
import numpy as np
n = 3
a = np.random.rand(n,n)
A = str(a).replace("\n","").replace(" ",",").replace("[","{").replace("]","}")

print(f"Matrix a = {A};")
print("double det = a.det();")
print(f"double realDet = {np.linalg.det(a)};")
print("ASSERT_LE(abs(realDet-det), tol);")
*/