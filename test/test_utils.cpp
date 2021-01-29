#include "gtest/gtest.h"
#include "../include/utils.h"

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

TEST(TestUtils, TestBlackScholesCall) {

}