#ifndef CYFROWEPRZETWARZANIESYGNALOW_COSINETRANSFORM_H
#define CYFROWEPRZETWARZANIESYGNALOW_COSINETRANSFORM_H

#pragma once
#include <vector>
#include <complex>

class CosineTransform {
public:
    static std::vector<std::complex<double>> computeDCT(const std::vector<double>& input);
};


#endif //CYFROWEPRZETWARZANIESYGNALOW_COSINETRANSFORM_H
