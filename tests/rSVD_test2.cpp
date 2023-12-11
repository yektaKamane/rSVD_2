#include "../include/r_SVD/rSVD.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <chrono>
#include <iostream>
#include <filesystem> // C++17 or later
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <unsupported/Eigen/SparseExtra>

// The main function for running the tests
int main(int /*argc*/, char** argv) {
    std::cout << "*** rSVD test ***\n" << std::endl;
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
        Eigen::SparseMatrix<double> sparseMatrix;
        
        Eigen::loadMarket(sparseMatrix, inputFilePath.string());
        Eigen::MatrixXd A = Eigen::MatrixXd(sparseMatrix);
        if (fileName == "simple.mtx") std::cout << A << std::endl;

        // start calculating the time
        auto start = std::chrono::high_resolution_clock::now();

        // Perform rSVD decomposition
        int n = A.rows();
        Mat U = Mat::Zero(n, n);
        Vet S = Vet::Zero(n);
        Mat V = Mat::Zero(n, n);
        rSVD(A, U, S, V);

        // Record the end time
        auto end = std::chrono::high_resolution_clock::now();
        // Calculate the duration
        std::chrono::duration<double> duration = end - start;

        Mat diagonalMatrix = S.asDiagonal();
        Mat A_2(n, n);
        A_2 = U * diagonalMatrix;
        A_2 = A_2 * V;

        Mat diff = A - A_2;
        double norm_of_difference = (A - A_2).norm();

        // Print the duration in seconds
        std::cout << "Dataset: " << fileName << "\n";
        std::cout << "Size: " << A.rows() << ", " << A.cols() << "\n";
        std::cout << "Execution time: " << duration.count() << " seconds" << "\n";
        std::cout << "norm of diff : " << norm_of_difference << "\n";
        std::cout << "-------------------------\n" << std::endl;;

        // Construct the full paths for output files
        std::filesystem::path outputUFilePath = outputDir / ("U_" + fileName + "_output.mtx");
        std::filesystem::path outputSFilePath = outputDir / ("S_" + fileName + "_output.mtx");
        std::filesystem::path outputVFilePath = outputDir / ("V_" + fileName + "_output.mtx");

        // Write Q and R matrices to output files
        Eigen::saveMarket(U, outputUFilePath.string());
        Eigen::saveMarket(S, outputSFilePath.string());
        Eigen::saveMarket(V, outputVFilePath.string());
    }

    return 0;
}
