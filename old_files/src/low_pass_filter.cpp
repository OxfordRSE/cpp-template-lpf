#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <string>
#include <vector>
#include <utility>
#include <execution>

#include "low_pass_filter.hpp"
/// Low pass filter class
/**
 * This class reads the filter coefficients from file and applies them to a given index on the input.
 */
class LowPassFilter
{
public:
    /// The class constructor
    /**
     * Reads the filter coefficients from file and assigns an iterator for the input data.
     * @param n integer argument that determines the number of filter coefficients
     * @param data_block a vector<double> iterator to the input data
     */
    LowPassFilter(const std::size_t n, std::vector<double>::iterator data_block) : m_weights(n),
                                                                                   m_data_block(data_block) {
        //Read binary file for filter coefficients
        const std::string filename = "../test_data/filterCoeff.bin";
        std::ifstream reader(filename, std::ios::in | std::ios::binary);
        if (!reader) { throw std::system_error(errno, std::system_category(),
                                               "Failed to open filter coefficient file for read"); }

        const auto weights_iter = std::begin(m_weights);

        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
        auto *const read_buffer = reinterpret_cast<char *>(&(*weights_iter));// cppcheck-suppress invalidPointerCast
        reader.read(read_buffer, static_cast<std::streamsize>(n * sizeof(double)));
        reader.close();
    }

    /// Function call operator to apply filter coefficients
    /**
     * The operator takes the inner product between the filter coefficient vector and the input data
     * at the index defined by i.
     * @param i the index of the input data at which the last filter coefficient will be applied
     * @return the filtered data
     */
  double operator()(const int i) const
  {
    return std::transform_reduce(std::execution::par_unseq,
      std::begin(m_weights), std::end(m_weights), m_data_block + i - static_cast<long>(m_weights.size())+1, 0.);
  }

private:
  std::vector<double> m_weights; ///< vector for the filter coefficients
  std::vector<double>::iterator m_data_block; ///< iterator to the input data
};

/// Function to read the input signal from file and output to file the filtered signal
/**
 * Takes the reader for the input data and the configuration parameters for the input data and low pass filter. The low
 * pass filter is applied to the input data and the filtered data is outputted to file.
 * @param reader ifstream of the input data
 * @param writer ofstream for the destination of the filtered signal
 * @param config struct giving the configuration parameter
 * @see Lpfconthefig
 */
void cpp_template_lpf::low_pass_filter(std::ifstream &reader, std::ofstream &writer, const LpfConfig &config)
{
  const auto n_blocks = static_cast<std::size_t>(std::ceil(config.input_data_size / config.block_data_size));
  // create some vectors for processing the data
  std::vector<double> halo_and_block(config.block_data_size + config.halo_size, 0.);
  std::vector<double> processed_block(config.block_data_size);
  std::vector<int> indices(config.block_data_size);
  std::iota(std::begin(indices), std::end(indices), 0);

  // get an iterator to the actual data block (after the halo)
  using diff_type = std::vector<double>::difference_type;
  const auto block = std::begin(halo_and_block) + static_cast<diff_type>(config.halo_size);

  // create our low pass filter functor
  LowPassFilter lpf(config.lpf_size, block);

  // read in a new data block at each iteration, process it, then write to the
  // output file
  // we need a "halo" of data at the start of the halo_and_block vector that is at least
  // the size of the low pass filter weights, initially this will be 0, but at the end
  // of each iteration we will fill this "halo" using the last data block
  for (std::size_t i = 0; i < n_blocks; i++) {

    // read next block
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    auto *const read_buffer = reinterpret_cast<char *>(&(*block));// cppcheck-suppress invalidPointerCast
    reader.read(read_buffer, static_cast<std::streamsize>(config.block_data_size * sizeof(double)));

    // perform low pass filter
    std::transform(std::begin(indices), std::end(indices), std::begin(processed_block), lpf);

    // write out processed_block
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    auto *const write_buffer = reinterpret_cast<char *>(processed_block.data());// cppcheck-suppress invalidPointerCast
    writer.write(write_buffer, static_cast<std::streamsize>(config.block_data_size * sizeof(double)));

    // put last halo_size elements to the start of the current block, ready for
    // the next block
    std::copy(std::end(halo_and_block) - static_cast<diff_type>(config.halo_size),
      std::end(halo_and_block),
      std::begin(halo_and_block));
  }
}