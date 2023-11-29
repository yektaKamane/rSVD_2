#include <iostream>
#include <tuple>
#include <cmath>
#include "../include/dataStructure/matrix.hpp"

Matrix givens_rotation(double a, double b) {
    
    Matrix G(2, 2);

    if (b == 0.0){
        G.setElement(0, 0, 1.0);
        G.setElement(0, 1, 0.0);
        G.setElement(1, 0, 0.0);
        G.setElement(1, 1, 1.0);
    }

    else{
        double r = std::sqrt(a*a + b*b);
        double c = a / r;
        double s = -b / r;
        
        G.setElement(0, 0, c);
        G.setElement(0, 1, -s);
        G.setElement(1, 0, s);
        G.setElement(1, 1, c);
    }
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

// int main() {
//     Matrix A("../data/input/bcsstm01.mtx");
//     A.display();
//     A.writeNonZeroElementsToCSR("../data/output/bcsstm01_output.mtx");

//     // Perform QR decomposition
//     auto [Q, R] = qr_decomposition(A);
//     // std::cout << "Matrix Q:\n";
//     // Q.display();
//     // std::cout << "Matrix R:\n";
//     // R.display();

//     return 0;
// }
