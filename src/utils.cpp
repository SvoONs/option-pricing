#include <cmath>
#include "../include/utils.h"

void discountValue(double &value, double discFactor, double t) {
    value *= std::exp(-discFactor * t);
}

// implementation of cumulative normal distribution function:
// https://en.cppreference.com/w/cpp/numeric/math/erfc
double normalCDF(double x) {
    // Phi(-∞, x) aka N(x)
    return std::erfc(-x / std::sqrt(2)) / 2;
}

Eigen::Vector3d quadraticRegression(Eigen::VectorXd &X, Eigen::VectorXd &y) {
    int n = X.cols();
    Eigen::MatrixXd XMat = Eigen::ArrayXd::Ones(n, 3);
    XMat.col(1) = X;
    XMat.col(2) = X.array().square();
    Eigen::MatrixXd XMatTmp = (X.transpose()*X).inverse()*X.transpose();
    return XMatTmp*y;
}