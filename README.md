# option-pricing

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

## Code formatting (TODO)
```bash
clang-format-8 -i ../include/*.h ../src/*.cpp -style="{BasedOnStyle: google, IndentWidth: 4}"
```