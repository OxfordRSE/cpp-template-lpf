#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <string>
#include <vector>
#include <utility>

#include "low_pass_filter.hpp"

class LowPassFilter
{
public:
  LowPassFilter(const std::size_t n, const std::vector<double>::iterator data_block)
    : m_weights(n), m_data_block(data_block)
  {
    const unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    std::generate(std::begin(m_weights), std::end(m_weights), [&]() { return distribution(generator); });
  }

  double operator()(const int i) const
  {
    return std::inner_product(
      std::begin(m_weights), std::end(m_weights), m_data_block + i - static_cast<long>(m_weights.size()), 0.);
  }

private:
  std::vector<double> m_weights;
  std::vector<double>::iterator m_data_block;
};


void cpp_template_lpf::low_pass_filter(std::ifstream &reader, std::ofstream &writer, const LpfConfig &config)
{
  const auto n_blocks = static_cast<std::size_t>(std::floor(config.input_data_size / config.block_data_size));
  // create some vectors for processing the data
  std::vector<double> halo_and_block(config.block_data_size + config.halo_size, 0.);
  std::vector<double> processed_block(config.block_data_size);
  std::vector<double> indices(config.block_data_size);
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
