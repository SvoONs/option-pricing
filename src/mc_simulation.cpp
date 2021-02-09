#include "../include/mc_simulation.h"
#include <cmath>
#include <future>
#include <random>
#include <vector>
#include "../include/utils.h"

AssetPriceGenerator::AssetPriceGenerator(double initPrice, double mu,
                                         double sigma, double dt)
    : _initPrice(initPrice), _mu(mu), _sigma(sigma), _dt(dt){};

double AssetPriceGenerator::randomWalk(double prevAssetPrice,
                                       double randStdNorm) const {
    // St=S_{t−1}*exp{(μ−σ2/2)Δt+σ(N(0,1)*sqrt(Δt))}
    double driftTerm = (_mu - std::pow(_sigma, 2) / 2) * _dt;
    double stochasticTerm = _sigma * randStdNorm * std::sqrt(_dt);
    double newAssetPrice =
        prevAssetPrice * std::exp(driftTerm + stochasticTerm);
    return newAssetPrice;
}

std::vector<double> AssetPriceGenerator::generateAssetPrices(int seed,
                                                             int nSteps) const {
    std::mt19937 generator(seed);
    std::normal_distribution<double> norm(0, 1.0);

    std::vector<double> assetPrices;
    assetPrices.push_back(_initPrice);
    double assetPrice = _initPrice;
    for (size_t i = 0; i < nSteps; i++) {
        assetPrice = randomWalk(assetPrice, norm(generator));
        assetPrices.push_back(assetPrice);
    }
    return assetPrices;
}

double MCSimulation::getRiskFreeOptionPrice(Option &option, int nSteps,
                                            int nPaths,
                                            bool runAsync) const {
    double dt = option.yearsToMaturity / nSteps;
    AssetPriceGenerator priceGenerator{option.assetPrice, option.interest,
                                       option.sigma, dt};
    std::vector<std::future<std::vector<double>>> walks;
    // TODO evaluate more robust seed generation
    for (size_t i = 0; i < nPaths; i++) {
        walks.emplace_back(
            std::async(runAsync ? std::launch::async : std::launch::deferred,
                       &AssetPriceGenerator::generateAssetPrices,
                       &priceGenerator, i + 42, nSteps));
    }

    std::vector<double> payoffsAtMaturity;
    for (auto &&walk : walks) {
        double priceAtMaturity = walk.get().back();
        double payoff = option.getPayoff(priceAtMaturity);
        discountValue(payoff, option.interest, option.yearsToMaturity);
        payoffsAtMaturity.emplace_back(payoff);
    }

    return std::accumulate(payoffsAtMaturity.begin(), payoffsAtMaturity.end(),
                           decltype(payoffsAtMaturity)::value_type(0)) /
           payoffsAtMaturity.size();
}