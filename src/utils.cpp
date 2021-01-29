#include "../include/option.h"
#include <cmath>

// implementation of cumulative normal distribution function:
// https://en.cppreference.com/w/cpp/numeric/math/erfc
double normalCDF(double x) {
    // Phi(-∞, x) aka N(x)
    return std::erfc(-x/std::sqrt(2))/2;
}

double Black_Scholes_Call(const EuropeanCall &call) {
    double d1 = (std::log(call.assetPrice/call.strikePrice)+(call.interest+std::pow(call.sigma,2)/2)*(call.yearsToMaturity))/(call.sigma*std::sqrt(call.yearsToMaturity));
    double d2 = d1 - call.sigma*std::sqrt(call.yearsToMaturity);
    double bsPrice = call.strikePrice*std::exp(-call.interest*call.yearsToMaturity)*normalCDF(-d2)-call.assetPrice*normalCDF(-d1);
    return bsPrice;
}