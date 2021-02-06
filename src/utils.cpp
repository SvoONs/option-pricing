#include <cmath>

void discountValue(double &value, double discFactor, double t) {
    value *= std::exp(-discFactor * t);
}

// implementation of cumulative normal distribution function:
// https://en.cppreference.com/w/cpp/numeric/math/erfc
double normalCDF(double x) {
    // Phi(-∞, x) aka N(x)
    return std::erfc(-x / std::sqrt(2)) / 2;
}
