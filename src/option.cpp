#include "../include/option.h"
#include <algorithm>

Option::Option(double assetPrice, double strikePrice, double interest,
               double sigma, double yearsToMaturity, OptionRight right,
               OptionStyle style)
    : assetPrice(assetPrice),
      strikePrice(strikePrice),
      interest(interest),
      sigma(sigma),
      yearsToMaturity(yearsToMaturity),
      right(right),
      style(style) {}

double Option::getPayoff(double currentAssetPrice) const {
    double payoff;
    if (right == OptionRight::Call) {
        payoff = std::max(currentAssetPrice - this->strikePrice, 0.0);
    } else if (right == OptionRight::Put) {
        payoff = std::max(this->strikePrice - currentAssetPrice, 0.0);
    }
    return payoff;
}