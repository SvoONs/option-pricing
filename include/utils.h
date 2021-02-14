#include "Eigen/Dense"

void discountValue(double &value, double discFactor, double t);

double normalCDF(double x);

Eigen::Vector3d quadraticRegression(Eigen::VectorXd &X, Eigen::VectorXd &y);