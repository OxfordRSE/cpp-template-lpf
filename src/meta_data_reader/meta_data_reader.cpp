#include <map>
#include <string>
#include <fstream>
#include <system_error>

std::map<std::string, std::string> meta_data_reader(const std::string &filename) {
  std::map<std::string, std::string> dict;
  std::ifstream reader (filename);
  if (!reader) {
    throw std::system_error(errno, std::system_category(), "Failed to open " + filename);
  }
  std::string key;
  std::string value;
  while (reader >> key) {
    if (!(reader >> value)) {
      throw std::runtime_error("Key is missing a value in file");
    }
    dict.insert({key, value});
  }
  return dict;
}