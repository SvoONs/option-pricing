
enum OptionRight { Call, Put };

struct Option {
    Option(float assetPrice, float strikePrice, float interest, float sigma, float yearsToMaturity);
    float assetPrice;
    float strikePrice;
    float interest;
    float sigma;
    float yearsToMaturity;
};

/*
Different option styles are derived from the base class, see also:
https://en.wikipedia.org/wiki/Option_style
*/

struct EuropeanCall : public Option {
    EuropeanCall(float assetPrice, float strikePrice, float interest,
                 float sigma, float yearsToMaturity);
    OptionRight right;
};
