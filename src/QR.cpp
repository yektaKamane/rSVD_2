#include "../include/QRdecomposition/QR.hpp"
#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <unsupported/Eigen/SparseExtra>

Mat givens_rotation(double a, double b) {
    double r = sqrt(a*a + b*b);
    double c = a / r;
    double s = -b / r;

    Mat G(2, 2);
    G << c, -s,
         s, c;

    return G;
}

void qr_decomposition(const Mat &A, Mat &Q, Mat &R) {
    int m = A.rows();
    int n = A.cols();

    for (int j = 0; j < n; ++j) {
        for (int i = m - 1; i > j; --i) {
            if (R(i, j) != 0){
                Mat G = givens_rotation(R(i - 1, j), R(i, j));
                R.block(i - 1, j, 2, n - j) = G * R.block(i - 1, j, 2, n - j);
                Q.block(0, i - 1, m, 2) = Q.block(0, i - 1, m, 2) * G.transpose();
            }
        }
    }
}
