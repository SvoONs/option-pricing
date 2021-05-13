#ifndef OPTION_H
#define OPTION_H

#include <iostream>

enum OptionRight { Call = 0, Put = 1 };

/*
Different option styles https://en.wikipedia.org/wiki/Option_style
*/
enum OptionStyle { American = 0, European = 1 };

struct Option {
    Option(double assetPrice, double strikePrice, double interest, double sigma,
           double yearsToMaturity, OptionRight right, OptionStyle style, double dividendYield=0);
    const double assetPrice;
    const double strikePrice;
    const double interest;
    const double sigma;
    const double yearsToMaturity;
    const double dividendYield;
    const OptionRight right;
    const OptionStyle style;

    double getPayout(double currentAssetPrice) const;
    friend std::ostream &operator<<(std::ostream &os, const Option &option);
};

#endif