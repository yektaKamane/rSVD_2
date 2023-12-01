#include "../include/powerMethod/PM1.hpp"
#include "../include/powerMethod/SVD.hpp"

int main() {

    int m = 100;
    int n = 10;
    Mat A = Mat::Random(m, n); // Mat::Random(m, n) generate a random matrix with entries in [-1, 1]

    Vec sigma = Vec::Zero(A.cols());
    Mat U = Mat::Zero(A.rows(), A.cols()); // U m*n
    Mat V = Mat::Zero(A.cols(), A.cols()); // V n*n

    SVD(A, sigma, U, V);

    cout << "FULL SVD" << endl;
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
