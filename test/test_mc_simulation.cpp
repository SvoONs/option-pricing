#include "gtest/gtest.h"
#include "../include/mc_simulation.h"

TEST(TestMCSimulation, TestAssetPriceGenerator) {
    AssetPriceGenerator priceGen{50.0, 2.5, 5.25, 0.825, 12};
    int seed = 42;
    auto prices = priceGen.generateAssetPrices(seed);
    ASSERT_EQ(prices.size(), 13);
}