#ifndef CYFROWEPRZETWARZANIESYGNALOW_SENSOR_H
#define CYFROWEPRZETWARZANIESYGNALOW_SENSOR_H
#include <vector>

class Sensor {
public:
    Sensor(double signalPeriod, double samplingFrequency, int bufferLength, double reportPeriod);
    void generateSignal();
    void simulateEcho(double objectDistance, double objectSpeed, double propagationSpeed);
    void performCrossCorrelation();
    double calculateDistance();

private:
    double signalPeriod;
    double samplingFrequency;
    int bufferLength;
    double reportPeriod;
    std::vector<double> transmittedSignal;
    std::vector<double> receivedSignal;
    std::vector<double> crossCorrelation;
    double objectDistance;
    double objectSpeed;
    double propagationSpeed;
    int numSamples;
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_SENSOR_H
