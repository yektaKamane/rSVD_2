#include "../include/QRdecomposition/QR.hpp"
#include "../include/dataStructure/matrix.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <iostream>
#include <filesystem> // C++17 or later


// The main function for running the tests
int main(int argc, char** argv) {
    std::cout << "test 1" << std::endl;
    // Get the path to the directory where the executable is located
    std::filesystem::path exePath = std::filesystem::absolute(argv[0]);
    std::filesystem::path exeDir = exePath.parent_path();

    // Set the current working directory to the directory of the executable
    std::filesystem::current_path(exeDir);

    Matrix A("../data/input/west0067.mtx");
    auto [Q, R] = qr_decomposition(A);

    Q.writeNonZeroElementsToCSR("../data/output/Q_west0067_output.mtx");
    R.writeNonZeroElementsToCSR("../data/output/R_west0067_output.mtx");


    return 0;
}
