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
    BlockWriter blcWtr1_X(TEST_DATA_DIR "/LIA_collection_output1_X.bin");
    BlockWriter blcWtr2_X(TEST_DATA_DIR "/LIA_collection_output2_X.bin");
    BlockWriter blcWtr1_Y(TEST_DATA_DIR "/LIA_collection_output1_Y.bin");
    BlockWriter blcWtr2_Y(TEST_DATA_DIR "/LIA_collection_output2_Y.bin");

    auto freq1 = config.at("f1").get<double>();
    auto freq2 = config.at("f2").get<double>();
    auto samp_freq = config.at("fs").get<double>();
    Band band1{freq1/samp_freq, odd};
    Band band2{freq2/samp_freq, odd};
    std::vector<Band> bands{band1, band2};
    LockInAmplifierCollection liaCollection(filterCoef, bands, blockSize);

    std::vector<double> inputBlock(blockSize);
    std::vector<std::vector<double>> outputManyBlocks_X(bands.size());
    std::vector<std::vector<double>> outputManyBlocks_Y(bands.size());
    for (auto &outputBlock : outputManyBlocks_X) {
      outputBlock = std::vector<double>(blockSize);
    }
    for (auto &outputBlock : outputManyBlocks_Y) {
      outputBlock = std::vector<double>(blockSize);
    }

    for (std::size_t i = 0; i < blcRdr.numOfBlocks(); i++) {
      blcRdr.readNextBlock(std::begin(inputBlock));
      liaCollection(std::begin(inputBlock), std::end(inputBlock), std::begin(outputManyBlocks_X), std::begin(outputManyBlocks_Y));
      blcWtr1_X.writeBlock(std::begin(outputManyBlocks_X[0]), std::end(outputManyBlocks_X[0]));
      blcWtr2_X.writeBlock(std::begin(outputManyBlocks_X[1]), std::end(outputManyBlocks_X[1]));
      blcWtr1_Y.writeBlock(std::begin(outputManyBlocks_Y[0]), std::end(outputManyBlocks_Y[0]));
      blcWtr2_Y.writeBlock(std::begin(outputManyBlocks_Y[1]), std::end(outputManyBlocks_Y[1]));
    }
  }
  catch (std::system_error &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  catch (...) {
    std::cerr << "unknown exception" << std::endl;
    return 1;
  }

  return 0;
}