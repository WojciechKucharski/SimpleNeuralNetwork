#include <iostream>
#include <vector>
#include "Matrix.hpp"

using namespace std;

int main(){
    vector<Matrix> network;
    network.push_back({5,5,1});
    network.push_back({5,2,2});
    network.push_back({2,3,3});
    network.push_back({3,1,4});
    Matrix a = network[0];
    a.printMatrix();
    a = a * network[1];
    a.printMatrix();
    a = a * network[2];
    a.printMatrix();
    return 0;
}