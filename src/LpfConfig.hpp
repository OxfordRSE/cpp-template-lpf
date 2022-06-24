#ifndef cpp_template_lpf_LPFCONFIG_HPP
#define cpp_template_lpf_LPFCONFIG_HPP

#include <cstddef>


namespace cpp_template_lpf {

struct LpfConfig
{
  const static std::size_t DEFAULT_INPUT_DATA_SIZE = 1000U;
  const static std::size_t DEFAULT_BLOCK_DATA_SIZE = 100U;
  const static std::size_t DEFAULT_HALO_SIZE = 10U;
  const static std::size_t DEFAULT_LPF_SIZE = 10U;
  std::size_t input_data_size = DEFAULT_INPUT_DATA_SIZE;
  std::size_t block_data_size = DEFAULT_BLOCK_DATA_SIZE;
  std::size_t halo_size = DEFAULT_HALO_SIZE;
  std::size_t lpf_size = DEFAULT_LPF_SIZE;
};

}// namespace cpp_template_lpf

#endif
