#ifndef CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALHALFRECTIFIEDSIGNAL_H
#define CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALHALFRECTIFIEDSIGNAL_H

#include <ContinuousSignal.h>

class SinusoidalHalfRectifiedSignal : public ContinuousSignal {
private:
    double amplitude;
    double term;

public:
    SinusoidalHalfRectifiedSignal(double amplitude, double term, double startTime, double duration);
    ~SinusoidalHalfRectifiedSignal() override = default;

    void generate() override;

    double getAmplitude() const;
    double getTerm() const;

    void setAmplitude(double amplitude);
    void setTerm(double term);
};


#endif //CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALHALFRECTIFIEDSIGNAL_H
