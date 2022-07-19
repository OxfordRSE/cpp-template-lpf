//
// Created by sjoh5083 on 19/07/2022.
//
class LockInAmplifier {
public:
  LockInAmplifier(double frequency, Config dataConfig)
  : conf(dataConfig) {
    lockInSignal = generate_signal(frequency, conf.size);
  }

  std::vector<double>::iterator LockInAmplifier(std::vector<double>::iterator blockIter) {
# TODO have to make sure no memory leak occurs
    lpfDataPtr = new vector<double>(conf.size);
    std::vector<double>::iterator lpfDataIter = lpfDataPtr->begin();
    outputDataPtr = new vector<double>(conf.size);
    std::vector<double>::iterator outputDataIter = outputDataPtr->begin();
    //multiply data from blockIter by lockInSignal and output to lpfDataIter
    //take this lpf data and apply low pass filter and output result to outputIter

    return outputIter
  }

private:
  std::vector<double> lockInSignal;
  Config conf;
};