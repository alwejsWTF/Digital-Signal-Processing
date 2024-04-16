#ifndef CYFROWEPRZETWARZANIESYGNALOW_QUANTIZER_H
#define CYFROWEPRZETWARZANIESYGNALOW_QUANTIZER_H


#include <vector>

class Quantizer {
public:
    static std::vector<int> uniformQuantize(const std::vector<double>& samples, int levels);
};


#endif //CYFROWEPRZETWARZANIESYGNALOW_QUANTIZER_H
