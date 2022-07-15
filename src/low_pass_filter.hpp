#ifndef cpp_template_lpf_LOW_PASS_FILTER_HPP
#define cpp_template_lpf_LOW_PASS_FILTER_HPP

#include <fstream>
#include "LpfConfig.hpp"

namespace cpp_template_lpf {
const std::size_t MAX_PRINT_LINES (20);
void low_pass_filter(std::ifstream &reader, std::ofstream &writer, const cpp_template_lpf::LpfConfig &config);

}

#endif
