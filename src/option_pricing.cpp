#include <iostream>
#include "../include/black_scholes.h"
#include "../include/mc_simulation.h"

using namespace std;

void welcomeUser() {
    cout << "Hello fellow investor and welcome to "
            "OptionPricing! \U0001F4B0\nOptionPricing is a command line "
            "application "
            "to determine fair prices of options.\nCurrently supported are "
            "European and American stock options.\n";
}

Option getOptionFromUserInput() {
    cout << "\nFirst, provide the details of the option you would like to "
            "price.\n";
    double assetPrice, strikePrice, interest, volatility, yearsToMaturity;
    string style, right;
    cout << "Current asset price in $: ";
    cin >> assetPrice;
    while (assetPrice < 0) {
        cout << "The asset price can not be negative.\nCurrent asset price in "
                "$: ";
        cin >> assetPrice;
    }
    cout << "Strike price in $: ";
    cin >> strikePrice;
    while (strikePrice < 0) {
        cout << "The strike price can not be negative.\nStrike price in $: ";
        cin >> strikePrice;
    }
    cout << "Risk free interest rate in %: ";
    cin >> interest;
    while (interest < 0 || interest > 100) {
        cout << "The interest rate must be between 0 and 100%.\nRisk free "
                "interest rate in %: ";
        cin >> interest;
    }
    cout << "Volatility in %: ";
    cin >> volatility;
    while (volatility < 0 || volatility > 100) {
        cout << "The volatility must be between 0 and 100%.\nVolatility in %: ";
        cin >> volatility;
    }
    cout << "Years to maturity: ";
    cin >> yearsToMaturity;
    while (yearsToMaturity < 0) {
        cout << "Years to maturity must be a positive decimal value.\nYears to "
                "maturity: ";
        cin >> yearsToMaturity;
    }
    cout << "Option right (supported are 'Call'/'C' and 'Put'/'P'): ";
    cin >> right;
    while (!(right == string{"Call"} || right == string{"C"} || right == string{"Put"} || right == string{"P"}))
    {
        cout << "Option right must be one of 'Call'/'C' or 'Put'/'P')\nOption right: ";
        cin >> right;
    }   
    cout << "Option style (supported are 'American'/'A' and 'European'/'E'): ";
    cin >> style;
    while (!(style == string{"American"} || style == string{"A"} || style == string{"European"} || style == string{"E"}))
    {
        cout << "Option style must be one of 'American'/'A' or 'European'/'E')\nOption style: ";
        cin >> style;
    }

    Option option{assetPrice,
                  strikePrice,
                  interest / 100,
                  volatility / 100,
                  yearsToMaturity,
                  right == string{"Call"} || right == string{"C"}
                      ? OptionRight::Call
                      : OptionRight::Put,
                  style == string{"American"} || style == string{"A"}
                      ? OptionStyle::American
                      : OptionStyle::European};
    cout << "\U0001F389 Successfully initialised " << option;
    return option;
}

string getModel(Option &option) {
    string model;
    if (option.style == OptionStyle::American) {
        cout << "\nSince you are pricing an American style option, the only "
                "currently available pricing model is Monte Carlo Simulation";
        model = "MCSimulation";
    } else {
        cout << "\nNext, choose which model should be used to determine the "
                "fair "
                "option price. \nCurrently available models are "
                "'BlackScholes'/'BS' for "
                "European style options\n or 'MCSimulation'/'MC' for American "
                "and "
                "European style derivates.\n";
        cout << "Model: ";
        cin >> model;
        while (!(model == string{"BlackScholes"} || model == string{"BS"} || model == string{"MCSimulation"} || model == string{"MC"}))
        {
            cout << "Model must be one of 'BlackScholes'/'BS' or 'MCSimulation'/'MC'.\nModel: ";
            cin >> model;          
        }
    }
    return model;
}

void getFairOptionPrice(Option &option, string model) {
    double optionPrice;
    if (model == "BlackScholes" || model == "BS") {
        optionPrice = BlackScholesPrice(option);
        cout << "\nThe Black-Scholes price of the option is: " << optionPrice
             << "$\n";
    } else if (model == "MCSimulation" || model == "MC") {
        MCSimulation mcSimulation;

        int nPaths, nSteps;
        cout << "\n# of asset price paths to simulate: ";
        cin >> nPaths;
        while (nPaths < 0) {
            cout << "# of asset price paths to simulate can not be negative.\nPlease enter a positive value: ";
            cin >> nPaths;
        }
        cout << "# of timesteps in each path: ";
        cin >> nSteps;
        while (nSteps < 0) {
            cout << "# of timesteps in each path can not be negative.\nPlease enter a positive value: ";
            cin >> nSteps;
        }
        optionPrice =
            mcSimulation.getRiskFreeOptionPrice(option, nSteps, nPaths);
        cout << "\nThe Monte-Carlo price of the option is: " << optionPrice
             << "$\n";
    }
}

int main() {
    welcomeUser();
    Option option = getOptionFromUserInput();
    string model = getModel(option);
    getFairOptionPrice(option, model);
    return 0;
}