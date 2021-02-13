#include "Eigen/Core"

void discountValue(double &value, double discFactor, double t);

double normalCDF(double x);

Eigen::Vector3d quadraticRegression(Eigen::MatrixXd &X, Eigen::VectorXd &y);