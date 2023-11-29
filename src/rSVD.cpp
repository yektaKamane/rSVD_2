#include "rSVD.hpp"

#include "../include/powerMethod/PM2_full.hpp"
#include "../include/dataStructure/matrix.hpp"
#include "../include/dataStructure/vector.hpp"
#include "../include/QRdecomposition/QR.hpp"


 void rSVD(const Matrix& A, Matrix& U, Vector& S, Matrix& V) {
    // Stage A
    // (1) Form an n × (k + p) Gaussian random matrix G.
    int n=A.getRows();
    int m=A.getCols();
    //Matrix G(n,m);
    // code to generate Gaussian random matrix G
    Matrix G=gaussianRandomMatrix(n,m);
    // (2) Form the sample matrix Y = A G.
    Matrix Y = A * G;

    // (3) Orthonormalize the columns of the sample matrix Q = orth(Y).
    std::tuple<Matrix, Matrix> qr_result = qr_decomposition(Y);
    Matrix Q= std::get<0>(qr_result);

    // Stage B
    // (4) Form the (k + p) × n matrix B = Q∗A.
    Matrix B = Q.transpose() * A;

    // (5) Form the SVD of the small matrix B: B = UDV ˆ
    Matrix U_hat;
    PM(B, U_hat, S, V);

    // (6) Form U = QUˆ
    U = Q * U_hat;
    // END
}
    