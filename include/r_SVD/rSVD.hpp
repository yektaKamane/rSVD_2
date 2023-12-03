
#ifndef rSVD_H
#define rSVD_H

<<<<<<< HEAD
#include <Eigen/Dense>
#include <Eigen/Sparse>


using mat = Eigen::MatrixXd;
using vet = Eigen::VectorXd;
=======
#include "../powerMethod/PM.hpp"
#include "../QRdecomposition/QR.hpp"
#include <Eigen/Dense>

>>>>>>> c1319e7f2034c2526958ac833863c0d4306f2750

using mat=Eigen::MatrixXd;
using vet=Eigen::VectorXd;

void rSVD(mat& A, mat&U, vet& S, mat& V);


#endif
