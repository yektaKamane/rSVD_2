
#ifndef PM_HPP
#define PM_HPP

#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <random>
#include <cmath>
#include <fstream>


using mat = Eigen::MatrixXd;
using vet = Eigen::VectorXd;
void power_method(mat& m, vet& s, mat& U, mat& V);

#endif 
