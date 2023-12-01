#include "PM1.hpp"
#include "SVD.hpp"

// #include "../include/powerMethod/PM1.hpp"
// #include "../include/powerMethod/SVD.hpp"
// #include "../include/dataStructure/vector_modified.hpp"
// #include "../include/dataStructure/matrix_modified.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <iostream>
#include <filesystem> // C++17 or later

// The main function for running the tests
int main(int /*argc*/, char** argv) {
    // Get the path to the directory where the executable is located
    std::filesystem::path exePath = std::filesystem::absolute(argv[0]);
    std::filesystem::path exeDir = exePath.parent_path();
    // Get the path to the root of the project
    std::filesystem::path root = exeDir.parent_path();

    // Input and output directories
    std::filesystem::path inputDir = root / "data" / "input";
    std::filesystem::path outputDir = root / "data" / "output";

    // Create output directory if it doesn't exist
    if (!std::filesystem::exists(outputDir))
        std::filesystem::create_directory(outputDir);

    // Array to store file names
    std::vector<std::string> fileNames;

    // Iterate over files in the input directory
    for (const auto& entry : std::filesystem::directory_iterator(inputDir)) {
        if (entry.is_regular_file()) {
            fileNames.push_back(entry.path().filename().string());
        }
    }

    // Loop over file names
    for (const auto& fileName : fileNames) {
        // Construct the full path for input file
        std::filesystem::path inputFilePath = inputDir / fileName;

        // Load matrix from the input file
        Mat A(inputFilePath.string());

        // Perform SVD
        Vec sigma = Vec::Zero(A.cols());
        Mat U = Mat::Zero(A.rows(), A.cols()); // U m*n
        Mat V = Mat::Zero(A.cols(), A.cols()); // V n*n

        SVD(A, sigma, U, V);

        cout << "FULL SVD" << endl;
        cout << "Singular values: " << endl << sigma << endl;

        /*
        // Construct the full paths for output files
        std::filesystem::path outputSigmaFilePath = outputDir / ("sigma_" + fileName + "_output.mtx");
        std::filesystem::path outputUFilePath = outputDir / ("U_" + fileName + "_output.mtx");
        std::filesystem::path outputVFilePath = outputDir / ("V_" + fileName + "_output.mtx");

        // Write to output files
        sigma.writeNonZeroElementsToCSR(outputSigmaFilePath.string());
        U.writeNonZeroElementsToCSR(outputUFilePath.string());
        V.writeNonZeroElementsToCSR(outputVFilePath.string());
        */

        // Export the singular values as csv file
        ofstream filecsv("sigma_" + fileName + ".csv");
        if (filecsv.is_open()) {
        Eigen::IOFormat fmt(Eigen::FullPrecision, Eigen::DontAlignCols, "\t", "\n");
        filecsv << sigma.format(fmt);
        filecsv.close();
        }

        // B is not declared in this scope
        // Export B = A^T*A as mtx file in Matrix Market format
        // SpMat BS = B.sparseView(); // sparseView() returns a sparse view of the dense matrix B, it does not convert B into a sparse matrix
        // string matrixFileOut("./Brandom_" + fileName + ".mtx");
        // saveMarket(BS, matrixFileOut);

        // Export U as mtx file in Matrix Market format
        SpMat US = U.sparseView();
        string matrixFileOut("./U_" + fileName + ".mtx");
        saveMarket(US, matrixFileOut);

        // Export V as mtx file in Matrix Market format
        SpMat VS = V.sparseView();
        string matrixFileOut1("./V_" + fileName + ".mtx");
        saveMarket(VS, matrixFileOut1);

    }

    return 0;
}




