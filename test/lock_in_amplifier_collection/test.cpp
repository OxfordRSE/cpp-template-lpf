#include <vector>
#include <iostream>

#include "BlockReader.hpp"
#include "BlockWriter.hpp"
#include "LockInAmplifier.hpp"
#include "LockInAmplifierCollection.hpp"
#include "filterCoefficientReader.hpp"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include "testConfig.hpp"

constexpr std::size_t blockSize(50000);

int main() {
  try {
    std::vector<double> filterCoef = filterCoefficientReader(TEST_DATA_DIR "/filter_coefficients.bin");

    std::ifstream ifs(TEST_DATA_DIR "/LIA_collection_input.txt");
    json config(json::parse(ifs));
    BlockReader blcRdr(TEST_DATA_DIR "/LIA_collection_input.bin", blockSize);
    BlockWriter blcWtr1(TEST_DATA_DIR "/LIA_collection_output1.bin");
    BlockWriter blcWtr2(TEST_DATA_DIR "/LIA_collection_output2.bin");

    auto freq1 = config.at("f1").get<double>();
    auto freq2 = config.at("f2").get<double>();
    auto samp_freq = config.at("fs").get<double>();
    Band band1{freq1/samp_freq, odd};
    Band band2{freq2/samp_freq, odd};
    std::vector<Band> bands{band1, band2};
    LockInAmplifierCollection liaCollection(filterCoef, bands, blockSize);

    std::vector<double> inputBlock(blockSize);
    std::vector<std::vector<double>> outputManyBlocks(bands.size());
    for (auto &outputBlock : outputManyBlocks) {
      outputBlock = std::vector<double>(blockSize);
    }

    for (std::size_t i = 0; i < blcRdr.numOfBlocks(); i++) {
      blcRdr.readNextBlock(std::begin(inputBlock));
      liaCollection(std::begin(inputBlock), std::end(inputBlock), std::begin(outputManyBlocks));
      blcWtr1.writeBlock(std::begin(outputManyBlocks[0]), std::end(outputManyBlocks[0]));
      blcWtr2.writeBlock(std::begin(outputManyBlocks[1]), std::end(outputManyBlocks[1]));

    }
  }
  catch (std::system_error &e) {
    std::cerr << e.what() << std::endl;
  }
  catch (...) {
    std::cerr << "unknown exception" << std::endl;
  }

  return 0;
}