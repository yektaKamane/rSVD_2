#include "../include/powerMethod/PM1.hpp"
#include "../include/powerMethod/SVD.hpp"

int main() {

    int m = 3;
    int n = 3;
    Mat A = Mat::Random(m, n); // Mat::Random(m, n) generate a random matrix with entries in [-1, 1]

    Vec sigma = Vec::Zero(A.cols());
    Mat U = Mat::Zero(A.rows(), A.cols()); // U m*n
    Mat V = Mat::Zero(A.cols(), A.cols()); // V n*n

    SVD(A, sigma, U, V);

    cout << "FULL SVD" << endl;
    cout << "Singular values: " << endl << sigma << endl;
    cout << "U: " << endl << U << endl;
    cout << "V: " << endl << V << endl;

    // Export the singular values as csv file
    // ofstream filecsv("sigma.csv");
    // if (filecsv.is_open()) {
    //     Eigen::IOFormat fmt(Eigen::FullPrecision, Eigen::DontAlignCols, "\t", "\n");
    //     filecsv << sigma.format(fmt);
    //     filecsv.close();
    // }

    return 0;
}
