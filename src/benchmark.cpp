#include <chrono>
#include <iostream>
#include <vector>
#include "../include/mc_simulation.h"

void benchmarkMCSimulation() {
    std::vector<int> nPathsVec{50, 100, 1000, 5000, 10000};
    int nSteps = 3600;
    double assetPrice = 60, strikePrice = 65, interest = 0.08, volatility = 0.3,
           T = 10;

    Option europeanCall{assetPrice,           strikePrice, interest,
                        volatility,           T,           OptionRight::Call,
                        OptionStyle::European};

    MCSimulation mcSimulator;
    for (auto &&nPaths : nPathsVec) {
        auto t1 = std::chrono::high_resolution_clock::now();
        double optionPrice1 = mcSimulator.getRiskFreeOptionPrice(
            europeanCall, nSteps, nPaths, true);
        auto t2 = std::chrono::high_resolution_clock::now();
        double duration1 =
            std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1)
                .count();
        auto t3 = std::chrono::high_resolution_clock::now();
        double optionPrice2 = mcSimulator.getRiskFreeOptionPrice(
            europeanCall, nSteps, nPaths, false);
        auto t4 = std::chrono::high_resolution_clock::now();
        double duration2 =
            std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t2)
                .count();
        std::cout << "nPaths: " << nPaths << ", runAsync=true:  " << duration1
                  << "ms"
                  << " (price: " << optionPrice1 << "$)\n";
        std::cout << "nPaths: " << nPaths << ", runAsync=false: " << duration2
                  << "ms"
                  << " (price: " << optionPrice2 << "$)\n";
        double fraction = 1.0 - duration1 / duration2;
        std::cout << "Speed gain by parallelisation: " << fraction * 100
                  << "%\n";
    }
}