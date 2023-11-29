// matrix.h
#pragma once
#include <string>
#include <vector>

class Matrix {
private:
    std::vector<std::vector<double>> data;
    int rows;
    int cols;

public:
    Matrix(int rows, int cols);
    Matrix(const std::vector<std::vector<double>>& input_data);

    // Constructor for initialization similar to Eigen
    Matrix(std::initializer_list<std::initializer_list<double>> values);
    Matrix(const std::string& filename);

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

    static Matrix identity(int size);
    void setBlock(int row, int col, const Matrix& block);
    Matrix getBlock(int row, int col, int numRows, int numCols) const;
    
    // Display method
    void display() const;
};
