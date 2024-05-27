#ifndef CYFROWEPRZETWARZANIESYGNALOW_CONVOLUTION_H
#define CYFROWEPRZETWARZANIESYGNALOW_CONVOLUTION_H


#include <vector>

std::pair<std::vector<double>, std::vector<double>> discreteConvolution(
        const std::vector<double>& h, double hDeltaT, const std::vector<double>& x, double xDeltaT);

std::vector<double> resample(const std::vector<double>& signal, double originalDeltaT, double newDeltaT);



#endif //CYFROWEPRZETWARZANIESYGNALOW_CONVOLUTION_H
