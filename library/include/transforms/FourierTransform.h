#ifndef CYFROWEPRZETWARZANIESYGNALOW_FOURIERTRANSFORM_H
#define CYFROWEPRZETWARZANIESYGNALOW_FOURIERTRANSFORM_H

#pragma once
#include <vector>
#include <complex>

class FourierTransform {
public:
    static std::vector<std::complex<double>> computeDFT(const std::vector<double>& input);
};


#endif //CYFROWEPRZETWARZANIESYGNALOW_FOURIERTRANSFORM_H
