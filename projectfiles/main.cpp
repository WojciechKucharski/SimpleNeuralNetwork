#include <iostream>
#include <vector>
#include "Matrix.hpp"

using namespace std;

int main(){
    vector<Matrix> network;
    Matrix a{2,2,1};
    a(1,1) = -10;
    a.normalise();
    a.printMatrix();
    
    
    
    return 0;
}