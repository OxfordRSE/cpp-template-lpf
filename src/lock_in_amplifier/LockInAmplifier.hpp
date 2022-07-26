#include <algorithm>
#include <cmath>
#include <numbers>
#include <numeric>

#include "LowPassFilter.hpp"

#ifndef CPP_TEMPLATE_LPF_LOCKINAMPLIFIER_HPP
#define CPP_TEMPLATE_LPF_LOCKINAMPLIFIER_HPP

/// Parity enumeration
/**
 * @param even
 * @param odd
 */
enum Parity { even, odd };

/// Struct for a single frequency band indicating its frequency and parity.
struct Band
{
  double frequency; ///< frequency of band
  Parity parity; ///< parity of band
};

/// Class for a lock in amplifier.
/**
 * This class constructs a lock in amplifier at a certain frequency band and operates on input data to
 * apply a lock in amplification algorithm.
 */
class LockInAmplifier
{
public:
  /// Default constructor
  LockInAmplifier() : blockSize(0) {}

  /// Constructor
  /**
   * A lock in amplifier is created with coefficients for the low pass filter, the frequency band at which the
   * lock in amplifier works at, and the size of the data block.
   * @param coefficients  Low pass filter coefficients.
   * @param frequencyBand Frequency band of lock in amplifier.
   * @param sizeOfBlock Size of the data block.
   */
  LockInAmplifier(std::vector<double> const &coefficients, Band frequencyBand, std::size_t const sizeOfBlock);

  /// Function call operator for applying lock in amplifier.
  /**
   * Applies the lock in amplifier algorithm on an input vector and outputs the result to another vector.
   * @param first1 vector of doubles iterator to start of input vector
   * @param last1 vector of doubles iterator to one past the end of the input vector
   * @param d_first vector of doubles iterator to beginning of output vector
   */
  void operator()(const std::vector<double>::iterator first1,
    const std::vector<double>::iterator last1, std::vector<double>::iterator d_first);

private:
  std::vector<double> lockInSignal; ///< Sinusoidal function for multiplication of the input signal.
  /// Vector storing input block with halo.
  /**
   * Stores the input block as well as a halo in front. The halo consists of the last N-1 terms of the previous block
   * where N is the order of the filter. For the first block, the halo elements are 0.
   */
  std::vector<double> blockWithHalo;
  std::vector<double>::iterator endOfHaloIt; ///< Vector of doubles iterator to element after halo.
  std::vector<double>::iterator copyBeginIt; ///< Vector of doubles iterator to beginning of last N-1 elements.
  std::size_t blockSize; ///< Size of the input block.
  LowPassFilter lpf; ///< Low pass filter

  void set_signal(Band band); ///< Helper function to set the lock in signal @see lockinsignal
};
#endif// CPP_TEMPLATE_LPF_LOCKINAMPLIFIER_HPP
