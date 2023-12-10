
#ifndef rSVD_H
#define rSVD_H

#include <Eigen/Dense>
#include <Eigen/Sparse>



using mat = Eigen::MatrixXd;
using vet = Eigen::VectorXd;

using mat=Eigen::MatrixXd;
using vet=Eigen::VectorXd;

void intermediate_step(Mat &A,Mat &Q,Mat &Omega,int &l,int &q);
void rSVD(mat& A, mat&U, vet& S, mat& V);


#endif