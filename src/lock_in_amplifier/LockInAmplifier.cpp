#include <algorithm>
#include <numeric>
#include <cmath>
#include <numbers>
#include "LockInAmplifier.hpp"

//TODO should use namespaces
//TODO block size should be macro or constexpr?
class LockInAmplifier {
public:

  explicit LockInAmplifier(std::size_t sizeOfBlock)
  :  lockInSignal(sizeOfBlock), blockSize(sizeOfBlock) {};

  std::vector<double>::iterator operator()(std::vector<double>::iterator blockIter) {
  //TODO have to make sure no memory leak occurs
    auto *lpfDataPtr = new std::vector<double>(blockSize);
    auto lpfDataIter = lpfDataPtr->begin();
    auto *outputDataPtr = new std::vector<double>(blockSize);
    auto outputDataIter = outputDataPtr->begin();
    blockIter;
    //multiply data from blockIter by lockInSignal and output to lpfDataIter
    //take this lpf data and apply low pass filter and output result to outputIter

    return outputDataIter;
  }

protected:
  std::vector<double> lockInSignal;
  std::size_t blockSize;
};

class EvenLockInAmplifier : public LockInAmplifier {
public:
  EvenLockInAmplifier(double frequency, std::size_t sizeOfBlock)
  : LockInAmplifier(sizeOfBlock) {
    std::vector<int> indices(blockSize);
    std::iota(std::begin(indices), std::end(indices), 0);
    std::transform(std::begin(indices),
      std::end(indices),
      std::begin(lockInSignal),
      [frequency](int i) {return std::sin(2 * std::numbers::pi * frequency * i);}
      );
  }
};

class OddLockInAmplifier : public LockInAmplifier {
public:
  OddLockInAmplifier(double frequency, std::size_t sizeOfBlock)
    : LockInAmplifier(sizeOfBlock) {
    std::vector<int> indices(blockSize);
    std::iota(std::begin(indices), std::end(indices), 0);
    std::transform(std::begin(indices),
      std::end(indices),
      std::begin(lockInSignal),
      [frequency](int i) {return std::cos(2 * std::numbers::pi * frequency * i);}
    );
  }
};