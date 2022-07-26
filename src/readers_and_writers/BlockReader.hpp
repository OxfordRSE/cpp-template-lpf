//
// Created by sjoh5083 on 20/07/22.
//

#ifndef CPP_TEMPLATE_LPF_BLOCKREADER_HPP
#define CPP_TEMPLATE_LPF_BLOCKREADER_HPP

#include <fstream>

/// Class to read blocks of binary input data from file.
/**
 * This class reads input data from binary files. The data is read block by block.
 */
class BlockReader {
public:
  /// Constructor
  /**
   * Creates an ifstream to a filename opening the file for reading of input data.
   * @param filename  Path to input binary data file.
   * @param sizeOfBlock Size of blocks in number of doubles at which the file will be read.
   */
  BlockReader(const std::string &filename, std::size_t sizeOfBlock);

  /// Returns the number of blocks in the input data file.
  /**
   * @return Number of blocks in data file.
   */
  std::size_t numOfBlocks() const;

  /// Reads the next block of data from file.
  /**
   * Reads a block of data from initialized ifstream to given output block.
   * @param d_first Vector of doubles iterator to beginning of output block.
   */
  void readNextBlock(std::vector<double>::iterator d_first);

  /// Destructor
  ~BlockReader() {reader.close();}

private:
  std::ifstream reader; ///< Reader attached to the path of the input data.
  std::size_t blockSize; ///< Size of data block in number of doubles.
  std::size_t nBlocks; ///< Number of blocks stored in the input data file.
};
#endif// CPP_TEMPLATE_LPF_BLOCKREADER_HPP
