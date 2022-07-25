#include <catch2/catch_test_macros.hpp>

#include <string>
#include <map>

#include "meta_data_reader.hpp"
#include "testConfig.hpp"

// values for test case come from metaDataTest file
TEST_CASE("Testing meta data reader", "[meta_data_reader]") {
  std::map<std::string, std::string> dict = meta_data_reader(TEST_DATA_DIR "/metaDataTest");

  REQUIRE(dict["fSamp"] == "3.123");
  REQUIRE(dict["blockSize"] == "1000");
  REQUIRE(dict["T"] == "3");
}