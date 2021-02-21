#include <iostream>
#include "../include/black_scholes.h"
#include "../include/mc_simulation.h"

using namespace std;

void welcomeUser() {
    cout << "Hello fellow investor and welcome to "
            "OptionPricing! \U0001F4B0\nOptionPricing is a command line "
            "application "
            "to determine fair prices of options.\nCurrently supported are "
            "European and American stock options.\nThe implemented underlying "
            "pricing "
            "models rely on the Black-Scholes theory, see "
            "https://en.wikipedia.org/wiki/Black%E2%80%93Scholes_model for "
            "further information";
}

Option getOptionFromUserInput() {
    cout << "\nFirst, provide the details of the option you would like to "
            "price.";
    double assetPrice, strikePrice, interest, volatility, yearsToMaturity;
    string style, right;
    cout << "\nCurrent asset price in $: ";
    cin >> assetPrice;
    cout << "Strike price in $: ";
    cin >> strikePrice;
    cout << "Risk free interest rate in %: ";
    cin >> interest;
    cout << "Volatility in %: ";
    cin >> volatility;
    cout << "Years to maturity: ";
    cin >> yearsToMaturity;
    cout << "Option right (valid are 'Call'[C] and 'Put'[P]): ";
    cin >> right;
    cout << "Option style (valid are 'American'[A] and 'European'[E]): ";
    cin >> style;

    Option option{
        assetPrice,
        strikePrice,
        interest / 100,
        volatility / 100,
        yearsToMaturity,
        right == string{"Call"} ? OptionRight::Call : OptionRight::Put,
        style == string{"American"} ? OptionStyle::American
                                    : OptionStyle::European};
    cout << "\U0001F389 Successfully initialised " << option;
    return option;
}

string getModel(Option &option) {
    cout << "\nNext, choose which model should be used to determine the fair "
            "option price.";
    string model;
    if (option.style == OptionStyle::American) {
        cout << "\nSince you are pricing an American style option, the only "
                "currently available model is Monte Carlo Simulation";
        model = "MCSimulation";
    } else {
        cout << "\nCurrently available models are 'BlackScholes' for "
                "European style options\n or 'MCSimulation' for American and "
                "European style derivates.\n";
        cout << "Model: ";
        cin >> model;
    }
    return model;
}

void getFairOptionPrice(Option &option, string model) {
    double optionPrice;
    if (model == "BlackScholes") {
        optionPrice = BlackScholesPrice(option);
        cout << "The Black-Scholes price of the option is: " << optionPrice
             << "$\n";
    } else if (model == "MCSimulation") {
        MCSimulation mcSimulation;

        int nPaths, nSteps;
        cout << "\n# of asset price paths to simulate: ";
        cin >> nPaths;
        cout << "\n# of timesteps in each path: ";
        cin >> nSteps;
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