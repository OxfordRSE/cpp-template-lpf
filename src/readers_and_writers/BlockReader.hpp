//
// Created by sjoh5083 on 20/07/22.
//

#ifndef CPP_TEMPLATE_LPF_BLOCKREADER_HPP
#define CPP_TEMPLATE_LPF_BLOCKREADER_HPP

#include <fstream>

class BlockReader {
public:
  BlockReader(const std::string &filename, std::size_t sizeOfBlock);
  std::size_t numOfBlocks() const;

  void readNextBlock(std::vector<double>::iterator start);

  ~BlockReader() {reader.close();}

private:
  std::ifstream reader;
  std::size_t blockSize;
  std::size_t nBlocks;
};
#endif// CPP_TEMPLATE_LPF_BLOCKREADER_HPP
