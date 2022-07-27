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
  LockInAmplifier() : freqBand{0, even}, blockSize(0) {}

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
   * @param first Vector of doubles iterator to start of input vector
   * @param last Vector of doubles iterator to one past the end of the input vector
   * @param xOdd Vector of doubles iterator to beginning of xOdd output vector
   * @param yOdd Vector of doubles iterator to beginning of yOdd output vector
   */
  void operator()(const std::vector<double>::iterator first,
    const std::vector<double>::iterator last, std::vector<double>::iterator xOdd,
    std::vector<double>::iterator yOdd);

private:
  Band freqBand; ///< Frequency band. @see Band
  std::vector<double> sinLockInSignal; ///< Sinusoidal function for multiplication of the input signal.
  std::vector<double> cosLockInSignal; ///< Sinusoidal function for multiplication of the input signal.

  /// Vector of doubles iterator to beginning of phase shifted signal.
  std::vector<double>::iterator sinSignalBegin;
  std::vector<double>::iterator cosSignalBegin;

  /// Vector storing input block with halo.
  /**
   * Stores the input block as well as a halo in front. The halo consists of the last N-1 terms of the previous block
   * where N is the order of the filter. For the first block, the halo elements are 0.
   */
  std::vector<double> blockWithHalo1;
  std::vector<double>::iterator endOfHaloIt1; ///< Vector of doubles iterator to element after halo.
  std::vector<double>::iterator copyBeginIt1; ///< Vector of doubles iterator to beginning of last N-1 elements.

  /// Vector storing input block with halo.
  /**
   * Stores the input block as well as a halo in front. The halo consists of the last N-1 terms of the previous block
   * where N is the order of the filter. For the first block, the halo elements are 0.
   */
  std::vector<double> blockWithHalo2;
  std::vector<double>::iterator endOfHaloIt2; ///< Vector of doubles iterator to element after halo.
  std::vector<double>::iterator copyBeginIt2; ///< Vector of doubles iterator to beginning of last N-1 elements.

  std::size_t blockSize; ///< Size of the input block.
  LowPassFilter lpf; ///< Low pass filter

  void offset_phase(double phi); ///< Offsets phase of lock in signals by phi radians.
};
#endif// CPP_TEMPLATE_LPF_LOCKINAMPLIFIER_HPP
