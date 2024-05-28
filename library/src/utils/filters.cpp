#include "utils/filters.h"
#include <cmath>

std::vector<double> generateWindow(int numCoeffs, WindowType windowType) {
    std::vector<double> window(numCoeffs);

    switch(windowType) {
        case RECTANGULAR:
            std::fill(window.begin(), window.end(), 1.0);
            break;
        case HAMMING:
            for(int i = 0; i < numCoeffs; ++i) {
                window[i] = 0.54 - 0.46 * cos(2 * M_PI * i / (numCoeffs - 1));
            }
            break;
        case HANNING:
            for(int i = 0; i < numCoeffs; ++i) {
                window[i] = 0.5 * (1 - cos(2 * M_PI * i / (numCoeffs - 1)));
            }
            break;
        case BLACKMAN:
            for(int i = 0; i < numCoeffs; ++i) {
                window[i] = 0.42 - 0.5 * cos(2 * M_PI * i / (numCoeffs - 1)) + 0.08 * cos(4 * M_PI * i / (numCoeffs - 1));
            }
            break;
    }
    return window;
}

std::pair<std::vector<double>, std::vector<double>> designFilter(int numCoeffs, double samplingRate, double cutoffFreq, WindowType windowType, FilterType filterType) {
    std::vector<double> h(numCoeffs);
    std::vector<double> window = generateWindow(numCoeffs, windowType);
    std::vector<double> t(numCoeffs);

    int M = numCoeffs;
    double K = samplingRate / cutoffFreq;
    for (int n = 0; n <= (M - 1); ++n) {
        double timeIndex = n - (1.0 * M - 1) / 2;
        t[n] = 1.0 * n / (M - 1);
        if (timeIndex == 0) {
            h[n] = 2.0 / K;
        } else {
            h[n] = sin(2.0 * M_PI * timeIndex / K) / (M_PI * timeIndex);
        }
        if (filterType == LOW_PASS) {
            h[n] *= window[n];
        }
        else {
            h[n] *= pow(-1, n) * window[n];
        }
    }
    return {h, t};
}