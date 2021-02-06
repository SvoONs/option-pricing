#include "../include/black_scholes.h"
#include "gtest/gtest.h"

// examples taken from literature:
// The complete guide to option pricing formulas, 2nd ed.
// E.G. Haug, PhD

TEST(TestBlackScholes, TestBlackScholesCall) {
    Option europeanCall{
        60, 65, 0.08, 0.3, 0.25, OptionRight::Call, OptionStyle::European};
    double valueEC = BlackScholesPrice(europeanCall);
    ASSERT_NEAR(valueEC, 2.1334, 1e-04);
}

TEST(TestBlackScholes, TestBlackScholesPut) {
    Option europeanPut{
        60, 65, 0.08, 0.3, 0.25, OptionRight::Put, OptionStyle::European};
    double valueEP = BlackScholesPrice(europeanPut);
    ASSERT_NEAR(valueEP, 5.8462, 1e-04);
}