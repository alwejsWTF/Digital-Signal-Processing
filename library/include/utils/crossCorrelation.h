#ifndef CYFROWEPRZETWARZANIESYGNALOW_CROSSCORRELATION_H
#define CYFROWEPRZETWARZANIESYGNALOW_CROSSCORRELATION_H


#include <vector>

std::vector<double> directCrossCorrelation(const std::vector<double>& h, const std::vector<double>& x);
std::vector<double> convolutionCrossCorrelation(const std::vector<double>& h, const std::vector<double>& x);


#endif //CYFROWEPRZETWARZANIESYGNALOW_CROSSCORRELATION_H
