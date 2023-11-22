
#include "PM.hpp"

void power_method(mat& m, vet& s, mat& U, mat& V) {
    if(m.norm()==0){
        std::cout<<"null matrix"<<std::endl;
        return;

    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> distribuzione(0.0, 1.0);

    size_t dimensione_vettore = m.cols();

    Eigen::VectorXd initial_guess(dimensione_vettore);
    vet auxx, v1, u1;
    double s1;
    size_t dim = (m.rows() < m.cols()) ? m.rows() : m.cols();
    for (size_t j = 0; j < dim; ++j) {
        for (size_t i = 0; i < dimensione_vettore; ++i) {
            initial_guess(i) = distribuzione(gen);
        }

        mat aux = m.transpose() * m;
        double epsilon = 1.e-8, delta = 0.05, lambda = 0.1;
        size_t stop = log((4 * log((2 * m.cols()) / delta)) / (epsilon * delta)) / (2 * lambda);
        
        for (size_t i = 0; i < stop; ++i) {
            initial_guess = aux * initial_guess;
            initial_guess = initial_guess / initial_guess.norm();
        }

        v1 = initial_guess;
        s1 = (m * v1).norm();
        u1 = (m * v1) / s1;
        s(j) = s1;
        U.col(j) = u1;
        V.col(j) = v1;
        auxx = s1 * u1;
        m = m - (auxx * v1.transpose());
    }
}



