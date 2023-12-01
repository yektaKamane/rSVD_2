#include "../include/r_SVD/rSVD.hpp"

#include "../include/powerMethod/PM2_full.hpp"
#include "../include/powerMethod/PM.hpp"
#include "../include/QRdecomposition/QR.hpp"


 void rSVD(mat& A, mat& U, vet& S, mat& V) {
    // Stage A
    // (1) Form an n × (k + p) Gaussian random matrix G.
    int n=A.rows();
    int m=A.cols();
    //Matrix G(n,m);
    // code to generate Gaussian random matrix G
    mat G = mat::Random(n, m);
    // (2) Form the sample matrix Y = A G.
    mat Y = A * G;

    // (3) Orthonormalize the columns of the sample matrix Q = orth(Y).
    std::tuple<mat, mat> qr_result = qr_decomposition(Y);
    mat Q = std::get<0>(qr_result);

    // Stage B
    // (4) Form the (k + p) × n matrix B = Q∗A.
    mat B = Q.transpose() * A;

    // (5) Form the SVD of the small matrix B: B = UDV ˆ
    mat U_hat;
    PM(B, U_hat, S, V);

    // (6) Form U = QUˆ
    U = Q * U_hat;
    // END
}
    