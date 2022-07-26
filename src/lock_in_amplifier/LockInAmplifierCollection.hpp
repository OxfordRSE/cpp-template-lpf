#include <vector>

#include "LockInAmplifier.hpp"

#ifndef CPP_TEMPLATE_LPF_LOCKINAMPLIFIERCOLLECTION_HPP
#define CPP_TEMPLATE_LPF_LOCKINAMPLIFIERCOLLECTION_HPP

/// @brief Class to store multiple lock in amplifiers.
/// @see LockInAmplifier
class LockInAmplifierCollection
{
public:
  /// Constructor
  /**
   * Constructs lock in amplifiers for each band in bands based on the input block size and low pass filter
   * coefficients.
   * @param coefficients Low pass filter coefficients.
   * @param bands Frequency bands of the individual lock in amplifiers.
   * @param blockSize Size of the input block.
   */
  LockInAmplifierCollection(std::vector<double> const &coefficients,
    std::vector<Band> const &bands,
    std::size_t const blockSize);

  /// Function call operator
  /**
   * Applies each lock in amplifier in the collection to an input block.
   * @param first1 Vector of doubles iterator to beginning of input block.
   * @param last1 Vector of doubles iterator to one past the end of the input block.
   * @param d_first Vector of doubles iterator to beginning of output block.
   */
  void operator()(std::vector<double>::iterator first1,
    std::vector<double>::iterator last1,
    std::vector<std::vector<double>>::iterator d_first);

private:
  std::vector<LockInAmplifier> LIA_vector; ///< Vector of lock in amplifiers.
};


#endif// CPP_TEMPLATE_LPF_LOCKINAMPLIFIERCOLLECTION_HPP
