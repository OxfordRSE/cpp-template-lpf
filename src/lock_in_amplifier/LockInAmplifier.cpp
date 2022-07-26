#include <algorithm>
#include <cmath>
#include <execution>
#include <iostream>
#include <numbers>
#include <numeric>

#include "LockInAmplifier.hpp"

LockInAmplifier::LockInAmplifier(std::vector<double> const &coefficients, std::size_t const sizeOfBlock)
  : lockInSignal(sizeOfBlock), blockWithHalo(sizeOfBlock + coefficients.size() - 1, 0.0),
    endOfHaloIt(std::begin(blockWithHalo) + static_cast<long>(coefficients.size()) - 1),
    copyBeginIt(std::end(blockWithHalo) - (static_cast<long>(coefficients.size()) - 1)), blockSize(sizeOfBlock),
    lpf(coefficients)
{}

void LockInAmplifier::set_signal(Band band)
{
  std::vector<int> indices(blockSize);
  std::iota(std::begin(indices), std::end(indices), 0);
  // frequency is given in terms of indicies so will be given in terms of the sampling frequency
  switch (band.parity) {
  case even:
    std::transform(
      std::execution::par_unseq, std::begin(indices), std::end(indices), std::begin(lockInSignal), [band](int index) {
        return std::cos(2 * std::numbers::pi * band.frequency * index);
      });
  case odd:
    std::transform(
      std::execution::par_unseq, std::begin(indices), std::end(indices), std::begin(lockInSignal), [band](int index) {
        return std::sin(2 * std::numbers::pi * band.frequency * index);
      });
  }
}

std::vector<double>::iterator LockInAmplifier::operator()(const std::vector<double>::iterator first1,
  const std::vector<double>::iterator last1,
  std::vector<double>::iterator d_first)
{
  std::copy(std::execution::par_unseq, copyBeginIt, std::end(blockWithHalo), std::begin(blockWithHalo));

  std::transform(std::execution::par_unseq, first1, last1, std::begin(lockInSignal), endOfHaloIt, std::multiplies<>{});

  return lpf(endOfHaloIt, std::end(blockWithHalo), d_first);
}