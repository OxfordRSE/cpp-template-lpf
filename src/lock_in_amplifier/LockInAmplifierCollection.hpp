#include <vector>

#include "LockInAmplifier.hpp"

#ifndef CPP_TEMPLATE_LPF_LOCKINAMPLIFIERCOLLECTION_HPP
#define CPP_TEMPLATE_LPF_LOCKINAMPLIFIERCOLLECTION_HPP

class LockInAmplifierCollection
{
public:
  LockInAmplifierCollection(std::vector<double> const &coefficients,
    std::vector<Band> const &bands,
    std::size_t const blockSize);

  void operator()(std::vector<double>::iterator first1,
    std::vector<double>::iterator last1,
    std::vector<std::vector<double>>::iterator d_first);

private:
  std::vector<LockInAmplifier> LIA_vector;
};


#endif// CPP_TEMPLATE_LPF_LOCKINAMPLIFIERCOLLECTION_HPP
