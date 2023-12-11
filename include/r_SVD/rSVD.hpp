
#ifndef rSVD_H
#define rSVD_H

#include <Eigen/Dense>
#include <Eigen/Sparse>


using Mat = Eigen::MatrixXd;
using Vet = Eigen::VectorXd;

using Mat=Eigen::MatrixXd;
using Vet=Eigen::VectorXd;

void intermediate_step(Mat &A,Mat &Q,Mat &Omega,int &l,int &q);
void rSVD(Mat& A, Mat&U, Vet& S, Mat& V);


#endif