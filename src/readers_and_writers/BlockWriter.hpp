//
// Created by sjoh5083 on 21/07/22.
//

#ifndef CPP_TEMPLATE_LPF_BLOCKWRITER_HPP
#define CPP_TEMPLATE_LPF_BLOCKWRITER_HPP

#include <fstream>

/// Class to write blocks of data to a binary data file.
/**
 * This class write blocks of data to a binary output file, creating an output file if it does not exist. The
 * data is written block by block.
 */
class BlockWriter {
public:
  /// Constructor
  /**
   * Creates an ofstream to open a file for writing creating one if it does not exist and overwriting it if the file
   * does exist.
   * @param filename Path to output binary data file.
   */
  explicit BlockWriter(const std::string &filename);

  /// Destructor
  ~BlockWriter();

  /// Function to write a block to output file.
  /**
   * Writes a block of data to the opened binary data file.
   * @param first Vector of doubles iterator to beginning of output data block.
   * @param last Vector of doubles iterator to one past the end of output data block.
   */
  void writeBlock(std::vector<double>::iterator first, std::vector<double>::iterator last);

private:
  std::ofstream writer; ///< Writer attached to the path of the output data file.
};


#endif// CPP_TEMPLATE_LPF_BLOCKWRITER_HPP
