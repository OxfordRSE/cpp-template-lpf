//
// Created by sjoh5083 on 19/07/2022.
//

#include <vector>
#include "LockInAmplifier.h"

class LockInAmplifierCollection {
public:
  LockInAmplifierCollection(std::vector<double> frequencies, std::vector<double>::iterator iteratorToBlock, Config conf)
    : blockIter{iteratorToBlock}, LIA_vector{frequencies.size()} {
    for (i = 0; i < LIA_vector.size(); i++) {
      LIA_vector[i] = LockInAmplifier(frequency, conf);
    }
  }

  std::vector<double>::iterator LockInAmplifierCollection(i) {
    LIA = LIA_vector[i];
    return LIA(blockIter);
  }
private:
    std::vector<double>::iterator blockIter
    std::vector<LockInAmplifier> LIA_vector;
};