
enum OptionRight { Call, Put };

/*
Different option styles https://en.wikipedia.org/wiki/Option_style
*/
enum OptionStyle { American, European };

struct Option {
    Option(double assetPrice, double strikePrice, double interest, double sigma,
           double yearsToMaturity, OptionRight right, OptionStyle style);
    const double assetPrice;
    const double strikePrice;
    const double interest;
    const double sigma;
    const double yearsToMaturity;
    const OptionRight right;
    const OptionStyle style;

    double getPayoff(double currentAssetPrice) const;
};
