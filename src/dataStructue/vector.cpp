// vector.cpp
#include "vector.h"
#include <iostream>

Vector::Vector(int size) : size(size) {
    data.resize(size, 0.0);
}

Vector::Vector(const std::vector<double>& input_data) : data(input_data) {
    size = static_cast<int>(data.size());
}

int Vector::getSize() const {
    return size;
}

double Vector::getElement(int index) const {
    return data[index];
}

void Vector::setElement(int index, double value) {
    data[index] = value;
}

double Vector::dotProduct(const Vector& other) const {
    // Check if the vectors have the same size
    if (size != other.size) {
        std::cerr << "Error: Vector dimensions are not compatible for dot product.\n";
        return 0.0;
    }

    double result = 0.0;
    for (int i = 0; i < size; ++i) {
        result += getElement(i) * other.getElement(i);
    }
    return result;
}

Vector Vector::operator+(const Vector& other) const {
    Vector result(size);
    for (int i = 0; i < size; ++i) {
        result.setElement(i, getElement(i) + other.getElement(i));
    }
    return result;
}

Vector Vector::operator-(const Vector& other) const {
    Vector result(size);
    for (int i = 0; i < size; ++i) {
        result.setElement(i, getElement(i) - other.getElement(i));
    }
    return result;
}

Vector Vector::operator*(double scalar) const {
    Vector result(size);
    for (int i = 0; i < size; ++i) {
        result.setElement(i, getElement(i) * scalar);
    }
    return result;
}

void Vector::display() const {
    for (int i = 0; i < size; ++i) {
        std::cout << getElement(i) << " ";
    }
    std::cout << "\n";
}
