#ifndef CYFROWEPRZETWARZANIESYGNALOW_QUANTIZER_H
#define CYFROWEPRZETWARZANIESYGNALOW_QUANTIZER_H


#include <vector>

class Quantizer {
public:
    static std::vector<double> uniformQuantize(const std::vector<double>& samples, int levels, bool flag);
};


#endif //CYFROWEPRZETWARZANIESYGNALOW_QUANTIZER_H
