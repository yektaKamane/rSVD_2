// vector.cpp
#include "../../include/dataStructure/vector_modified.hpp"
#include <iostream>
#include <random>

Vector::Vector(int size) : size(size) {
    data.resize(size, 0.0);
}

Vector::Vector(const std::vector<double>& input_data) : data(input_data) {
    size = static_cast<int>(data.size());
}


// Generate a random vector
Vector Vector::genRandom() const {
    Vector result(size);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> distribution(0.0, 1.0);

    for (int i=0; i<size; i++) {
        result.setElement(i,distribution(gen));
    }

    return result;
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


// Compute the Euclidean norm of a vector
double Vector::norm() const {
    double result = 0.0;
    for (int i = 0; i < size; ++i) {
        result += getElement(i) * getElement(i);
    }
    return sqrt(result);
}

// Normalize a vector
Vector Vector::normalize() const {
    Vector result(size);
    result = (*this)/norm();
    return result;
}

// Transpose a vector
// A horizontal vector can be seen as a matrix with one row
/* Matrix Vector::transpose() {
    Matrix result(1, size);

    for (int i=0; i<size; i++) {
        result.setElement(0, i, getElement(i));
    }

    return result;
} */

// Maybe it is better to export the Vector as a std::vector<double> and then create a Matrix from it
std::vector<double> Vector::transpose() {
    // Matrix Vector::transpose()
    // Matrix result(1, size);
    std::vector<double> result;

    for (int i=0; i<size; i++) {
        result.push_back(getElement(i));
    }

    return result;
}


// Compute the product of a column vector and a row vector
// Where the row vector can be seen as a matrix with one row
/* Matrix Vector::col_row_product(const Matrix& other) {
    Matrix result(size, size);

    // Check if the vectors have the same size
    if (size != other.getCols() || 1 != other.getRows()) {
        std::cerr << "Error: Vector dimensions are not compatible for column-row product.\n";
        return result;
    }

    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            result.setElement(i, j, getElement(i) * other.getElement(0, j));
        }
    }

    return result;
} */

// Maybe it is better to export the result as a std::vector<std::vector<double>> and then create a Matrix from it
std::vector<std::vector<double>> Vector::col_row_product(const std::vector<double>& other) {
    std::vector<std::vector<double>> result;
    result.resize(size, std::vector<double>(size, 0.0));

    // Check if the vectors have the same size
    if (size != other.size()) {
        std::cerr << "Error: Vector dimensions are not compatible for column-row product.\n";
        return result;
    }

    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            result[i][j] = getElement(i) * other[j];
        }
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

Vector Vector::operator/(double scalar) const {
    Vector result(size);
    for (int i = 0; i < size; ++i) {
        result.setElement(i, getElement(i) / scalar);
    }
    return result;
}

void Vector::display() const {
    for (int i = 0; i < size; ++i) {
        std::cout << getElement(i) << " ";
    }
    std::cout << "\n";
}
