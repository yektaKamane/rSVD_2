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
        Matrix A(inputFilePath.string());

        // Perform QR decomposition
        auto [Q, R] = qr_decomposition(A);

        // Construct the full paths for output files
        std::filesystem::path outputQFilePath = outputDir / ("Q_" + fileName + "_output.mtx");
        std::filesystem::path outputRFilePath = outputDir / ("R_" + fileName + "_output.mtx");

        // Write Q and R matrices to output files
        Q.writeNonZeroElementsToCSR(outputQFilePath.string());
        R.writeNonZeroElementsToCSR(outputRFilePath.string());
    }

    return 0;
}
