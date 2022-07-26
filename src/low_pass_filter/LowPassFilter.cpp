#include <vector>
#include <numeric>
#include <execution>
#include "LowPassFilter.hpp"

//TODO templates?
//TODO

double LowPassFilter::singleOperation(std::vector<double>::iterator blockIter) {
  //TODO add halo
  //TODO check off by one errors here
  double output = std::transform_reduce(std::execution::par_unseq,
    std::begin(m_coef), std::end(m_coef), blockIter - static_cast<long>(haloSize), 0.0);
  return output;
}

LowPassFilter::LowPassFilter(std::vector<double> const &coefficients)
  : m_coef(coefficients), haloSize(coefficients.size()-1) {}

//TODO maybe a different signature
std::vector<double>::iterator LowPassFilter::operator()( const std::vector<double>::iterator inputBegin,
  const std::vector<double>::iterator inputEnd,
  std::vector<double>::iterator outputBegin) {

  auto blockSize(static_cast<std::size_t>(std::distance(inputBegin, inputEnd)));
  using vecIter = std::vector<double>::iterator;
  std::vector<vecIter> blockIters(blockSize);
  std::iota(std::begin(blockIters), std::end(blockIters), inputBegin);
  return std::transform(std::execution::par_unseq,
    std::begin(blockIters), std::end(blockIters), outputBegin,
    [this](vecIter blockIterator) { return this->singleOperation(blockIterator); });
}
