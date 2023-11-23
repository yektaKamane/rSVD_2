#include <iostream>
#include <cmath>
#include <Eigen/Dense>

Eigen::MatrixXd givens_rotation(double a, double b) {
    double r = std::sqrt(a*a + b*b);
    double c = a / r;
    double s = -b / r;

    Eigen::MatrixXd G(2, 2);
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

int main() {
    // Create a 3x3 matrix A
    Eigen::MatrixXd A(3, 3);
    A << 1.0, 2.0, 3.0,
         4.0, 5.0, 6.0,
         7.0, 8.0, 9.0;

    // Perform QR decomposition
    auto [Q, R] = qr_decomposition(A);

    // Print the results
    std::cout << "Matrix A:" << std::endl << A << std::endl << std::endl;
    std::cout << "Matrix Q:" << std::endl << Q << std::endl << std::endl;
    std::cout << "Matrix R:" << std::endl << R << std::endl;

    return 0;
}
