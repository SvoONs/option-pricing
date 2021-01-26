#include "../include/Option.h"

Option::Option(float assetPrice, float strikePrice, float interest, float sigma)
    : assetPrice(assetPrice),
      strikePrice(strikePrice),
      interest(interest),
      sigma(sigma) {}

EuropeanCall::EuropeanCall(float assetPrice, float strikePrice, float interest,
                           float sigma)
    : Option(assetPrice, strikePrice, interest, sigma),
      right(OptionRight::Call) {}
