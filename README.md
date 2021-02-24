# option-pricing

``option-pricing`` is an easy-to-use command line tool which allows you to determine the fair price of [options](https://en.wikipedia.org/wiki/Option_(finance)).
Currently, two different models are implemented which can be used to determine the option price for European and American options.

* [Black-Scholes](https://en.wikipedia.org/wiki/Black%E2%80%93Scholes_model), which makes certain assumptions regarding the market the option is traded on and provides an analytical formula for the fair price. It can be used to price European style options, also sometimes referred to as Vanilla style options.
* [Monte-Carlo Simulation](https://en.wikipedia.org/wiki/Monte_Carlo_methods_for_option_pricing), which allows to determine prices of more complex option types such as American options. The procedure consists of four steps: 1. simulate ``nPaths`` price paths of the underlying asset, 2. calculate the payout from the option for each path, 3. compute the average payoff and 4. discount the expected payoff to today. For American style options the possibility of early exercise needs to be considered. This is done using the model presented in 
*Longstaff, Francis A., and Eduardo S. Schwartz. "Valuing American options by simulation: a simple least-squares approach." The review of financial studies 14.1 (2001): 113-147.*

## Project structure
TODO

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

To use ``option-pricing`` for determination of the price of an option, run
```bash
./OptionPricing
```
from inside the build directory. The program will ask you for the required input parameters in order to determine the fair price of your option.

First, those are the characteristics of the option: current asset price, strike price, interest rate, volatility of the asset and years to maturity of the option.
Second, you get to choose the model you would like to use to evaluate the option price. Note, that for European style options the Black-Scholes model provides an analytical formula to determine the value of the option. The value determined using Monte Carlo simulation converges to that same value with an increasing number of simulated asset price paths but won't be identical to the value retrieved using Black Scholes.

It looks like this. (TODO: gif)

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
This project is developed as part of the C++ Nanodegree programm. It addresses the following rubrice points:

__Loops, Functions, I/O:__

__Object Oriented Programming:__
* The project uses Object Oriented Programming techniques: src/option.cpp, line 4
* Classes use appropriate access specifiers for class members: include/mc_simulation.h, line 10, 14 & 23, 27
* Class constructors utilize member initialization lists: src/option.cpp, line 7 to 13; src/mc_simulation.cpp, line 10

__Memory Management:__
* The project makes use of references in function declarations:
include/utils.h, line 7 & 9

__Concurrency:__

## Code formatting (TODO)
```bash
clang-format-8 -i ../include/*.h ../src/*.cpp -style="{BasedOnStyle: google, IndentWidth: 4}"
```