#include "../include/QRdecomposition/QR.hpp"
#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <unsupported/Eigen/SparseExtra>

Eigen::MatrixXd givens_rotation(double a, double b) {
    
    Eigen::MatrixXd G(2, 2);
    double c = 1.0;
    double s = 0;

    if (b != 0){
        double r = std::sqrt(a*a + b*b);
        c = a / r;
        s = -b / r;
    }
    G << c, -s,
         s, c;

    return G;
}

std::tuple<Eigen::MatrixXd, Eigen::MatrixXd> qr_decomposition(const Eigen::MatrixXd& A) {
    int m = A.rows();
    int n = A.cols();

    Eigen::MatrixXd Q = Eigen::MatrixXd::Identity(m, m);
    Eigen::MatrixXd R = A;

    for (int j = 0; j < n; ++j) {
        for (int i = m - 1; i > j; --i) {
            Eigen::MatrixXd G = givens_rotation(R(i - 1, j), R(i, j));
            R.block(i - 1, j, 2, n - j) = G * R.block(i - 1, j, 2, n - j);
            Q.block(0, i - 1, m, 2) = Q.block(0, i - 1, m, 2) * G.transpose();
        }
    }

    return std::make_tuple(Q, R);
}

// int main() {
    
//     Eigen::SparseMatrix<double> sparseMatrix;
//     Eigen::loadMarket(sparseMatrix, "../data/input/bcsstm01.mtx");
//     Eigen::MatrixXd A = Eigen::MatrixXd(sparseMatrix);

//     // Perform QR decomposition
//     auto [Q, R] = qr_decomposition(A);

//     // Print the results
//     std::cout << "Matrix A:" << std::endl << A << std::endl << std::endl;
//     std::cout << "Matrix Q:" << std::endl << Q << std::endl << std::endl;
//     std::cout << "Matrix R:" << std::endl << R << std::endl;

//     return 0;
// }