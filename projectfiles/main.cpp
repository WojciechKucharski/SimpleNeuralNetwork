#include <iostream>
#include <vector>
#include "Matrix.hpp"

using namespace std;

int main(){
    Matrix a = Matrix({{1.0,1.0},{2.0,3.0}});
    Matrix b = Matrix({{1.0,1.0},{1.0,3.0}});
    if(a==b) cout << "equal";
    

    
    
    return 0;
}