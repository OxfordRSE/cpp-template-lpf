#ifndef CPP_TEMPLATE_LPF_FILTERCOEFFICIENTREADER_HPP
#define CPP_TEMPLATE_LPF_FILTERCOEFFICIENTREADER_HPP

/// \file filterCoefficientReader.hpp

/// Function to read filter coefficients from binary file.
/**
 * @param filename Path to binary file for filter coefficients.
 * @return Vector of doubles of filter coefficients.
 */
std::vector<double> filterCoefficientReader(const std::string &filename);

#endif// CPP_TEMPLATE_LPF_FILTERCOEFFICIENTREADER_HPP
