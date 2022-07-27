#include <vector>
#include <string>

#include "filterCoefficientReader.hpp"
#include "BlockReader.hpp"
#include "BlockWriter.hpp"
#include "LowPassFilter.hpp"

#include "testConfig.hpp"

constexpr std::size_t blockSize(10000);

int main() {
  std::vector<double> coef = filterCoefficientReader(TEST_DATA_DIR "/filter_coefficients.bin");
  const std::size_t haloSize (coef.size() - 1);

  BlockReader blcRdr(TEST_DATA_DIR "/chirp_signal.bin", blockSize);
  BlockWriter blcWtr(TEST_DATA_DIR "/filtered_chirp_signal.bin");
  LowPassFilter lpf(coef);

  std::vector<double> blockAndHalo(blockSize+haloSize);
  std::vector<double> lpfOutput(blockSize);
  auto blockIter(std::begin(blockAndHalo) + static_cast<long>(haloSize));
  for (std::size_t i = 0; i < blcRdr.numOfBlocks(); i++) {
    blcRdr.readNextBlock(blockIter);

    lpf(blockIter, std::end(blockAndHalo), std::begin(lpfOutput));
    blcWtr.writeBlock(std::begin(lpfOutput), std::end(lpfOutput));
    std::copy(std::end(blockAndHalo) - static_cast<long>(haloSize), std::end(blockAndHalo), std::begin(blockAndHalo));
  }

  return 0;
}
