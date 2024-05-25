#ifndef CYFROWEPRZETWARZANIESYGNALOW_FILTERS_H
#define CYFROWEPRZETWARZANIESYGNALOW_FILTERS_H


#include <vector>

enum WindowType { RECTANGULAR, HAMMING, HANNING, BLACKMAN };
enum FilterType { LOW_PASS, HIGH_PASS };

std::vector<double> designFilter(int numCoeffs, double cutoffFreq, WindowType windowType, FilterType filterType);



#endif //CYFROWEPRZETWARZANIESYGNALOW_FILTERS_H
