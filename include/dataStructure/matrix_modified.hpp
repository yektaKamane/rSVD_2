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
    Matrix genRandom() const;

    // Getter methods
    int getRows() const;
    int getCols() const;
    double getElement(int row, int col) const;
    Matrix extractCol(int col) const; // Vector extractCol(int col);
    Matrix extractRow(int row) const; // Vector extractRow(int row);

    // Setter methods
    void setElement(int row, int col, double value);
    void setRow(int row, const Matrix& input_data); // void setRow(int row, const Vector& input_data);
    void setCol(int col, const Matrix& input_data); // void setCol(int col, const Vector& input_data);

    // Matrix operations
    Matrix transpose() const;
    Matrix multiply(const Matrix& other) const;
    std::vector<double> mat_vet_multiply(const std::vector<double>& other); // Vector mat_vet_multiply(const Vector& other);
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
