#ifndef CYFROWEPRZETWARZANIESYGNALOW_SIGNALRECONSTRUCTION_H
#define CYFROWEPRZETWARZANIESYGNALOW_SIGNALRECONSTRUCTION_H


#include <vector>

class SignalReconstruction {
public:
    static std::pair<std::vector<double>, std::vector<double>> reconstructZOH(
            const std::vector<double>& samples,
            double startTime,
            double originalSamplingRate,
            int reconstructionMultiplier
    );
    static std::pair<std::vector<double>, std::vector<double>> reconstructFOH(
            const std::vector<double>& samples,
            double startTime,
            double originalSamplingRate,
            int reconstructionMultiplier
    );
    static std::pair<std::vector<double>, std::vector<double>> reconstructSinc(
            const std::vector<double>& samples,
            double startTime,
            double originalSamplingRate,
            int reconstructionMultiplier
    );
};


#endif //CYFROWEPRZETWARZANIESYGNALOW_SIGNALRECONSTRUCTION_H
