#include <cmath>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "BlockReader.hpp"

BlockReader::BlockReader(const std::string &filename, std::size_t sizeOfBlock)
  : reader(filename, std::ios::in | std::ios::binary), blockSize(sizeOfBlock)
{
  if (!reader) { throw std::system_error(errno, std::system_category(), "Failed to open input data file for read"); }
  const std::filesystem::path pathToData(filename);
  const std::size_t sizeInBytes = std::filesystem::file_size(pathToData);
  const std::size_t numOfData = sizeInBytes / sizeof(double);
  double nBlocksDouble(static_cast<double>(numOfData) / static_cast<double>(sizeOfBlock));
  if (std::floor(nBlocksDouble) != std::ceil(nBlocksDouble)) {
    throw std::system_error(errno, std::system_category(), "The input data is not divisible by the block size");
  }
  nBlocks = std::floor(nBlocksDouble);
}

std::size_t BlockReader::numOfBlocks() const { return nBlocks; }

void BlockReader::readNextBlock(std::vector<double>::iterator d_first)
{
  //  NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  auto *const read_buffer = reinterpret_cast<char *>(&(*d_first));// cppcheck-suppress invalidPointerCast
  reader.read(read_buffer, static_cast<std::streamsize>(blockSize * sizeof(double)));
}