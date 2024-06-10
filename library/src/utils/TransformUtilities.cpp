#include "utils/TransformUtilities.h"
#include <vector>
#include <cmath>

std::vector<double> TransformUtilities::generateSignal1(double duration, double fs) {
    int N = static_cast<int>(duration * fs);
    std::vector<double> signal(N);
    for (int i = 0; i < N; ++i) {
        double t = i / fs;
        signal[i] = 2 * sin(M_PI * t + M_PI/2) + 5 * sin(4 * M_PI * t + M_PI/2);
    }
    return signal;
}

std::vector<double> TransformUtilities::generateSignal2(double duration, double fs) {
    int N = static_cast<int>(duration * fs);
    std::vector<double> signal(N);
    for (int i = 0; i < N; ++i) {
        double t = i / fs;
        signal[i] = 2 * sin(M_PI * t) + sin(2 * M_PI * t) + 5 * sin(4 * M_PI * t);
    }
    return signal;
}

std::vector<double> TransformUtilities::generateSignal3(double duration, double fs) {
    int N = static_cast<int>(duration * fs);
    std::vector<double> signal(N);
    for (int i = 0; i < N; ++i) {
        double t = i / fs;
        signal[i] = 5 * sin(M_PI * t) + sin(8 * M_PI * t);
    }
    return signal;
}
