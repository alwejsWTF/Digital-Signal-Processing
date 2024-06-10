#ifndef CYFROWEPRZETWARZANIESYGNALOW_HADAMARDTRANSFORM_H
#define CYFROWEPRZETWARZANIESYGNALOW_HADAMARDTRANSFORM_H

#pragma once
#include <complex>
#include <vector>

class HadamardTransform {
public:
    static std::vector<std::complex<double>> computeHadamard(const std::vector<double>& input);
};


#endif //CYFROWEPRZETWARZANIESYGNALOW_HADAMARDTRANSFORM_H
