#ifndef PM_H
#define PM_H

#include <iostream>
#include <fstream>
#include <random>
#include "../dataStructure/vector_modified.hpp"
#include "../dataStructure/matrix_modified.hpp"

using namespace std;

using Mat = Matrix;
using Vec = Vector;

void PM(Mat &A, Mat &B, double &sigma, Vec &u, Vec &v);

#endif