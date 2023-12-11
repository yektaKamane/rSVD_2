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
    int n = 4;
    Mat A(n, n);
    A << 1.0, 2.0, 3.0, 4.0,
         5.0, 6.0, 7.0, 8.0,
         9.0, 10.0, 11.0, 12.0,
         13.0, 14.0, 15.0, 16.0;
    Mat U = Mat::Zero(n, n);
    Vet S = Vet::Zero(n);
    Mat V = Mat::Zero(n, n);
    //vet sigma = vet::Zero(dim);
    //mat U = mat::Zero(A.rows(), dim); // U m*n or m*m
    //mat V = mat::Zero(dim, A.cols()); // V n*n or m*n
    rSVD(A, U, S, V);
    std::cout<<"--RSVD TEST--"<<std::endl;
    // std::cout << "A = \n" << A << std::endl;
     std::cout << "U = \n" << U << std::endl;
     std::cout << "S = \n" << S << std::endl;
     std::cout << "V = \n" << V << std::endl;
    
     Eigen::MatrixXd diagonalMatrix = S.asDiagonal();

    Mat A_2(n, n);
    A_2 = U * diagonalMatrix;
    A_2 = A_2 * V.transpose();
    //std::cout << "A_2 = \n" << A_2 << std::endl;

    Mat diff = A - A_2;
    double norm_of_difference = (A - A_2).norm();
    std::cout << "norm of diff : " << norm_of_difference << std::endl;
    return 0;
}