#include "../include/r_SVD/rSVD.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <iostream>
#include <filesystem> // C++17 or later
#include <Eigen/Dense>

// The main function for running the tests

int main(){
    std::cout << "test rSVD" << std::endl;
    mat A = mat::Random(3, 3);
    mat U;
    vet S;
    mat V;
    rSVD(A, U, S, V);
    std::cout << "A = \n" << A << std::endl;
    std::cout << "U = \n" << U << std::endl;
    std::cout << "S = \n" << S << std::endl;
    std::cout << "V = \n" << V << std::endl;
    return 0;
}