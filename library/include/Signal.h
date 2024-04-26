#ifndef CYFROWEPRZETWARZANIESYGNALOW_SIGNAL_H
#define CYFROWEPRZETWARZANIESYGNALOW_SIGNAL_H

#include <vector>
#include <functional>
#include <string>

class Signal {
protected:
    std::vector<double> data;
    std::vector<double> time;
    double amplitude{};
    double startTime{};
    double duration{};
    double samplingRate{};
    std::function<double(double)> signalFunction;
public:
    Signal(double amplitude, double startTime, double duration, double samplingRate, const std::function<double(double)> &func);
    Signal(std::vector<double> data, std::vector<double> time, double startTime, double duration, double samplingRate);
    virtual ~Signal() = default;

    virtual void generate();
    virtual std::string display();
    virtual std::string getSignalName();

    double meanValue();
    double meanAbsoluteValue();
    double meanPower();
    double variance();
    double rootMeanSquare();

    std::vector<double> getData() const;
    std::vector<double> getTime() const;

    double getAmplitude() const;
    double getStartTime() const;
    double getDuration() const;
    double getSamplingRate() const;

    double getMaxAmplitude();

    void setData(std::vector<double> data);
    void setTime(std::vector<double> time);
    void setAmplitude(double amplitude);
    void setStartTime(double startTime);
    void setDuration(double duration);
    void setSamplingRate(double samplingRate);
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_SIGNAL_H
