#include "gtest/gtest.h"
#include "../include/option.h"

TEST(TestOption, TestOptionConstructors) {
    Option americanCall{100.0, 105.0, 0.02, 1.0, 2.0, OptionRight::Call, OptionStyle::American };
    ASSERT_EQ(americanCall.assetPrice, 100.0);
    ASSERT_EQ(americanCall.strikePrice, 105.0);
    ASSERT_NEAR(americanCall.interest, 0.02, 1.0e-6);
    ASSERT_EQ(americanCall.sigma, 1.0);
    ASSERT_EQ(americanCall.yearsToMaturity, 2.0);
    ASSERT_EQ(americanCall.right, OptionRight::Call);
    ASSERT_EQ(americanCall.style, OptionStyle::American);

    Option europeanCall{100.0, 105.0, 0.02, 1.0, 2.0, OptionRight::Call, OptionStyle::European };
    ASSERT_EQ(europeanCall.assetPrice, 100.0);
    ASSERT_EQ(europeanCall.strikePrice, 105.0);
    ASSERT_NEAR(europeanCall.interest, 0.02, 1.0e-6);
    ASSERT_EQ(europeanCall.sigma, 1.0);
    ASSERT_EQ(europeanCall.yearsToMaturity, 2.0);
    ASSERT_EQ(europeanCall.right, OptionRight::Call);
    ASSERT_EQ(europeanCall.style, OptionStyle::European);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}