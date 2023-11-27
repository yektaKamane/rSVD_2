#include <iostream>
#include <tuple>
#include <cmath>
#include "../include/dataStructure/matrix.hpp"

Matrix givens_rotation(double a, double b) {
    double r = std::sqrt(a*a + b*b);
    double c = a / r;
    double s = -b / r;

    Matrix G(2, 2);
    G.setElement(0, 0, c);
    G.setElement(0, 1, -s);
    G.setElement(1, 0, s);
    G.setElement(1, 1, c);

    return G;
}

std::tuple<Matrix, Matrix> qr_decomposition(const Matrix& A) {
    int m = A.getRows();
    int n = A.getCols();

    Matrix Q = Matrix::identity(m);
    Matrix R = A;

    for (int j = 0; j < n; ++j) {
        for (int i = m - 1; i > j; --i) {
            Matrix G = givens_rotation(R.getElement(i - 1, j), R.getElement(i, j));
            R.setBlock(i - 1, j, G.multiply(R.getBlock(i - 1, j, 2, n - j)));
            Q.setBlock(0, i - 1, Q.getBlock(0, i - 1, m, 2).multiply(G.transpose()));
        }
    }

    return std::make_tuple(Q, R);
}

int main() {
    // Create a 3x3 matrix A
    Matrix A = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    };

    std::cout << "Matrix A:\n";
    A.display();


    // Perform QR decomposition
    auto [Q, R] = qr_decomposition(A);

    // Print the results
    std::cout << "Matrix Q:\n";
    Q.display();
    std::cout << "Matrix R:\n";
    R.display();
    return 0;
}
