#include "../include/QRdecomposition/QR.hpp"
#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <unsupported/Eigen/SparseExtra>

using namespace Eigen;

void givens_rotation(double a, double b, Matrix2d& G) {
    double r = hypot(a, b);
    double c = a / r;
    double s = -b / r;

    G << c, -s,
         s, c;
}

void qr_decomposition(const MatrixXd &A, MatrixXd &Q, MatrixXd &R) {
    int m = A.rows();
    int n = A.cols();
    Matrix2d G;
    Q = Mat::Identity(m, n);
    R = A;

    for (int j = 0; j < n; ++j) {
        for (int i = m - 1; i > j; --i) {
            if (R(i, j) != 0) {
                givens_rotation(R(i - 1, j), R(i, j), G);
                R.block(i - 1, j, 2, n - j) = G * R.block(i - 1, j, 2, n - j);
                Q.leftCols(m).middleCols(i - 1, 2) *= G.transpose();
            }
        }
    }
}
