#ifndef CYFROWEPRZETWARZANIESYGNALOW_TRANSFORMUTILITIES_H
#define CYFROWEPRZETWARZANIESYGNALOW_TRANSFORMUTILITIES_H


#include <vector>

class TransformUtilities {
public:
    static std::vector<double> generateSignal1(double duration, double fs);
    static std::vector<double> generateSignal2(double duration, double fs);
    static std::vector<double> generateSignal3(double duration, double fs);
};


#endif //CYFROWEPRZETWARZANIESYGNALOW_TRANSFORMUTILITIES_H
