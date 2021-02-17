#include "Eigen/Dense"

void discountValue(double &value, double discFactor, double t);

double normalCDF(double x);

Eigen::Vector3d fitQuadraticRegression(Eigen::VectorXd &X, Eigen::VectorXd &y);

Eigen::VectorXd predictQuadraticRegression(Eigen::VectorXd &X,
                                           Eigen::Vector3d &betas);