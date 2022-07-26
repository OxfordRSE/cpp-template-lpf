#ifndef CPP_TEMPLATE_LPF_LOWPASSFILTER_HPP
#define CPP_TEMPLATE_LPF_LOWPASSFILTER_HPP

class LowPassFilter {
public:
  double singleOperation(std::vector<double>::iterator blockIter);

  LowPassFilter() : haloSize(0) {}

  explicit LowPassFilter(std::vector<double> const &coefficients);

  std::vector<double>::iterator operator()(const std::vector<double>::iterator inputBegin,
    const std::vector<double>::iterator inputEnd,
    std::vector<double>::iterator outputBegin);

private:
  std::vector<double> coef;
  std::size_t haloSize;
};

#endif// CPP_TEMPLATE_LPF_LOWPASSFILTER_HPP