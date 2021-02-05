#include "../include/utils.h"
#include "gtest/gtest.h"

TEST(TestUtils, TestNormalCDF) {
    // Test some quantiles of normal distribution
    double inv_quant_25 = -1.64;
    ASSERT_NEAR(normalCDF(inv_quant_25), 0.0505, 1e-4);
    double inv_quant_50 = 0;
    ASSERT_EQ(normalCDF(inv_quant_50), 0.5);
    double inv_quant_95 = 1.64;
    ASSERT_NEAR(normalCDF(inv_quant_95), 0.9495, 1e-4);
    // Test tails
    double tail = 10;
    ASSERT_GE(normalCDF(-tail), 0);
    ASSERT_NEAR(normalCDF(-tail), 0, 1e-4);
    ASSERT_LE(normalCDF(tail), 1);
    ASSERT_NEAR(normalCDF(tail), 1, 1e-4);
}

TEST(TestUtils, TestBlackScholes) {
    // examples taken from literature:
    // The complete guide to option pricing formulas, 2nd ed.
    // E.G. Haug, PhD
    Option europeanCall{
        60, 65, 0.08, 0.3, 0.25, OptionRight::Call, OptionStyle::European};
    double valueEC = BlackScholesPrice(europeanCall);
    ASSERT_NEAR(valueEC, 2.1334, 1e-04);
    Option europeanPut{
        60, 65, 0.08, 0.3, 0.25, OptionRight::Put, OptionStyle::European};
    double valueEP = BlackScholesPrice(europeanPut);
    ASSERT_NEAR(valueEP, 5.8462, 1e-04);
}