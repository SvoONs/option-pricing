#include <cmath>
#include "../include/option.h"

// implementation of cumulative normal distribution function:
// https://en.cppreference.com/w/cpp/numeric/math/erfc
double normalCDF(double x) {
    // Phi(-∞, x) aka N(x)
    return std::erfc(-x / std::sqrt(2)) / 2;
}

double BlackScholesPrice(const Option &option) {
    double d1 = (std::log(option.assetPrice / option.strikePrice) +
                 (option.interest + std::pow(option.sigma, 2) / 2) *
                     (option.yearsToMaturity)) /
                (option.sigma * std::sqrt(option.yearsToMaturity));
    double d2 = d1 - option.sigma * std::sqrt(option.yearsToMaturity);
    double bsPrice;
    if (option.right == OptionRight::Call) {
        bsPrice = option.assetPrice * normalCDF(d1) -
                  option.strikePrice *
                      std::exp(-option.interest * option.yearsToMaturity) *
                      normalCDF(d2);
    } else {
        bsPrice = normalCDF(-d2) * option.strikePrice *
                      std::exp(-option.interest * option.yearsToMaturity) -
                  option.assetPrice * normalCDF(-d1);
    }
    return bsPrice;
}
