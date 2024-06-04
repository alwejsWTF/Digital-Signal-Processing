#ifndef CYFROWEPRZETWARZANIESYGNALOW_SENSOR_H
#define CYFROWEPRZETWARZANIESYGNALOW_SENSOR_H
#include <vector>
#include "typedefs.h"

class Sensor  {
public:
    Sensor(SignalPtr signal, double term, double propagationSpeed);
    double simulateEchoAndCalculateDistance(double objectDistance, double objectSpeed);

    std::vector<double> getTransmitted() const;
    std::vector<double> getReceived() const;
    std::vector<double> getCrossCorrelation() const;
    std::vector<double> getTimeVector() const;
    std::vector<double> getTimeVectorCross() const;
    std::vector<double> getTimeVectorCrossPlot() const;
    std::vector<double> getCrossCorrelationPlot() const;

private:
    SignalPtr signal;
    double term;
    double propagationSpeed;

    std::vector<double> transmittedSignal;
    std::vector<double> receivedSignal;
    std::vector<double> crossCorrelation;
    std::vector<double> timeVector;
    std::vector<double> timeVectorCross;
    std::vector<double> crossCorrelationPlot;
    std::vector<double> timeVectorCrossPlot;
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_SENSOR_H
