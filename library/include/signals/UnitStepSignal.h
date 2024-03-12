#ifndef CYFROWEPRZETWARZANIESYGNALOW_UNITSTEPSIGNAL_H
#define CYFROWEPRZETWARZANIESYGNALOW_UNITSTEPSIGNAL_H
#include <ContinuousSignal.h>


class UnitStepSignal : public ContinuousSignal {
private:
    double stepTime;
public:
    UnitStepSignal(double amplitude, double startTime, double duration, double stepTime);
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_UNITSTEPSIGNAL_H
