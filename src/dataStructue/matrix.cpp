// matrix.cpp
#include "matrix.h"
#include <iostream>

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    data.resize(rows, std::vector<double>(cols, 0.0));
}

Matrix::Matrix(const std::vector<std::vector<double>>& input_data) : data(input_data) {
    rows = static_cast<int>(data.size());
    cols = (rows > 0) ? static_cast<int>(data[0].size()) : 0;
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
