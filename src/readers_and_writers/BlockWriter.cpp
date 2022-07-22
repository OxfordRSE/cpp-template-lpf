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

int BlockWriter::writeBlock(std::vector<double>::iterator blockBegin, std::vector<double>::iterator blockEnd)
{
  // TODO maybe clean up the casting a bit
  auto blockSize(static_cast<std::size_t>(std::distance(blockBegin, blockEnd)));
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  auto *const write_buffer = reinterpret_cast<char *>(&(*blockBegin));// cppcheck-suppress invalidPointerCast
  writer.write(write_buffer, static_cast<std::streamsize>(blockSize * sizeof(double)));
  // TODO add error return?
  writer.flush();
  return 0;
}
