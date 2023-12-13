#include "../include/r_SVD/rSVD.hpp"
#include "../include/powerMethod/SVD.hpp"
#include "../include/QRdecomposition/QR.hpp"

void intermediate_step(Mat &A, Mat &Q, Mat &Omega, int &l,int &q){
    
    Mat Y0 = A * Omega;
    Mat Q0 (Y0.rows(), Y0.rows());
    Mat R0(Y0.rows(), Y0.cols());
    qr_decomposition_reduced(Y0, Q0, R0);
    
    for (int j = 1; j <= q; j++) {
        Y0 = A.transpose() * Q0;
        
        qr_decomposition_reduced(Y0, Q0, R0);

        Y0 = A * Q0;
        
        qr_decomposition_reduced(Y0, Q0, R0);
        
    }
    Q = Q0;
}


 void rSVD(Mat& A, Mat& U, Vet& S, Mat& V) {
    // Stage A
    // (1) Form an n × (k + p) Gaussian random matrix G.
    int m=A.rows();
    int n=A.cols();
    Mat Omega(n, m);
    

    // Create a random number generator for a normal distribution
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> distribution(0.0, 1.0);

    // Fill the matrix with values from a standard normal distribution
    for (int i = 0; i < Omega.rows(); ++i) {
        for (int j = 0; j < Omega.cols(); ++j) {
            Omega(i, j) = distribution(gen);
        }
    }
    int q=2;
    
    Mat Q(m, m);
    intermediate_step(A, Q, Omega, n, q);
    

    // Stage B
    // (4) Form the (k + p) × n matrix B = Q∗A.
    Mat B = Q.transpose() * A;

    // (5) Form the SVD of the small matrix B: B = UDV ˆ
    Mat U_hat(U.rows(), U.cols());
    //std::cout << "U_hat = \n" << U_hat << std::endl;
    int min= B.rows() < B.cols() ? B.rows() : B.cols();
    SVD(B, S, U_hat, V, min);

    // // (6) Form U = QUˆ
    U = Q * U_hat;
    // END
}
