#ifndef CYFROWEPRZETWARZANIESYGNALOW_CROSSCORRELATION_H
#define CYFROWEPRZETWARZANIESYGNALOW_CROSSCORRELATION_H


#include <vector>

std::pair<std::vector<double>, std::vector<double>> directCrossCorrelation(
        const std::vector<double>& h, double hDeltaT, const std::vector<double>& x, double xDeltaT);
std::vector<double> convolutionCrossCorrelation(const std::vector<double>& h, const std::vector<double>& x);


#endif //CYFROWEPRZETWARZANIESYGNALOW_CROSSCORRELATION_H
