#include <random>
#include <vector>
#include "../include/option.h"

class AssetPriceGenerator {
   public:
    AssetPriceGenerator(double initPrice, double mu, double sigma, double dt,
                        int nSteps);
    std::vector<double> generateAssetPrices(const int seed);

   private:
    double randomWalk(const double &prevAssetPrice, double randStdNorm);
    const double _initPrice;
    const double _mu;
    const double _sigma;
    const double _dt;
    const int _nSteps;
};

class MCSimulation {
   public:
    MCSimulation();
};