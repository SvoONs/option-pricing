cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

# Find all executables
file(GLOB project_SRCS src/*.cpp) #include/*.h

project(OptionPricing)
add_executable(OptionPricing ${project_SRCS})

### gtest ###
# incorporate as documented here:
# https://github.com/google/googletest/blob/master/googletest/README.md

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()
# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# run tests with ctest
include(CTest)

### Configure Test Suites ### 
# add TestOption test suite
add_executable(TestOption test/test_option.cpp include/option.h src/option.cpp)
target_link_libraries(TestOption gtest_main)
add_test(NAME TestOption COMMAND TestOption)
# add TestUtils test suite
add_executable(TestUtils test/test_utils.cpp include/utils.h src/utils.cpp)
target_link_libraries(TestUtils gtest_main)
add_test(NAME TestUtils COMMAND TestUtils)
# add TestBlackScholes test suite
add_executable(TestBlackScholes test/test_black_scholes.cpp include/utils.h src/utils.cpp include/option.h src/option.cpp include/black_scholes.h src/black_scholes.cpp)
target_link_libraries(TestBlackScholes gtest_main)
add_test(NAME TestBlackScholes COMMAND TestBlackScholes)
# add TestMCSimulation test suite
add_executable(TestMCSimulation test/test_mc_simulation.cpp include/mc_simulation.h src/mc_simulation.cpp include/option.h src/option.cpp include/utils.h src/utils.cpp)
target_link_libraries(TestMCSimulation gtest_main)
add_test(NAME TestMCSimulation COMMAND TestMCSimulation)