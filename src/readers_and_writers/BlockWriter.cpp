#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "BlockWriter.hpp"

BlockWriter::BlockWriter(const std::string &filename) : writer(filename, std::ios::out | std::ios::binary)
{
  if (!writer) { throw std::system_error(errno, std::system_category(), "Failed to open output data file for write"); }
}

BlockWriter::~BlockWriter()
{
  writer.close();
}

void BlockWriter::writeBlock(std::vector<double>::iterator first, std::vector<double>::iterator last)
{
  auto blockSize(static_cast<std::size_t>(std::distance(first, last)));
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  auto *const write_buffer = reinterpret_cast<char *>(&(*first));// cppcheck-suppress invalidPointerCast
  writer.write(write_buffer, static_cast<std::streamsize>(blockSize * sizeof(double)));
  writer.flush();
}
