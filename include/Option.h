
enum OptionRight { Call, Put };

class Option {
   public:
    Option(float assetPrice, float strikePrice, float interest, float sigma);
    float assetPrice;
    float strikePrice;
    float interest;
    float sigma;
};

/*
Different option styles are derived from the base class, see also:
https://en.wikipedia.org/wiki/Option_style
*/

class EuropeanCall : public Option {
   public:
    EuropeanCall(float assetPrice, float strikePrice, float interest,
                 float sigma);
    OptionRight right;
};
