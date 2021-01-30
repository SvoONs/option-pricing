#include "../include/option.h"

Option::Option(float assetPrice, float strikePrice, float interest, float sigma, float yearsToMaturity, OptionRight right, OptionStyle style)
    : assetPrice(assetPrice),
      strikePrice(strikePrice),
      interest(interest),
      sigma(sigma),
      yearsToMaturity(yearsToMaturity),
      right(right),
      style(style) {}
