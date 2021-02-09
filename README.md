# option-pricing

``option-pricing`` is an easy-to-use command line tool which allows you to determine the fair price of [options](https://en.wikipedia.org/wiki/Option_(finance)).
Currently, two different models are implemented which can be used to determine the option price.

* [Black-Scholes](https://en.wikipedia.org/wiki/Black%E2%80%93Scholes_model), which makes certain assumptions regarding the market the option is traded on and provides an analytical formula for the fair price. It can be used to price European style options, also sometimes referred to as Vanilla style options.
* [Monte-Carlo Simulation](https://en.wikipedia.org/wiki/Monte_Carlo_methods_for_option_pricing), which allows to determine prices of more complex option types. The procedure consists of four steps: 1. simulate ``nPaths`` price paths of the underlying asset, 2. calculate the payoff for each path, 3. compute the average payoff and 4. discount the expected payoff to today.

## Building

After you have successfully cloned the repository to your machine you can build the project easily by running
```bash
mkdir build && cd build
cmake .. && make
```
from the source directory. Note that as part of the build the googletest library for unit testing is downloaded and build.

**Remark:** ``option-pricing`` is developed on Debian 10, for cross-platform usage and development a docker setup is being worked on. 

## Running

To use ``option-pricing`` for determination of the price of an option, run
```bash
./OptionPricing
```
from inside the build directory. The program will ask you for the required input parameters in order to determine the fair price of your option, as shown below. (TODO: gif)

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

## Future work (TODO)
* add more pricing models

## Code formatting (TODO)
```bash
clang-format-8 -i ../include/*.h ../src/*.cpp -style="{BasedOnStyle: google, IndentWidth: 4}"
```