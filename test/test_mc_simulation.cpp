#include "../include/mc_simulation.h"
#include "gtest/gtest.h"

TEST(TestMCSimulation, TestAssetPriceGenerator) {
    double initPrice = 50.0, mu = 2.5, sigma = 5.25, dt = 0.825;
    AssetPriceGenerator priceGen{initPrice, mu, sigma, dt};
    int seed = 42, nSteps = 12;
    auto prices = priceGen.generateAssetPrices(seed, nSteps);
    ASSERT_EQ(prices.size(), 13);
    for (auto &&price : prices) {
        // with a positive initial price, all generated asset prices must be
        // strictly positive
        ASSERT_GT(price, 0.0);
    }
}

TEST(TestMCSimulation, TestMCSimulationEuropeanCall) {
    double assetPrice = 60, strikePrice = 65, interest = 0.08, volatility = 0.3,
           T = 0.25;
    Option europeanCall{assetPrice,           strikePrice, interest,
                        volatility,           T,           OptionRight::Call,
                        OptionStyle::European};
    MCSimulation simulator;
    int nSteps = 50, nPaths = 1000;
    double mcValueEC =
        simulator.getRiskFreeOptionPrice(europeanCall, nSteps, nPaths);
    ASSERT_NEAR(mcValueEC, 2.1334, 0.02);
}

TEST(TestMCSimulation, TestMCSimulationEuropeanPut) {
    double assetPrice = 60, strikePrice = 65, interest = 0.08, volatility = 0.3,
           T = 0.25;
    Option europeanPut{assetPrice,           strikePrice, interest,
                       volatility,           T,           OptionRight::Put,
                       OptionStyle::European};
    MCSimulation simulator;
    int nSteps = 50, nPaths = 1000;
    double mcValueEC =
        simulator.getRiskFreeOptionPrice(europeanPut, nSteps, nPaths);
    ASSERT_NEAR(mcValueEC, 5.8462, 0.2);
}


TEST(TestMCSimulation, TestMCSimulationAmericanPut) {
    double assetPrice = 36, strikePrice = 40, interest = 0.06, volatility = 0.2,
           T = 1;
    Option americanPut{assetPrice,           strikePrice, interest,
                       volatility,           T,           OptionRight::Put,
                       OptionStyle::American};
    MCSimulation simulator;
    int nSteps = 50, nPaths = 1000;
    double mcValueAP =
        simulator.getRiskFreeOptionPrice(americanPut, nSteps, nPaths);
    ASSERT_NEAR(mcValueAP, 4.472, 0.2);
}