#include "../include/powerMethod/PM3.hpp"


int main() {

    int m = 100;
    int n = 10;
    Mat A = Mat(m, n);
    A = A.genRandom(); // FIX
    // A.display();

    Vec sigma = Vec(A.getCols());
    Mat U = Mat(A.getRows(), A.getCols()); // U m*n
    Mat VT = Mat(A.getCols(), A.getCols()); // VT is the transpose of V

    // Define the matrix B = A^T*A
    Mat AT = A.transpose();
    // AT.display();
    Mat B = AT.multiply(A); 
    // B.display();
    Mat aux = Mat(A.getRows(), A.getCols());

    std::cout << "FULL SVD" << endl;

    Vec u = Vec(A.getRows());
    Vec v = Vec(A.getCols());
    double s = 0.0;

    // Auxiliary variables
    Mat uu = Mat(A.getRows(), 1);
    Mat vv = Mat(1, A.getCols());
    vector<double> aux1;
    // aux1.resize(A.getRows());
    vector<double> aux2;
    // aux2.resize(A.getCols());
    vector<vector<double>> aux3;
    // aux3.resize(A.getRows(), vector<double>(A.getCols(), 0.0));
    // aux3.resize(A.getCols(), vector<double>(A.getRows(), 0.0));
    vector<vector<double>> aux4;
    // aux4.resize(A.getRows(), vector<double>(1, 0.0));
    vector<vector<double>> aux5;
    // aux5.resize(1, vector<double>(A.getCols(), 0.0));

    for (int i=0; i<A.getCols(); i++) {
        // It is not necessary to extract u, v, s because U, VT and sigma are initialized at zero
        // u = U.extractCol(i);
        // v = VT.extractRow(i);
        // s = sigma.getElement(i);
        // It is easier to set u, v, s to zero at each iteration
        u = Vec(A.getRows());
        v = Vec(A.getCols());
        s = 0.0;
        aux1.clear();
        aux2.clear();
        aux3.clear();

        PM(A, B, s, u, v);

        // A = A - (u.col_row_product(v.transpose()))*s; initial value of reference to non-const must be an lvalue
        aux2 = v.transpose();
        aux3 = u.col_row_product(aux2); // Error: Vector dimensions are not compatible for column-row product.
        cout << "Check dimensions at the end of one iteration of the power method:" << endl;
        cout << "Expected size of aux2: " << A.getCols() << endl;
        cout << "Real size of aux2    : " << aux2.size() << endl;

        // malloc(): corrupted top size
        A = A - Mat(aux3)*s; // Conversion from vector<vector<double>> to Mat
        B = (A.transpose()).multiply(A); 

        sigma.setElement(i, s);

        aux1 = u.transpose(); // aux2 is already set to v.transpose()
        // aux4 ...
        // aux5 ...
    
        uu = Mat(aux4); // Conversion from vector<double> to Mat
        vv = Mat(aux5); // Conversion from vector<double> to Mat

        U.setCol(i, uu);
        VT.setRow(i, vv);
    }

    Mat V = VT.transpose(); // VT is the transpose of V

    std::cout << "Singular values: " << endl;
    sigma.display();
    

    return 0;
}

