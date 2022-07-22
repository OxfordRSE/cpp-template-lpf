#include <vector>
#include <utility>
#include "LockInAmplifier.hpp"

class LockInAmplifierCollection {
public:
  LockInAmplifierCollection(std::vector<Band> &bands, std::size_t blockSize) {

  }


//  std::vector<double>::iterator operator()(std::vector<double>::iterator blockIter) {
//    LockInAmplifier LIA = LIA_vector[index];
//    return LIA(blockIter);
//  }
private:
//    std::vector<LockInAmplifier> LIA_vector;
  int num;
};