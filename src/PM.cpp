#include "../include/powerMethod/PM.hpp"

void PM(Mat &A, Mat &B, double &sigma, Vec &u, Vec &v) {
    // Generate a random initial guess x0
    Vec x0 = Vec::Zero(A.cols()); // To multiply B with x0

    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double> distribution(0.0, 1.0);

    for (unsigned int i=0; i<x0.size(); i++) {
        x0(i) = distribution(gen);
    }
    x0.normalize();
    // cout << "Check norm of x0: " << x0.norm() << endl;

    // Define the number of iterations
    double epsilon = 1.e-10;
    double delta = 0.05;
    double lambda = 0.1;
    int s = ceil( log(4*log(2*A.cols()/delta)/(epsilon*delta)) /(2*lambda));
    // cout << "Check the number of iterations: " << s << endl;

    for (unsigned int i=1; i<=s; i++) {
        x0 = B*x0; // B = A^T*A
        x0.normalize();
    }

    // Compute the left singlular vector
    v = x0;
    v.normalize();

    // Compute the singular value
    sigma = (A*v).norm();

    // Compute the right singular vector
    u = A*v/sigma;

}

/*
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
    }

    V = VT.transpose(); // VT is the transpose of V
}
*/


