#include <iostream>
#include <vector>
#include "Matrix.hpp"

using namespace std;

int main(){
    vector<Matrix> network;
    network.push_back({5,5,-1,1});
    network.push_back({5,2,2});
    network.push_back({2,3,3});
    network.push_back({3,1,4});
    Matrix a{2,2,1};
    a(1,1) = 10;
    cout << a.det();
    
    
    
    return 0;
}