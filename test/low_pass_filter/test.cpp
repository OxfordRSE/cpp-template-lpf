#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

using namespace Catch::literals;

#include <vector>

#include "LowPassFilter.hpp"

//NOLINTBEGIN
TEST_CASE("Testing low pass filter on random data and filter coefficients", "[low pass filter]") {
  std::vector<double> filterCoefficients{2.1, -3.2, -7.1};
  std::vector<double> block1{0, 0, 0.6, 5, -1.6, -5.4, 1.4};
  std::vector<double> block2{-5.4, 1.4, 6.3, 2.7, -9.1, 4.9, 6.2};

  LowPassFilter lpf(filterCoefficients);
  std::vector<double> blockOutput1(5);
  std::vector<double> blockOutput2(5);

  lpf(std::begin(block1) + 2, std::end(block1), std::begin(blockOutput1));
  lpf(std::begin(block2) + 2, std::end(block2), std::begin(blockOutput2));

  // FIXME: vector matchers are deprecated.
  REQUIRE_THAT(blockOutput1, Catch::Matchers::Approx(std::vector<double>{-4.26, -37.42, -3.38, 53.96, 3.98}));
  REQUIRE_THAT(blockOutput2, Catch::Matchers::Approx(std::vector<double>{-60.55, -36.39, 69.2, 0, -78.81}));
}
//NOLINTEND