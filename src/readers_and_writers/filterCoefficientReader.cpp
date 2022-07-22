#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "filterCoefficientReader.hpp"

//TODO Find the filter size from the size of the coefficient file
std::vector<double> filterCoefficientReader(const std::string &filename) {
  const std::filesystem::path pathToCoefficients(filename);
  const std::size_t sizeInBytes = std::filesystem::file_size(pathToCoefficients);
  const std::size_t filterSize = sizeInBytes/sizeof(double);

  std::ifstream reader(filename, std::ios::in | std::ios::binary);

  std::vector<double> coefficients(filterSize);

  if (!reader) { throw std::system_error(errno, std::system_category(),
    "Failed to open filter coefficient file for read"); }

  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  auto *const read_buffer = reinterpret_cast<char *>(coefficients.data());// cppcheck-suppress invalidPointerCast
  reader.read(read_buffer, static_cast<std::streamsize>(filterSize * sizeof(double)));
  reader.close();
  return coefficients;
}