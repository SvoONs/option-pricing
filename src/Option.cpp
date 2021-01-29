#include "../include/option.h"

Option::Option(float assetPrice, float strikePrice, float interest, float sigma, float yearsToMaturity)
    : assetPrice(assetPrice),
      strikePrice(strikePrice),
      interest(interest),
      sigma(sigma),
      yearsToMaturity(yearsToMaturity) {}

EuropeanCall::EuropeanCall(float assetPrice, float strikePrice, float interest,
                           float sigma, float yearsToMaturity)
    : Option(assetPrice, strikePrice, interest, sigma, yearsToMaturity),
      right(OptionRight::Call) {}
