#include "gtest/gtest.h"
#include "../include/Option.h"

TEST(TestOption, TestOptionConstructors) {
    Option option{100.0, 105.0, 0.02, 1.0, 2.0};
    ASSERT_EQ(option.assetPrice, 100.0);
    ASSERT_EQ(option.strikePrice, 105.0);
    ASSERT_NEAR(option.interest, 0.02, 1.0e-6);
    ASSERT_EQ(option.sigma, 1.0);
    ASSERT_EQ(option.yearsToMaturity, 2.0);

    EuropeanCall ec{100.0, 105.0, 0.02, 1.0, 2.0};
    ASSERT_EQ(ec.assetPrice, 100.0);
    ASSERT_EQ(ec.strikePrice, 105.0);
    ASSERT_NEAR(ec.interest, 0.02, 1.0e-6);
    ASSERT_EQ(ec.sigma, 1.0);
    ASSERT_EQ(ec.yearsToMaturity, 2.0);
    ASSERT_EQ(ec.right, OptionRight::Call);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}