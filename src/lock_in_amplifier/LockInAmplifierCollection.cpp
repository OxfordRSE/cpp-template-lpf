#include <execution>
#include <utility>
#include <vector>

#include "LockInAmplifier.hpp"
#include "LockInAmplifierCollection.hpp"

LockInAmplifierCollection::LockInAmplifierCollection(std::vector<double> const &coefficients,
  std::vector<Band> const &bands,
  std::size_t const blockSize)
  : LIA_vector(bands.size())
{
  for (std::size_t i = 0; i < bands.size(); i++) {
    // TODO move constructor?
    LIA_vector[i] = LockInAmplifier(coefficients, bands[i], blockSize);
  }
}

void LockInAmplifierCollection::operator()(std::vector<double>::iterator first1,
  std::vector<double>::iterator last1,
  std::vector<std::vector<double>>::iterator d_first)
{
  std::vector<int> indices(LIA_vector.size());
  std::iota(std::begin(indices), std::end(indices), 0);
  // TODO maybe without using indices
  return std::for_each(std::execution::par_unseq, std::begin(indices), std::end(indices), [&](std::size_t index) {
    LIA_vector[index](first1, last1, std::begin(*(d_first + static_cast<long>(index))));
  });
}