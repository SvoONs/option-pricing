#include <iostream>
#include "../include/black_scholes.h"
#include "../include/mc_simulation.h"

using std::cin;
using std::cout;

void welcomeUser() {
    cout << "Hello fellow investor and welcome to "
            "OptionPricing! \U0001F4B0\nOptionPricing is a command line application "
            "to determine fair prices of options.\nCurrently supported are "
            "European and American stock options\n";
}

Option getOptionFromUserInput() {
    cout << "\nFirst, provide the details of the option you would like to price.";
    double assetPrice, strikePrice, interest, volatility, yearsToMaturity;
    std::string style, right;
    cout << "\nCurrent asset price: ";
    cin >> assetPrice;
    cout << "Strike price: ";
    cin >> strikePrice;
    cout << "Interest rate: ";
    cin >> interest;
    cout << "Volatility: ";
    cin >> volatility;
    cout << "Years to maturity: ";
    cin >> yearsToMaturity;
    cout << "Option right (valid are 'Call'[0] and 'Put'[1]): ";
    cin >> right;
    cout << "Option style (valid are 'American'[0] and 'European'[1]): ";
    cin >> style;

    Option option{
        assetPrice,
        strikePrice,
        interest,
        volatility,
        yearsToMaturity,
        right == "Call" ? OptionRight::Call : OptionRight::Put,
        style == "American" ? OptionStyle::American : OptionStyle::European};
    cout << "\U0001F389 Successfully initialised " << option;
    return option;
}

void getFairOptionPrice(Option &option) {
    cout << "\nNext, choose how the fair option price should be "
            "determined.\nCurrently available models are 'BlackScholes' for "
            "European style options\n or 'MCSimulation' for American and "
            "European style derivates.\n";
    cout << "Model: ";
    std::string model;
    cin >> model;
    double optionPrice;
    if (model == "BlackScholes") {
        optionPrice = BlackScholesPrice(option);
        cout << "The Black-Scholes price of the option is: " << optionPrice
             << "$\n";
    } else if (model == "MCSimulation") {
        MCSimulation mcSimulation;
        int nPaths, nSteps;
        cout << "How many asset price paths should be simulated?\n";
        cin >> nPaths;
        cout << "How many steps should each price path simulate?\n";
        cin >> nSteps;
        optionPrice =
            mcSimulation.getRiskFreeOptionPrice(option, nSteps, nPaths);
        cout << "The Monte-Carlo price of the option is: " << optionPrice
             << "$\n";
    }
}

int main() {
    welcomeUser();
    Option option = getOptionFromUserInput();
    getFairOptionPrice(option);
    return 0;
}