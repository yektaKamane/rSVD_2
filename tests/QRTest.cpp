#include "../include/QRdecomposition/QR.hpp"
#include "../include/dataStructure/matrix.hpp"


// The main function for running the tests
int main(int argc, char **argv) {
    Matrix A("../data/input/bcsstm01.mtx");
    A.display();
    A.writeNonZeroElementsToCSR("../data/output/bcsstm01_output.mtx");
}
