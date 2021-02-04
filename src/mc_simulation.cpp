#include "../include/mc_simulation.h"
#include <cmath>
#include <random>
#include <vector>

AssetPriceGenerator::AssetPriceGenerator(double initPrice, double mu,
                                         double sigma, double dt, int nSteps)
    : _initPrice(initPrice), _mu(mu), _sigma(sigma), _dt(dt), _nSteps(nSteps){};

double AssetPriceGenerator::randomWalk(const double &prevAssetPrice,
                                       double randStdNorm) {
    // St=S_{t−1}*exp{(μ−σ2/2)Δt+σ(N(0,1)*sqrt(Δt))}
    double driftTerm = (_mu - std::pow(_sigma, 2) / 2) * _dt;
    double stochasticTerm = _sigma * randStdNorm * std::sqrt(_dt);
    double newAssetPrice =
        prevAssetPrice * std::exp(driftTerm + stochasticTerm);
    return newAssetPrice;
}

std::vector<double> AssetPriceGenerator::generateAssetPrices(const int seed) {
    std::mt19937 generator(seed);
    std::normal_distribution<double> norm(0, 1.0);

    std::vector<double> assetPrices;
    assetPrices.push_back(_initPrice);
    double assetPrice = _initPrice;
    for (size_t i = 0; i < _nSteps; i++) {
        assetPrice = randomWalk(assetPrice, norm(generator));
        assetPrices.push_back(assetPrice);
    }
    return assetPrices;
}
