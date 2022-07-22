//
// Created by sjoh5083 on 20/07/22.
//

#ifndef CPP_TEMPLATE_LPF_LOCKINAMPLIFIER_HPP
#define CPP_TEMPLATE_LPF_LOCKINAMPLIFIER_HPP

enum Parity {even, odd};
struct Band {
  double frequency;
  Parity parity;
};
class LockInAmplifier;

#endif// CPP_TEMPLATE_LPF_LOCKINAMPLIFIER_HPP
