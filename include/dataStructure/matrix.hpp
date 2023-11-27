// matrix.h
#pragma once

#include <vector>

class Matrix {
private:
    std::vector<std::vector<double>> data;
    int rows;
    int cols;

public:
    Matrix(int rows, int cols);
    Matrix(const std::vector<std::vector<double>>& input_data);

    // Getter methods
    int getRows() const;
    int getCols() const;
    double getElement(int row, int col) const;

    // Setter methods
    void setElement(int row, int col, double value);

    // Matrix operations
    Matrix transpose() const;
    Matrix multiply(const Matrix& other) const;

    // Additional operations specific to the SVD implementation
    // ...

    // Overloaded operators for convenience
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(double scalar) const;
    // ...

    // Display method
    void display() const;
};
