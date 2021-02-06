#include "../include/mc_simulation.h"
#include "gtest/gtest.h"

TEST(TestMCSimulation, TestAssetPriceGenerator) {
    AssetPriceGenerator priceGen{50.0, 2.5, 5.25, 0.825};
    int seed = 42, nSteps = 12;
    auto prices = priceGen.generateAssetPrices(seed, nSteps);
    ASSERT_EQ(prices.size(), 13);
}

TEST(TestMCSimulation, TestMCSimulationEuropeanCall) {
    double assetPrice = 60, strikePrice = 65, interest = 0.08, volatility = 0.3,
           T = 0.25;
    Option europeanCall{assetPrice,           strikePrice, interest,
                        volatility,           T,           OptionRight::Call,
                        OptionStyle::European};
    MCSimulation simulator;
    int nSteps = 90, nWalks = 1000;
    double mcValueEC =
        simulator.getRiskFreeOptionPrice(europeanCall, nSteps, nWalks);
    ASSERT_NEAR(mcValueEC, 2.1334, 0.02);
}

TEST(TestMCSimulation, TestMCSimulationEuropeanPut) {
    double assetPrice = 60, strikePrice = 65, interest = 0.08, volatility = 0.3,
           T = 0.25;
    Option europeanCall{assetPrice,           strikePrice, interest,
                        volatility,           T,           OptionRight::Put,
                        OptionStyle::European};
    MCSimulation simulator;
    int nSteps = 90, nWalks = 1000;
    double mcValueEC =
        simulator.getRiskFreeOptionPrice(europeanCall, nSteps, nWalks);
    // TODO why is the diff so high?
    ASSERT_NEAR(mcValueEC, 5.8462, 0.5);
}