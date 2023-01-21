#include "SimpleNeuralNetwork/Model.hpp"
#include <cstdlib>
#include <gtest/gtest.h>
#include <chrono>
#include <unistd.h>
TEST(ModelTC, ModelTC)
{


  ASSERT_EQ(12,1);
}

int main(int argc, char **argv)
{


  {
    {
  Model m = Model({30,30,30,30}, {0,0,0,0,0}, 0, 1);

  auto start = std::chrono::high_resolution_clock::now();
  m.forwardPropagation({30,100000,0,1});
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = stop - start;
  float ms = duration.count() * 1000.0f;
  std::cout << "Timer: " << ms << "ms" << std::endl;}
}
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}