#include <algorithm>
#include <cmath>
#include <numbers>
#include <numeric>

#include "LowPassFilter.hpp"

#ifndef CPP_TEMPLATE_LPF_LOCKINAMPLIFIER_HPP
#define CPP_TEMPLATE_LPF_LOCKINAMPLIFIER_HPP

enum Parity { even, odd };
struct Band
{
  double frequency;
  Parity parity;
};
class LockInAmplifier
{
public:
  LockInAmplifier(std::vector<double> const &coefficients, std::size_t const sizeOfBlock);

  void set_signal(Band band);

  std::vector<double>::iterator operator()(const std::vector<double>::iterator first1,
    const std::vector<double>::iterator last1, std::vector<double>::iterator d_first);

protected:
  std::vector<double> lockInSignal;
  std::vector<double> blockWithHalo;
  std::vector<double>::iterator endOfHaloIt;
  std::vector<double>::iterator copyBeginIt;
  std::size_t blockSize;
  LowPassFilter lpf;
};
#endif// CPP_TEMPLATE_LPF_LOCKINAMPLIFIER_HPP
