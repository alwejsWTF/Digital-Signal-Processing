#include "signals/SignalReconstruction.h"
#include <cmath>

std::pair<std::vector<double>, std::vector<double>> SignalReconstruction::reconstructZOH(
        const std::vector<double>& samples,
        const std::vector<double>& originalTime
   ) {

    std::vector<double> reconstructed;
    std::vector<double> newTime;


    return {reconstructed, newTime};
}

std::pair<std::vector<double>, std::vector<double>> SignalReconstruction::reconstructFOH(
        const std::vector<double>& samples,
        const std::vector<double>& originalTime
) {
    std::vector<double> reconstructed;
    std::vector<double> time;

    return {reconstructed, time};
}

std::pair<std::vector<double>, std::vector<double>> SignalReconstruction::reconstructSinc(
        const std::vector<double>& samples,
        const std::vector<double>& originalTime
) {
    std::vector<double> reconstructed;
    std::vector<double> time;

    return {reconstructed, time};
}
