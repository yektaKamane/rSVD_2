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

    // Getter methods
    int getSize() const;
    double getElement(int index) const;

    // Setter methods
    void setElement(int index, double value);

    // Vector operations
    double dotProduct(const Vector& other) const;

    // Additional operations specific to the SVD implementation
    // ...

    // Overloaded operators for convenience
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(double scalar) const;
    // ...

    // Display method
    void display() const;
};
