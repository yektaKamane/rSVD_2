#include "../include/powerMethod/PM3.hpp"

// CHECK: the dimensions of the auxiliary standard vectors are correct
// PROBLEM: A, A.transpose(), B are null matrices, so x0 becomes a -nan vector
// FIX: call A = A.genRandom() not only A.genRandom() because it is a non void method

void PM(Mat &A, Mat &B, double &sigma, Vec &u, Vec &v) {
    // Generate a random initial guess x0 (normal distribution)
    Vec x0 = Vec(A.getCols());
    x0 = x0.genRandom(); // FIX

    // Normalize the initial guess x0
    x0 = x0.normalize(); // FIX
    std::cout << "Check norm of x0: " << x0.norm() << endl;

    // Define the number of iterations
    double epsilon = 1.e-10;
    double delta = 0.05;
    double lambda = 0.1;
    int s = ceil( log(4*log(2*A.getCols()/delta)/(epsilon*delta)) /(2*lambda));
    // cout << "Check the number of iterations: " << s << endl;

    /*for (int i=1; i<=s; i++) { 
        x0 = B.mat_vet_multiply(x0); // B = A^T*A
        x0.normalize();
    }
    */

    // Mat aux1 = Mat(1, A.getCols());
    // Mat aux2 = Mat(A.getCols(), 1);
    // Mat aux3 = Mat(A.getRows(), 1);
    vector<double> aux1;
    // vector<vector<double>> aux2;
    // aux2.resize(A.getCols(), vector<double>(1, 0.0));
    Vec aux2 = Vec(A.getRows());
    vector<double> aux3;
    for (int i=1; i<=s; i++) {
        aux1.clear();
        aux3.clear();
        aux1 = x0.transpose(); // This is equivalent to vec_as_mat
        // aux2
        aux3 = B.mat_vet_multiply(aux1); // B = A^T*A
        Vec aux4 = Vec(aux3); // Conversion from vector<double> to Vec
        x0 = aux4;
        x0 = x0.normalize(); // FIX
    }

    cout << "Check dimensions at the end of the for loop:" << endl;
    cout << "Expected size of aux1: " << A.getCols() << endl;
    cout << "Real size of aux1    : " << aux1.size() << endl;
    cout << "Expected size of B   : " << A.getCols() << " * " << A.getCols() << endl;
    cout << "Real size of B       : " << B.getRows() << " * " << B.getCols() << endl;
    cout << "Expected size of aux3: " << A.getCols() << endl;
    cout << "Real size of aux3    : " << aux3.size() << endl;
    aux1.clear();
    aux3.clear();

    // Compute the left singlular vector
    v = x0;
    v = v.normalize(); // FIX
    aux1 = v.transpose();
    aux3 = A.mat_vet_multiply(aux1);
    aux2 = Vec(aux3); // Conversion from vector<double> to Vec

    // Compute the singular value
    sigma = (aux2).norm();

    // Compute the right singular vector
    u = aux2/sigma;

    cout << "Check dimensions outside the for loop:" << endl;
    cout << "Expected size of aux1: " << A.getCols() << endl;
    cout << "Real size of aux1    : " << aux1.size() << endl;
    cout << "Expected size of aux3: " << A.getRows() << endl;
    cout << "Real size of aux3    : " << aux3.size() << endl;

    cout << endl;
    cout << "Singular value: " << sigma << endl;
    cout << endl;
    /*
    cout << "Right singular vector: " << endl;
    u.display();
    cout << endl;
    cout << "Left singular vector: " << endl;
    v.display();
    cout << endl;
    */
    // Everything seems to be okay inside this functions
}


