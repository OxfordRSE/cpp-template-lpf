#ifndef cpp_template_lpf_LPFCONFIG_HPP
#define cpp_template_lpf_LPFCONFIG_HPP

#include <cstddef>


namespace cpp_template_lpf {

struct LpfConfig
{
  const static size_t DEFAULT_INPUT_DATA_SIZE = 1e2;
  const static size_t DEFAULT_BLOCK_DATA_SIZE = 1e2;
  const static size_t DEFAULT_HALO_SIZE = 10;
  const static size_t DEFAULT_LPF_SIZE = 10;
  size_t input_data_size = DEFAULT_INPUT_DATA_SIZE;
  size_t block_data_size = DEFAULT_BLOCK_DATA_SIZE;
  size_t halo_size = DEFAULT_HALO_SIZE;
  size_t lpf_size = DEFAULT_LPF_SIZE;
};

}// namespace cpp_template_lpf

#endif
