#include "../include/option.h"
#include "gtest/gtest.h"

TEST(TestOption, TestOptionConstructors) {
    Option americanCall{
        100.0, 105.0, 0.02, 1.0, 2.0, OptionRight::Call, OptionStyle::American};
    ASSERT_EQ(americanCall.assetPrice, 100.0);
    ASSERT_EQ(americanCall.strikePrice, 105.0);
    ASSERT_NEAR(americanCall.interest, 0.02, 1.0e-6);
    ASSERT_EQ(americanCall.sigma, 1.0);
    ASSERT_EQ(americanCall.yearsToMaturity, 2.0);
    ASSERT_EQ(americanCall.right, OptionRight::Call);
    ASSERT_EQ(americanCall.style, OptionStyle::American);

    Option europeanCall{
        100.0, 105.0, 0.02, 1.0, 2.0, OptionRight::Call, OptionStyle::European};
    ASSERT_EQ(europeanCall.assetPrice, 100.0);
    ASSERT_EQ(europeanCall.strikePrice, 105.0);
    ASSERT_NEAR(europeanCall.interest, 0.02, 1.0e-6);
    ASSERT_EQ(europeanCall.sigma, 1.0);
    ASSERT_EQ(europeanCall.yearsToMaturity, 2.0);
    ASSERT_EQ(europeanCall.right, OptionRight::Call);
    ASSERT_EQ(europeanCall.style, OptionStyle::European);
}

TEST(TestOption, TestGetPayoff) {
    Option europeanCall{
        100.0, 105.0, 0.02, 1.0, 2.0, OptionRight::Call, OptionStyle::European};
    Option europeanPut{
        100.0, 105.0, 0.02, 1.0, 2.0, OptionRight::Put, OptionStyle::European};

    double assetPriceT1 = 100.0;
    ASSERT_EQ(europeanCall.getPayout(assetPriceT1), 0.0);
    ASSERT_EQ(europeanPut.getPayout(assetPriceT1), 5.0);

    double assetPriceT2 = 110.0;
    ASSERT_EQ(europeanCall.getPayout(assetPriceT2), 5.0);
    ASSERT_EQ(europeanPut.getPayout(assetPriceT2), 0.0);

    double assetPriceT3 = 105.0;
    ASSERT_EQ(europeanCall.getPayout(assetPriceT3), 0.0);
    ASSERT_EQ(europeanPut.getPayout(assetPriceT3), 0.0);
}
