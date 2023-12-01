// vector.h
#pragma once

#include <vector>

class Vector {
private:
    std::vector<double> data;
    int size;

public:
    Vector(int size);
    Vector(const std::vector<double>& input_data);
    Vector genRandom() const;

    // Getter methods
    int getSize() const;
    double getElement(int index) const;

    // Setter methods
    void setElement(int index, double value);

    // Vector operations
    double dotProduct(const Vector& other) const;

    // Additional operations specific to the SVD implementation
    // ...
    double norm() const;
    Vector normalize() const;
    std::vector<double> transpose(); // Matrix transpose();
    std::vector<std::vector<double>> col_row_product(const std::vector<double>& other); // Matrix col_row_product(const Matrix& other);

    // Overloaded operators for convenience
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(double scalar) const;
    // ...
    Vector operator/(double scalar) const;

    // Display method
    void display() const;
}; 
