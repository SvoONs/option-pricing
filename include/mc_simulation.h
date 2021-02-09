#ifndef MC_SIMULATION_H
#define MC_SIMULATION_H

#include <random>
#include <vector>
#include "option.h"

class AssetPriceGenerator {
   public:
    AssetPriceGenerator(double initPrice, double mu, double sigma, double dt);
    std::vector<double> generateAssetPrices(int seed, int nSteps) const;

   private:
    double randomWalk(double prevAssetPrice, double randStdNorm) const;
    const double _initPrice;
    const double _mu;
    const double _sigma;
    const double _dt;
};

class MCSimulation {
   public:
    MCSimulation(){};
    double getRiskFreeOptionPrice(Option &option, int nSteps, int nPaths,
                                  bool runAsync=true) const;
};

#endif