#include "../include/r_SVD/rSVD.hpp"
#include "../include/powerMethod/SVD.hpp"
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
    const mat Y = A * G;

    // (3) Orthonormalize the columns of the sample matrix Q = orth(Y).
    auto [Q,R]= qr_decomposition(Y);
    

    // Stage B
    // (4) Form the (k + p) × n matrix B = Q∗A.
    mat B = Q.transpose() * A;

    // (5) Form the SVD of the small matrix B: B = UDV ˆ
    mat U_hat;
    power_method(B, S, U_hat, V);

    // (6) Form U = QUˆ
    U = Q * U_hat;
    // END
}

int main(){
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