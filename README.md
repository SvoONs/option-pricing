# option-pricing

``option-pricing`` is an easy-to-use command line tool which allows you to determine the fair price of [options](https://en.wikipedia.org/wiki/Option_(finance)).
Currently, two different models are implemented which can be used to determine the option price for European and American options.

* [Black-Scholes](https://en.wikipedia.org/wiki/Black%E2%80%93Scholes_model), which makes certain assumptions regarding the market the option is traded on and provides an analytical formula for the fair price. It can be used to price European style options, also sometimes referred to as Vanilla style options.
* [Monte-Carlo Simulation](https://en.wikipedia.org/wiki/Monte_Carlo_methods_for_option_pricing), which allows to determine prices of more complex option types such as American options. This is achieved using the model presented in 
*Longstaff, Francis A., and Eduardo S. Schwartz. "Valuing American options by simulation: a simple least-squares approach." The review of financial studies 14.1 (2001): 113-147.*

## Project structure
The main file of this project is src/option_pricing.cpp. It processes and validates user input and passes the data to the evaluation model and outputs the computed price. 

The project uses an ``Option`` struct defined in include/option.h as a data container which holds the characteristical data of an option. This includes the price of the underlying stock, the price at which the option can be exercised (strike price), a risk free interest rate offered on the market, the volatility of the underlying asset, the time to maturity of the option, the option right, being either *Put* or *Call* as well as the option style, *American* or *European*. This option struct is passed to the model that should be used for pricing the option.

There are currently two models implemented. An analytical formula in src/black_scholes.cpp for European style options and a Monte Carlo simulation based evaluation model as declared in include/mc_simulation.h.
This file defines a class to generate random paths of an asset price ``AssetPriceGenerator``. The asset price paths are simulated to follow a [Geometric Brownian Motion](https://en.wikipedia.org/wiki/Geometric_Brownian_motion). The class is used by the MCSimulation class to generate a given number of ``nPath`` different simulated stock price paths, each path containing `nSteps` prices. Those paths are used by the MCSimulation class member functions to compute an expected discounted payout of the option in the future.

Finally, there are a couple of useful helper functions provided in include/utils.h.

## Building

After you have successfully cloned the repository to your machine you can build the project easily by running
```bash
mkdir build && cd build
cmake .. && make
```
from the source directory. Note that as part of the build the googletest library for unit testing is downloaded and build.

Also, for the Monte Carlo evaluation of options with early-exercise the linear algebra library *Eigen* is used to take advantage of its matrix and vector implementations. To do so, the headers from https://gitlab.com/libeigen/eigen are included under *include/Eigen* as recommended here https://eigen.tuxfamily.org/index.php?title=Main_Page#License.

**Remark:** ``option-pricing`` is developed on Debian 10, for cross-platform usage and development a docker setup is being worked on. 

## Running

In order to calculate the price of an option using ``option-pricing`` run
```bash
./OptionPricing
```
from inside the build directory. The program will ask you for the required option parameters in order to determine the fair price of your option.

First, those are the characteristics of the option: current asset price, strike price, interest rate, volatility of the asset and years to maturity of the option.
Second, you get to choose the model you would like to use to evaluate the option price. Note that for European style options the Black-Scholes model provides an analytical formula to determine the value of the option. The value determined using Monte Carlo simulation converges to that same value with an increasing number of simulated asset price paths but won't be identical to the value retrieved using Black Scholes. To price American style options, currently only Monte Carlo Simulation is available.

A running example is shown below.
![](run_example.gif)

## Running tests
In order to run all unit tests at once you can just run
```bash
ctest
```
from inside the build directory.

Alternatively, you can run a single test suite using the corresponding executable. Below an example of how to run the ``TestOption`` test suite.
```bash
./TestOption
```

## Planned future work
* add more pricing models
* support more complex option types

## Capstone project rubric
This project is developed as part of the Udacity C++ Nanodegree programm. It addresses the following rubric points:

__Loops, Functions, I/O:__
* The project demonstrates an understanding of C++ functions and control structures:
    * while-loops: src/option_pricing.cpp, line 22, 29, 35, 42, 48, ...
    * for-loops: src/mc_simulation.cpp, line 30, 56, 62, ...
    * if-clauses: src/mc_simulation.cpp, line 63, 87, 123, 137
* The project accepts user input and processes the input: src/option_pricing.cpp, line 15, 84

__Object Oriented Programming:__
* The project uses Object Oriented Programming techniques: src/option.cpp, line 4
* Classes use appropriate access specifiers for class members: include/mc_simulation.h, line 10, 14 & 23, 27
* Class constructors utilize member initialization lists: src/option.cpp, line 7 to 13; src/mc_simulation.cpp, line 10
* Classes abstract implementation details from their interfaces: src/mc_simulation.cpp, line 22, 109

__Memory Management:__
* The project makes use of references in function declarations:
include/utils.h, line 7 & 9

__Concurrency:__
* The project uses multithreading: src/mc_simulation.cpp, line 117