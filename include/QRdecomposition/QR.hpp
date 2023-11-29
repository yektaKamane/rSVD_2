#ifndef QR_H
#define QR_H

#include <iostream>
#include <tuple>
#include <cmath>
#include "../include/dataStructure/matrix.hpp"



Matrix givens_rotation(double a, double b);
std::tuple<Matrix, Matrix> qr_decomposition(const Matrix& A);

#endif
