#ifndef CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALSIGNAL_H
#define CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALSIGNAL_H


#include <vector>
#include "Signal.h"

class SinusoidalSignal : public Signal {
private:
    std::vector<double> data;
    double amplitude;
    double term;
    double startTime;
    double duration;
public:
    SinusoidalSignal(double amplitude, double term, double startTime, double duration);
    ~SinusoidalSignal() override = default;

    void generate() override;
    void display() const override;

    std::vector<double> getData() const;
    double getAmplitude() const;
    double getTerm() const;
    double getStartTime() const;
    double getDuration() const;

    void setData(const std::vector<double> &data);
    void setAmplitude(double amplitude);
    void setTerm(double term);
    void setStartTime(double startTime);
    void setDuration(double duration);

};

#endif //CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALSIGNAL_H
