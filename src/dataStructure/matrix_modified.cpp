// matrix.cpp
#include "../../include/dataStructure/matrix_modified.hpp"
#include <iostream>
#include <random>

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    data.resize(rows, std::vector<double>(cols, 0.0));
}

Matrix::Matrix(const std::vector<std::vector<double>>& input_data) : data(input_data) {
    rows = static_cast<int>(data.size());
    cols = (rows > 0) ? static_cast<int>(data[0].size()) : 0;
}

// Generate a random matrix
Matrix Matrix::genRandom() const {
    Matrix result(rows, cols);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            result.setElement(i, j, distribution(gen));
        }
    }

    return result;
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


// Extract a column from a matrix and return it as a vector
Matrix Matrix::extractCol(int col) const {
    Matrix result(rows, 1);

    for (int i=0; i<rows; i++) {
        result.setElement(i, 0, getElement(i, col));
    }

    return result;
}

// Extract a row from a matrix and return it as a vector
Matrix Matrix::extractRow(int row) const{
    Matrix result(1, cols);

    for (int i=0; i<cols; i++) {
        result.setElement(0, i, getElement(row, i));
    }

    return result;
}

void Matrix::setElement(int row, int col, double value) {
    data[row][col] = value;
}

void Matrix::setRow(int row, const Matrix& input_data) { // input_data is a (1*cols) vector
    // Check if input_data has the correct size
    if (cols != input_data.getCols() || 1 != input_data.getRows()) {
        std::cerr << "Error: Vector dimensions are not compatible.\n";
    }

    for (int i=0; i<cols; i++) {
        setElement(row, i, input_data.getElement(i, 0));
    }

}

void Matrix::setCol(int col, const Matrix& input_data) { // input_data is a (rows*1) vector
    // Check if input_data has the correct size
    if (rows != input_data.getRows() || 1 != input_data.getCols()) {
        std::cerr << "Error: Vector dimensions are not compatible.\n";
    }

    for (int i=0; i<cols; i++) {
        setElement(col, i, input_data.getElement(0, i));
    }
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

// Matrix vector multiplication
std::vector<double> Matrix::mat_vet_multiply(const std::vector<double>& other) { // other is a (cols*1) vector
    std::vector<double> result; // (rows*cols) * (cols*1) = (rows*1)
    result.resize(rows);

    // Check if the matrix and the vector can be multiplied
    if (cols != other.size()) {
        std::cerr << "Error: Matrix dimensions are not compatible for multiplication.\n";
        return result;
    }

    for (int i = 0; i < rows; ++i) {
        double sum = 0.0;
        for (int k = 0; k < cols; ++k) {
            sum += getElement(i, k) * other[k];
        }
        result[i] = sum;
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
