#include "../include/powerMethod/PM1.hpp"
#include "../include/powerMethod/SVD.hpp"
// #include "../include/dataStructure/vector_modified.hpp"
// #include "../include/dataStructure/matrix_modified.hpp"

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

using SpMat = Eigen::SparseMatrix<double>;

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
        SpMat AS;
        loadMarket(AS, inputFilePath.string());

        Mat A = Mat(AS);
        Mat A1 = A.topLeftCorner(A.rows(), ceil(A.cols()/3));
        Mat A2 = A.topLeftCorner(ceil(A.rows()/2), A.cols());

        auto start = std::chrono::high_resolution_clock::now();
        // Perform SVD
        const int dim1 = (A1.rows() < A1.cols()) ? A1.rows() : A1.cols();
        Vec sigma1 = Vec::Zero(dim1);
        Mat U1 = Mat::Zero(A1.rows(), dim1); // U m*n or m*m
        Mat V1 = Mat::Zero(dim1, A1.cols()); // V n*n or m*n

        // Perform SVD
        const int dim2 = (A2.rows() < A2.cols()) ? A2.rows() : A2.cols();
        Vec sigma2 = Vec::Zero(dim2);
        Mat U2 = Mat::Zero(A2.rows(), dim2); // U m*n or m*m
        Mat V2 = Mat::Zero(dim2, A2.cols()); // V n*n or m*n

        SVD(A1, sigma1, U1, V1, dim1);
        SVD(A2, sigma2, U2, V2, dim2);

        cout << "THIN SVD" << endl;
        cout << "Singular values 1: " << endl << sigma1 << endl;
        cout << "Expected dimension: " << ceil(A.cols()/3) << endl;
        cout << "Real dimension:     " << dim1 << endl;
        
        std::cout << "-------------------------\n" << std::endl;
        cout << "Singular values 2: " << endl << sigma2 << endl;
        cout << "Expected dimension: " << ceil(A.rows()/2) << endl;
        cout << "Real dimension:     " << dim2 << endl;

        // Record the end time
        auto end = std::chrono::high_resolution_clock::now();
        // Calculate the duration
        std::chrono::duration<double> duration = end - start;
        // Print the duration in seconds
        std::cout << "\nDataset: " << fileName << "\n";
        std::cout << "Size: " << A.rows() << ", " << A.cols() << "\n";
        std::cout << "Execution time: " << duration.count() << " seconds" << "\n";
        std::cout << "-------------------------\n" << std::endl;

        // Construct the full paths for output files
        std::filesystem::path outputSigma1FilePath = outputDir / ("sigma1_" + fileName + "_output.csv");
        std::filesystem::path outputU1FilePath = outputDir / ("U1_" + fileName + "_output.mtx");
        std::filesystem::path outputV1FilePath = outputDir / ("V1_" + fileName + "_output.mtx");

        std::filesystem::path outputSigma2FilePath = outputDir / ("sigma2_" + fileName + "_output.csv");
        std::filesystem::path outputU2FilePath = outputDir / ("U2_" + fileName + "_output.mtx");
        std::filesystem::path outputV2FilePath = outputDir / ("V2_" + fileName + "_output.mtx");

        // Write matrices to output files
        saveMarket(sigma1, outputSigma1FilePath.string());
        saveMarket(U1, outputU1FilePath.string());
        saveMarket(V1, outputV1FilePath.string());

        saveMarket(sigma2, outputSigma2FilePath.string());
        saveMarket(U2, outputU2FilePath.string());
        saveMarket(V2, outputV2FilePath.string());

        // // Export the singular values as csv file
        // ofstream filecsv1("sigma1_" + fileName + ".csv");
        // if (filecsv1.is_open()) {
        // Eigen::IOFormat fmt(Eigen::FullPrecision, Eigen::DontAlignCols, "\t", "\n");
        // filecsv1 << sigma1.format(fmt);
        // filecsv1.close();
        // }

        // // Export the singular values as csv file
        // ofstream filecsv2("sigma2_" + fileName + ".csv");
        // if (filecsv2.is_open()) {
        // Eigen::IOFormat fmt(Eigen::FullPrecision, Eigen::DontAlignCols, "\t", "\n");
        // filecsv2 << sigma2.format(fmt);
        // filecsv2.close();
        // }

        // // B is not declared in this scope
        // // Export B = A^T*A as mtx file in Matrix Market format
        // // SpMat BS = B.sparseView(); // sparseView() returns a sparse view of the dense matrix B, it does not convert B into a sparse matrix
        // // string matrixFileOut("./Brandom_" + fileName + ".mtx");
        // // saveMarket(BS, matrixFileOut);

        // // Export U as mtx file in Matrix Market format
        // SpMat US1 = U1.sparseView();
        // string matrixFileOut1("./U1_" + fileName + ".mtx");
        // saveMarket(US1, matrixFileOut1);

        // // Export V as mtx file in Matrix Market format
        // SpMat VS1 = V1.sparseView();
        // string matrixFileOut3("./V1_" + fileName + ".mtx");
        // saveMarket(VS1, matrixFileOut3);

        // // Export U as mtx file in Matrix Market format
        // SpMat US2 = U2.sparseView();
        // string matrixFileOut2("./U2_" + fileName + ".mtx");
        // saveMarket(US2, matrixFileOut2);

        // // Export V as mtx file in Matrix Market format
        // SpMat VS2 = V2.sparseView();
        // string matrixFileOut4("./V2_" + fileName + ".mtx");
        // saveMarket(VS2, matrixFileOut4);

    }

    return 0;
}
