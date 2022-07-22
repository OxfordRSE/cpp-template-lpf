#ifndef CPP_TEMPLATE_LPF_LOWPASSFILTER_HPP
#define CPP_TEMPLATE_LPF_LOWPASSFILTER_HPP

class LowPassFilter {
public:
  double singleOperation(std::vector<double>::iterator blockIter);
  explicit LowPassFilter(std::vector<double> const &coefficients);
  void operator()(std::vector<double>::iterator inputBegin, std::vector<double>::iterator inputEnd,
    std::vector<double>::iterator outputBegin);

private:
  const std::vector<double> m_coef;
  const std::size_t haloSize;
  std::vector<double> processedData;
};

#endif// CPP_TEMPLATE_LPF_LOWPASSFILTER_HPP
