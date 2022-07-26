#include <vector>
#include <iostream>

#include "BlockReader.hpp"
#include "BlockWriter.hpp"
#include "LockInAmplifier.hpp"
#include "filterCoefficientReader.hpp"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include "testConfig.hpp"

constexpr std::size_t blockSize(50000);

int main() { //NOLINT
  try {
    std::vector<double> filterCoef = filterCoefficientReader(TEST_DATA_DIR "/filterCoeff.bin");

    std::ifstream ifs(TEST_DATA_DIR "/LIA_input.txt");
    json config(json::parse(ifs));
    BlockReader blcRdr(TEST_DATA_DIR "/LIA_input.bin", blockSize);
    BlockWriter blcWtr(TEST_DATA_DIR "/LIA_output.bin");
    LockInAmplifier lia(filterCoef, blockSize);
    auto freq = config.at("f").get<double>();
    auto samp_freq = config.at("fs").get<double>();
    Band band{freq/samp_freq, odd};
    lia.set_signal(band);

    std::vector<double> inputBlock(blockSize);
    std::vector<double> outputBlock(blockSize);

    for (std::size_t i = 0; i < blcRdr.numOfBlocks(); i++) {
      blcRdr.readNextBlock(std::begin(inputBlock));
      lia(std::begin(inputBlock), std::end(inputBlock), std::begin(outputBlock));
      blcWtr.writeBlock(std::begin(outputBlock), std::end(outputBlock));
    }
  }
  catch (std::system_error &e) {
    std::cerr << e.what() << std::endl;
  }
//  catch (...) {
//    std::cerr << "unknown exception" << std::endl;
//  }

  return 0;
}