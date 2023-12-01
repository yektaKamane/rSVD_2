#ifndef QR_H
#define QR_H

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <unsupported/Eigen/SparseExtra>

Eigen::MatrixXd givens_rotation(double a, double b);
std::tuple<Eigen::MatrixXd, Eigen::MatrixXd> qr_decomposition(const Eigen::MatrixXd& A);

#endif
