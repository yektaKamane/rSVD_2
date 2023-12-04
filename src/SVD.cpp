#include "../include/powerMethod/SVD.hpp"

void SVD(Mat &A, Vec &sigma, Mat &U, Mat &V) {
    Mat VT = Mat::Zero(A.cols(), A.cols()); // VT is the transpose of V

    // Define the matrix B = A^T*A
    Mat B = A.transpose()*A;

    // Define auxiliary vectors u and v
    Vec u = Vec::Zero(A.rows());
    Vec v = Vec::Zero(A.cols());
    
    for (int i=0; i<A.cols(); i++) {
        u = U.col(i);
        v = VT.row(i);
        PM(A, B, sigma(i), u, v);
        A -= sigma(i)*u*v.transpose();
        B = A.transpose()*A;
        U.col(i) = u;
        VT.row(i) = v;
    }

    V = VT.transpose(); // VT is the transpose of V
}