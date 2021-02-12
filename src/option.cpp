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

double Option::getPayout(double currentAssetPrice) const {
    double payoff;
    if (right == OptionRight::Call) {
        payoff = std::max(currentAssetPrice - this->strikePrice, 0.0);
    } else if (right == OptionRight::Put) {
        payoff = std::max(this->strikePrice - currentAssetPrice, 0.0);
    }
    return payoff;
}

std::ostream &operator<<(std::ostream &os, const Option &option) {
    auto style = option.style == 0 ? "American" : "European";
    auto right = option.right == 0 ? "Call" : "Put";
    os << style << " " << right << " -> "
       << "asset price: " << option.assetPrice << "$"
       << ", strike: " << option.strikePrice << "$"
       << ", interest: " << option.interest * 100 << "%"
       << ", volatility: " << option.sigma * 100 << "%"
       << ", maturity: " << option.yearsToMaturity << " years\n";
    return os;
}