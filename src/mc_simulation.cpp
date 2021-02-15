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

double MCSimulation::backTraceOptionPrice(Option &option,
                                          Eigen::MatrixXd &simulatedAssetPrices,
                                          double dt) const {
    int m=simulatedAssetPrices.rows(), n = simulatedAssetPrices.cols();
    //
    auto payoutLambda = [option](const double &price) {
        return option.getPayout(price);
    };
    auto inTheMoney = [](double payout) { return payout > 0.0 ? 1 : 0; };
    // initialize zero-matrix holding strategy of early exercise
    Eigen::MatrixXi strategyMatrix = Eigen::ArrayXXi::Zero(m, n);
    // initialize zero-matrix holding cashflows for early exercise options
    Eigen::MatrixXd cashflowMatrix = Eigen::ArrayXXd::Zero(m, n);

    // determine cashflow and strategy at maturity
    cashflowMatrix.col(n-1) =
        simulatedAssetPrices.col(n-1).unaryExpr(payoutLambda);
    ;
    strategyMatrix.col(n-1) =
        cashflowMatrix.col(n-1).unaryExpr(inTheMoney);
    // backpropagate to present
    for (int j = 1; j < n-1; ++j) {
        // determine payouts of option with "current" asset prices
        auto assetPrices = simulatedAssetPrices.col(n-1-j);
        Eigen::VectorXd payouts = assetPrices.unaryExpr(payoutLambda);
        int nCol = 0;
        std::vector<double> XRaw, yRaw;
        // collect scenarios in-the-money
        for (int i = 0; i < m; i++)
        {
            double payout = payouts(i);
            if (payout > 0) {
                XRaw.push_back(assetPrices(i));
                discountValue(payout, option.interest, j*dt);
                yRaw.push_back(payout);
                nCol++;
            }
        }
        Eigen::VectorXd X = Eigen::Map<Eigen::VectorXd>(XRaw.data(), XRaw.size());
        Eigen::VectorXd y = Eigen::Map<Eigen::VectorXd>(yRaw.data(), yRaw.size());
        Eigen::Vector3d betas = quadraticRegression(X,y);
    }
    return 0.0;
}

double MCSimulation::getRiskFreeOptionPrice(Option &option, int nSteps,
                                            int nPaths) const {
    double dt = option.yearsToMaturity / nSteps;
    AssetPriceGenerator priceGenerator{option.assetPrice, option.interest,
                                       option.sigma, dt};
    std::vector<std::future<std::vector<double>>> paths;
    // TODO evaluate more robust seed generation
    for (size_t i = 0; i < nPaths; i++) {
        paths.emplace_back(std::async(std::launch::async,
                                      &AssetPriceGenerator::generateAssetPrices,
                                      &priceGenerator, i + 42, nSteps));
    }

    double optionPrice;
    if (option.style == OptionStyle::European) {
        // for European options we just care about the final asset price at
        // maturity
        std::vector<double> payoutsAtMaturity;
        for (auto &&path : paths) {
            double priceAtMaturity = path.get().back();
            double payout = option.getPayout(priceAtMaturity);
            discountValue(payout, option.interest, option.yearsToMaturity);
            payoutsAtMaturity.emplace_back(payout);
        }
        optionPrice =
            std::accumulate(payoutsAtMaturity.begin(), payoutsAtMaturity.end(),
                            decltype(payoutsAtMaturity)::value_type(0)) /
            payoutsAtMaturity.size();
    } else if (option.style == OptionStyle::American) {
        // for American options we need the entire information of simulated
        // asset prices
        Eigen::MatrixXd assetPrices(nPaths, nSteps);
        int cnt = 0;
        for (auto &&path : paths) {
            std::vector<double> pathPrices = path.get();
            auto row =
                Eigen::Map<Eigen::RowVectorXd>(pathPrices.data(), nSteps);
            assetPrices.row(cnt) = row;
            cnt++;
        }
        optionPrice = backTraceOptionPrice(option, assetPrices, dt);
    }
    return optionPrice;
}