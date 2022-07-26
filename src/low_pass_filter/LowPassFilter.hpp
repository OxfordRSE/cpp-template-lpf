#ifndef CPP_TEMPLATE_LPF_LOWPASSFILTER_HPP
#define CPP_TEMPLATE_LPF_LOWPASSFILTER_HPP

/// Class for a finite impulse response low pass filter.
/**
 * This class construct an low pass filter with a set of filter coefficients that can then be applied to input data
 * to perform a low pass filter algorithm.
 */
class LowPassFilter {
public:
  /// Default constructor
  LowPassFilter() : haloSize(0) {}

  /// Constructor
  /**
   * Constructor that sets the low pass filter with filter coefficients.
   * @param coefficients Low pass filter coefficients.
   */
  explicit LowPassFilter(std::vector<double> const &coefficients);

  /// Function call operator.
  /**
   * Applies the low pass filter algorithm to an input block and outputs to an output block.
   * @param first1
   * @param last1
   * @param d_first
   * @return The iterator to one past the end of the output block.
   */
  std::vector<double>::iterator operator()(std::vector<double>::iterator const first1,
    const std::vector<double>::iterator last1,
    std::vector<double>::iterator d_first);

private:
  std::vector<double> coef; ///< Low pass filter coefficients.
  std::size_t haloSize; ///< Size of the halo.

  /// Single operation of the low pass filter coefficients.
  /**
   * This function returns a single inner product application of the filter coefficients with the last filter
   * coefficient being multiplied by the element pointed to by the input iterator.
   * @param blockIter Vector of doubles iterator to element which last filter coefficient will multiply
   * @return The value of the inner product of the filter coefficients and data.
   */
  double lowPassFilterKernel(std::vector<double>::iterator blockIter);
};

#endif// CPP_TEMPLATE_LPF_LOWPASSFILTER_HPP