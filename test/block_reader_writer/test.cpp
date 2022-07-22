#include <catch2/catch_test_macros.hpp>

#include <vector>
#include <numeric>

#include "testConfig.hpp"
#include "filterCoefficientReader.hpp"
#include "BlockReader.hpp"
#include "BlockWriter.hpp"

TEST_CASE( "Testing reading and writing from file", "[ReaderAndWriter]") {
  //TODO maybe not the best way of using a macro
  BlockWriter coefWriter("testFilterCoef.bin");
  std::vector<double> coef(1001); // NOLINT
  coefWriter.writeBlock(std::begin(coef), std::end(coef));
  std::vector<double> readCoef (filterCoefficientReader("testFilterCoef.bin"));

  CHECK(readCoef.size() == coef.size());
  REQUIRE(readCoef == coef);

  BlockWriter blcWtr("testBlockReader.bin");
  std::size_t blockSize(1000); // NOLINT
  std::vector<double> block(blockSize);
  std::iota(std::begin(block), std::end(block), -15./static_cast<double>(blockSize)); // NOLINT
  std::size_t nBlocks(10); // NOLINT
  BlockReader blcRdr("testBlockReader.bin", blockSize);
  for (std::size_t i = 0; i < nBlocks; i++) {
    blcWtr.writeBlock(std::begin(block), std::end(block));
  }
  std::vector<double> tempBlock(blockSize);
  for (std::size_t i = 0; i < nBlocks; i++) {
    blcRdr.readNextBlock(std::begin(tempBlock));
    REQUIRE(tempBlock == block);
  }
}

