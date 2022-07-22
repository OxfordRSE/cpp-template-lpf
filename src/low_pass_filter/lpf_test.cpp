#include <iostream>
#include <vector>
#include "filterCoefficientReader.hpp"
#include "BlockReader.hpp"
#include "BlockWriter.hpp"
#include "LowPassFilter.hpp"

constexpr std::size_t blockSize(10000);
constexpr std::size_t haloSize(1000);

int main() {
  std::vector<double> coef = filterCoefficientReader("../test_data/filterCoeff.bin");
  BlockReader blcRdr("../test_data/chirp_fMax=6.25E+07_fSamp=1.25E+08.bin", blockSize);
  BlockWriter blcWtr("../test_data/filtered_chirp_fMax=6.25E+07_fSamp=1.25E+08.bin");
  LowPassFilter lpf(coef);

  std::vector<double> blockAndHalo(blockSize+haloSize);
  std::vector<double> lpfOutput(blockSize);
  auto blockIter(std::begin(blockAndHalo)+haloSize);
  for (std::size_t i = 0; i < blcRdr.numOfBlocks(); i++) {
    blcRdr.readNextBlock(blockIter);

    lpf(blockIter, std::end(blockAndHalo), std::begin(lpfOutput));
    blcWtr.writeBlock(std::begin(lpfOutput), std::end(lpfOutput));
    std::copy(std::end(blockAndHalo)-haloSize, std::end(blockAndHalo), std::begin(blockAndHalo));
  }

  return 0;
}
