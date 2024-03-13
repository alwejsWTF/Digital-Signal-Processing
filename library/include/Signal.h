#ifndef CYFROWEPRZETWARZANIESYGNALOW_SIGNAL_H
#define CYFROWEPRZETWARZANIESYGNALOW_SIGNAL_H

#include <vector>
#include <functional>

class Signal {
protected:
    std::vector<double> data;
    std::vector<double> time;
    double amplitude;
    double startTime;
    double duration;
    std::function<double(double)> signalFunction;
public:
    Signal(double amplitude, double startTime, double duration, const std::function<double(double)> &func);
    virtual ~Signal() = default;

    virtual void generate(double samplingRate);
    virtual void display() const;

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

    double getMaxAmplitude();

    void setAmplitude(double amplitude);
    void setStartTime(double startTime);
    void setDuration(double duration);
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_SIGNAL_H
