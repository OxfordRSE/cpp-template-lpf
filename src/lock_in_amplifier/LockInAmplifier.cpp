#include <cmath>
#include <execution>
#include <numbers>
#include <numeric>

#include "LockInAmplifier.hpp"

LockInAmplifier::LockInAmplifier(std::vector<double> const &coefficients,
  Band frequencyBand,
  std::size_t const sizeOfBlock)
  : freqBand(frequencyBand),
    sinLockInSignal(sizeOfBlock + static_cast<std::size_t>(std::ceil(1 / frequencyBand.frequency))),
    cosLockInSignal(sizeOfBlock + static_cast<std::size_t>(std::ceil(1 / frequencyBand.frequency))),
    sinSignalBegin(std::begin(sinLockInSignal)), cosSignalBegin(std::begin(cosLockInSignal)),
    blockWithHalo1(sizeOfBlock + coefficients.size() - 1, 0.0),
    endOfHaloIt1(std::begin(blockWithHalo1) + static_cast<long>(coefficients.size()) - 1),
    copyBeginIt1(std::end(blockWithHalo1) - (static_cast<long>(coefficients.size()) - 1)),

    blockWithHalo2(sizeOfBlock + coefficients.size() - 1, 0.0),
    endOfHaloIt2(std::begin(blockWithHalo2) + static_cast<long>(coefficients.size()) - 1),
    copyBeginIt2(std::end(blockWithHalo2) - (static_cast<long>(coefficients.size()) - 1)),
    blockSize(sizeOfBlock),
    lpf(coefficients)
{
  std::vector<int> indices(cosLockInSignal.size());
  std::iota(std::begin(indices), std::end(indices), 0);
  // frequency is given in terms of indices so will be given in terms of the sampling frequency

  // Create sine signal
  std::transform(std::execution::par_unseq,
    std::begin(indices),
    std::end(indices),
    std::begin(sinLockInSignal),
    [frequencyBand](int index) { return std::sin(2 * std::numbers::pi * frequencyBand.frequency * index); });

  // Create cosine signal
  std::transform(std::execution::par_unseq,
   std::begin(indices),
   std::end(indices),
   std::begin(cosLockInSignal),
   [frequencyBand](int index) { return std::cos(2 * std::numbers::pi * frequencyBand.frequency * index); });
}

void LockInAmplifier::operator()(const std::vector<double>::iterator first,
  const std::vector<double>::iterator last,
  std::vector<double>::iterator xOdd,
  std::vector<double>::iterator yOdd)
{
  // TODO x and y outputs could be run in parallel
  std::copy(std::execution::par_unseq, copyBeginIt1, std::end(blockWithHalo1), std::begin(blockWithHalo1));
  std::transform(std::execution::par_unseq, first, last, sinSignalBegin, endOfHaloIt1, std::multiplies<>{});
  lpf(endOfHaloIt1, std::end(blockWithHalo1), xOdd);

  std::copy(std::execution::par_unseq, copyBeginIt2, std::end(blockWithHalo2), std::begin(blockWithHalo2));
  std::transform(std::execution::par_unseq, first, last, cosSignalBegin, endOfHaloIt2, std::multiplies<>{});
  lpf(endOfHaloIt2, std::end(blockWithHalo2), yOdd);
}

// TODO offsetting phase won't be very accurate because stored signal is sampled
void LockInAmplifier::offset_phase(double phi)
{
  phi = std::fmod(phi, 2 * std::numbers::pi);// Only want phase offset within [0, 2*pi)
  phi = (phi > 0) ? phi : 2 * std::numbers::pi + phi;
  using vecIter = std::vector<double>::iterator;
  using diff_type = std::iterator_traits<vecIter>::difference_type;
  auto indexOffset = static_cast<diff_type>(phi / (2 * std::numbers::pi * freqBand.frequency));
  diff_type distanceToEnd =
    std::distance(cosSignalBegin + static_cast<diff_type>(blockSize), std::end(cosLockInSignal));
  if (indexOffset > distanceToEnd) { indexOffset = indexOffset - static_cast<diff_type>(1 / freqBand.frequency); }
  cosSignalBegin += indexOffset;
  sinSignalBegin += indexOffset;
}