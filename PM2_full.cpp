#include "PM2_full.hpp"

void PM(Mat &A, Mat &B, double &sigma, Vec &u, Vec &v) {
    // Generate a random initial guess x0
    Vec x0 = Vec::Zero(A.cols());

    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double> distribution(0.0, 1.0);

    for (int i=0; i<x0.size(); i++) {
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

    for (int i=1; i<=s; i++) {
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


int main() {

    int m = 100;
    int n = 10;
    Mat A = Mat::Random(m, n); // Mat::Random(m, n) generate a random matrix with entries in [-1, 1]

    /*
    double sigma = 0.0;
    Vec u = Vec::Zero(A.rows());
    Vec v = Vec::Zero(A.cols());
    */

    Vec sigma = Vec::Zero(A.cols());
    Mat U = Mat::Zero(A.rows(), A.cols()); // U m*n
    Mat VT = Mat::Zero(A.cols(), A.cols()); // VT is the transpose of V

    // Define the matrix B = A^T*A
    Mat B = A.transpose()*A;
    Mat aux = Mat::Zero(A.rows(), A.cols());

    cout << "FULL SVD" << endl;

    Vec u = Vec::Zero(A.rows());
    Vec v = Vec::Zero(A.cols());
    for (int i=0; i<A.cols(); i++) {
        u = U.col(i);
        v = VT.row(i);
        PM(A, B, sigma(i), u, v);
        A -= sigma(i)*u*v.transpose();
        B = A.transpose()*A;
    }

    Mat V = VT.transpose(); // VT is the transpose of V

    cout << "Singular values: " << endl << sigma << endl;

    // Export the singular values as csv file
    ofstream filecsv("sigma.csv");
    if (filecsv.is_open()) {
        Eigen::IOFormat fmt(Eigen::FullPrecision, Eigen::DontAlignCols, "\t", "\n");
        filecsv << sigma.format(fmt);
        filecsv.close();
    }

    /*
    // Export A as csv file
    ofstream filecsv("Arandom.csv");
    if (filecsv.is_open()) {
        Eigen::IOFormat fmt(Eigen::FullPrecision, Eigen::DontAlignCols, "\t", "\n");
        filecsv << A.format(fmt);
        filecsv.close();
    }

    // Export B = A^T*A as mtx file in Matrix Market format
    SpMat BS = B.sparseView(); // sparseView() returns a sparse view of the dense matrix B, it does not convert B into a sparse matrix
    string matrixFileOut("./Brandom.mtx");
    saveMarket(BS, matrixFileOut);
    */

    return 0;
}
