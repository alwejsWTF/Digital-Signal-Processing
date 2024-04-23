#ifndef CYFROWEPRZETWARZANIESYGNALOW_SIGNALRECONSTRUCTION_H
#define CYFROWEPRZETWARZANIESYGNALOW_SIGNALRECONSTRUCTION_H


#include <vector>

class SignalReconstruction {
public:
    static std::pair<std::vector<double>, std::vector<double>> reconstructZOH(
            const std::vector<double>& samples,
            double originalSamplingRate,
            int reconstructionMultiplier
    );
    static std::pair<std::vector<double>, std::vector<double>> reconstructFOH(
            const std::vector<double>& samples,
            const std::vector<double>& time,
            double originalSamplingRate,
            int reconstructionMultiplier
    );
    static std::pair<std::vector<double>, std::vector<double>> reconstructSinc(
            const std::vector<double>& samples,
            const std::vector<double>& originalTime
    );
};


#endif //CYFROWEPRZETWARZANIESYGNALOW_SIGNALRECONSTRUCTION_H
