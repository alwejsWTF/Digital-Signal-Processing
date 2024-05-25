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

std::vector<double> designFilter(int numCoeffs, double cutoffFreq, WindowType windowType, FilterType filterType) {
    std::vector<double> h(numCoeffs);
    std::vector<double> window = generateWindow(numCoeffs, windowType);

    int M = numCoeffs - 1;
    double normFreq = 2 * M_PI * cutoffFreq;

    for (int n = 0; n <= M; ++n) {
        if (filterType == LOW_PASS) {
            if (n == M / 2) {
                h[n] = normFreq / M_PI;
            } else {
                h[n] = sin(normFreq * (n - M / 2)) / (M_PI * (n - M / 2));
            }
        } else if (filterType == HIGH_PASS) {
            if (n == M / 2) {
                h[n] = 1.0 - normFreq / M_PI;
            } else {
                h[n] = -sin(normFreq * (n - M / 2)) / (M_PI * (n - M / 2));
            }
        }
        h[n] *= window[n];
    }

    return h;
}