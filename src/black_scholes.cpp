#include "../include/black_scholes.h"
#include <cmath>
#include "../include/utils.h"

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