// matrix.cpp
#include "../../include/dataStructure/matrix.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    data.resize(rows, std::vector<double>(cols, 0.0));
}

Matrix::Matrix(const std::vector<std::vector<double>>& input_data) : data(input_data) {
    rows = static_cast<int>(data.size());
    cols = (rows > 0) ? static_cast<int>(data[0].size()) : 0;
}

// initialize by immediate values
Matrix::Matrix(std::initializer_list<std::initializer_list<double>> values) {
    // Determine the number of rows and columns
    rows = static_cast<int>(values.size());
    cols = (rows > 0) ? static_cast<int>(values.begin()->size()) : 0;

    // Resize the matrix
    data.resize(rows, std::vector<double>(cols, 0.0));

    // Copy values from the initializer list to the matrix
    int i = 0;
    for (const auto& row : values) {
        int j = 0;
        for (const auto& value : row) {
            data[i][j] = value;
            ++j;
        }
        ++i;
    }
}

// initialize by file
Matrix::Matrix(const std::string& filename) {
    // Open the .mtx file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        // Handle the error as needed, e.g., throw an exception
        return;
    }

    // Read the header line (skip it for now)
    std::string header;
    std::getline(file, header);

    // Read the matrix dimensions from the second line
    file >> rows >> cols;

    // Resize the matrix data vector
    data.resize(rows, std::vector<double>(cols, 0.0));

    // Read the matrix values from the file
    int numNonZero;
    file >> numNonZero;

    for (int i = 0; i < numNonZero; ++i) {
        int row, col;
        double value;
        file >> row >> col >> value;

        // Check if the read operation was successful
        if (!file) {
            std::cerr << "Error reading data from file: " << filename << std::endl;
            // Handle the error as needed, e.g., throw an exception
            return;
        }

        // Set the matrix element
        setElement(row - 1, col - 1, value);  // Adjust indices to start from 0
    }

    // Close the file
    file.close();
}


int Matrix::getRows() const {
    return rows;
}

int Matrix::getCols() const {
    return cols;
}

double Matrix::getElement(int row, int col) const {
    return data[row][col];
}

void Matrix::setElement(int row, int col, double value) {
    data[row][col] = value;
}

Matrix Matrix::transpose() const {
    Matrix result(cols, rows);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.setElement(j, i, getElement(i, j));
        }
    }
    return result;
}

Matrix Matrix::multiply(const Matrix& other) const {
    // Check if the matrices can be multiplied
    if (cols != other.rows) {
        std::cerr << "Error: Matrix dimensions are not compatible for multiplication.\n";
        return Matrix(0, 0);
    }

    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            double sum = 0.0;
            for (int k = 0; k < cols; ++k) {
                sum += getElement(i, k) * other.getElement(k, j);
            }
            result.setElement(i, j, sum);
        }
    }
    return result;
}

Matrix Matrix::operator+(const Matrix& other) const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.setElement(i, j, getElement(i, j) + other.getElement(i, j));
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.setElement(i, j, getElement(i, j) - other.getElement(i, j));
        }
    }
    return result;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.setElement(i, j, getElement(i, j) * scalar);
        }
    }
    return result;
}

void Matrix::display() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << getElement(i, j) << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

Matrix Matrix::identity(int size) {
    Matrix result(size, size);
    for (int i = 0; i < size; ++i) {
        result.setElement(i, i, 1.0);
    }
    return result;
}

void Matrix::setBlock(int row, int col, const Matrix& block) {
    int blockRows = block.getRows();
    int blockCols = block.getCols();

    for (int i = 0; i < blockRows; ++i) {
        for (int j = 0; j < blockCols; ++j) {
            setElement(row + i, col + j, block.getElement(i, j));
        }
    }
}

Matrix Matrix::getBlock(int row, int col, int numRows, int numCols) const {
    Matrix block(numRows, numCols);

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            block.setElement(i, j, getElement(row + i, col + j));
        }
    }

    return block;
}
