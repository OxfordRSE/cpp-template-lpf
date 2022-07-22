#ifndef CPP_TEMPLATE_LPF_DATACONFIG_HPP
#define CPP_TEMPLATE_LPF_DATACONFIG_HPP

#include <cstddef>

namespace cpp_template_lpf {
  struct DataConfig {
    const static std::size_t DEFAULT_INPUT_DATA_SIZE = 1250000U; ///< The default input data size
    const static std::size_t DEFAULT_BLOCK_DATA_SIZE = 10000U; ///< The default block data size
    const static std::size_t DEFAULT_HALO_SIZE = 1000U; ///< The default size of the halo
    const static std::size_t DEFAULT_LPF_SIZE = 1001U; ///< The default size of the low pass filter coefficients
    std::size_t input_data_size = DEFAULT_INPUT_DATA_SIZE; ///< The size of the input data
    std::size_t block_data_size = DEFAULT_BLOCK_DATA_SIZE; ///< The size of the block
    std::size_t halo_size = DEFAULT_HALO_SIZE; ///< The size of the halo
    std::size_t lpf_size = DEFAULT_LPF_SIZE; ///< The size of the low pass filter coefficients

  };
} // namespace cpp_template_lpf


#endif// CPP_TEMPLATE_LPF_DATACONFIG_HPP
