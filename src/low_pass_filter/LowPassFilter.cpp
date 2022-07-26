#include <vector>
#include <numeric>
#include <execution>
#include "LowPassFilter.hpp"

double LowPassFilter::lowPassFilterKernel(std::vector<double>::iterator blockIter) {
  double output = std::transform_reduce(std::execution::par_unseq,
    std::begin(coef), std::end(coef), blockIter - static_cast<long>(haloSize), 0.0);
  return output;
}

LowPassFilter::LowPassFilter(std::vector<double> const &coefficients)
  : coef(coefficients), haloSize(coefficients.size()-1) {}

std::vector<double>::iterator LowPassFilter::operator()(std::vector<double>::iterator const first1,
  std::vector<double>::iterator const last1,
  std::vector<double>::iterator d_first) {

  auto blockSize(static_cast<std::size_t>(std::distance(first1, last1)));
  using vecIter = std::vector<double>::iterator;
  std::vector<vecIter> blockIters(blockSize);
  std::iota(std::begin(blockIters), std::end(blockIters), first1);
  return std::transform(std::execution::par_unseq,
    std::begin(blockIters), std::end(blockIters), d_first,
    [this](vecIter blockIterator) { return this->lowPassFilterKernel(blockIterator); });
}