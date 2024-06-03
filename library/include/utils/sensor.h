#ifndef CYFROWEPRZETWARZANIESYGNALOW_SENSOR_H
#define CYFROWEPRZETWARZANIESYGNALOW_SENSOR_H
#include <vector>
#include "typedefs.h"

class Sensor  {
public:
    Sensor(SignalPtr signal, double propagationSpeed);

    void simulateEcho(double objectDistance, double objectSpeed);
    void performCrossCorrelation();
    double calculateDistance();
    void updateAndReport();

    std::vector<double> getTransmitted() const;
    std::vector<double> getReceived() const;
    std::vector<double> getCrossCorrelation() const;
    std::vector<double> getTimeVectorTransmitted() const;
    std::vector<double> getTimeVectorReceived() const;
    std::vector<double> getTimeVectorCrossCorrelation() const;

private:
    SignalPtr signal;
    double propagationSpeed;
    double objectDistance;
    double objectSpeed;

    std::vector<double> transmittedSignal;
    std::vector<double> receivedSignal;
    std::vector<double> crossCorrelation;
    std::vector<double> timeVectorCrossCorrelation;

    int reportPeriod;
    int reportCounter;
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_SENSOR_H
