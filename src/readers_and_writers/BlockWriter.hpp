//
// Created by sjoh5083 on 21/07/22.
//

#ifndef CPP_TEMPLATE_LPF_BLOCKWRITER_HPP
#define CPP_TEMPLATE_LPF_BLOCKWRITER_HPP

#include <fstream>

class BlockWriter {
public:
  explicit BlockWriter(const std::string &filename);
  ~BlockWriter();
  int writeBlock(std::vector<double>::iterator blockBegin, std::vector<double>::iterator blockEnd);

private:
  std::ofstream writer;
};


#endif// CPP_TEMPLATE_LPF_BLOCKWRITER_HPP
