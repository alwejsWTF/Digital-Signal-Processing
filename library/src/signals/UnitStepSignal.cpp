#include "signals/UnitStepSignal.h"
#include <sstream>

UnitStepSignal::UnitStepSignal(double amplitude, double startTime, double duration, double samplingRate, double stepTime)
: ContinuousSignal(amplitude, startTime, duration, samplingRate, [amplitude, stepTime](const double t) {
    if (t > stepTime) return amplitude;
    if (t == stepTime) return 0.5 * amplitude;
    return 0.0;
}), stepTime(stepTime) {}

std::string UnitStepSignal::getSignalName() {
    std::stringstream chain;
    chain << "Skok jednostkowy";
    return chain.str();
}

std::string UnitStepSignal::getSignalType() {
    return "UnitStepSignal";
}

double UnitStepSignal::getStepTime() const {
    return stepTime;
}
