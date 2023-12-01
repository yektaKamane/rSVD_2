
#ifndef rSVD_H
#define rSVD_H

#include "../powerMethod/PM.hpp"
#include "../QRdecomposition/QR.hpp"
#include <Eigen/Dense>

using mat=Eigen::MatrixXd;
using vet=Eigen::VectorXd;

void rSVD(mat& A, mat&U, vet& S, mat& V);


#endif
