
enum OptionRight { Call, Put };

/*
Different option styles https://en.wikipedia.org/wiki/Option_style
*/
enum OptionStyle { American, European };

struct Option {
    Option(float assetPrice, float strikePrice, float interest, float sigma,
           float yearsToMaturity, OptionRight right, OptionStyle style);
    const float assetPrice;
    const float strikePrice;
    const float interest;
    const float sigma;
    const float yearsToMaturity;
    const OptionRight right;
    const OptionStyle style;
};
