#include <iostream>
#include <vector>

#include "BlockReader.hpp"
#include "BlockWriter.hpp"
#include "LockInAmplifier.hpp"
#include "filterCoefficientReader.hpp"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include "testConfig.hpp"

constexpr std::size_t blockSize(50000);

int main()
{
  try {
    std::vector<double> filterCoef = filterCoefficientReader(TEST_DATA_DIR "/filter_coefficients.bin");

    std::ifstream ifs(TEST_DATA_DIR "/LIA_input.txt");
    json config(json::parse(ifs));
    BlockReader blcRdr(TEST_DATA_DIR "/LIA_input.bin", blockSize);
    BlockWriter blcWtrX(TEST_DATA_DIR "/LIA_output_X.bin");
    BlockWriter blcWtrY(TEST_DATA_DIR "/LIA_output_Y.bin");

    auto freq = config.at("f").get<double>();
    auto samp_freq = config.at("fs").get<double>();
    Band band{ freq / samp_freq, odd };
    LockInAmplifier lia(filterCoef, band, blockSize);

    std::vector<double> inputBlock(blockSize);
    std::vector<double> outputBlockX(blockSize);
    std::vector<double> outputBlockY(blockSize);

    for (std::size_t i = 0; i < blcRdr.numOfBlocks(); i++) {
      blcRdr.readNextBlock(std::begin(inputBlock));
      lia(std::begin(inputBlock), std::end(inputBlock), std::begin(outputBlockX), std::begin(outputBlockY));
      blcWtrX.writeBlock(std::begin(outputBlockX), std::end(outputBlockX));
      blcWtrY.writeBlock(std::begin(outputBlockY), std::end(outputBlockY));
    }
  } catch (std::system_error &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  } catch (...) {
    std::cerr << "unknown exception" << std::endl;
    return 1;
  }

  return 0;
}