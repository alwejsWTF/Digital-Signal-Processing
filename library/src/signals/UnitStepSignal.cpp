#include "signals/UnitStepSignal.h"
#include <sstream>

UnitStepSignal::UnitStepSignal(double amplitude, double startTime, double duration, double stepTime)
: ContinuousSignal(amplitude, startTime, duration, [amplitude, stepTime](const double t) {
    if (t > stepTime) return amplitude;
    if (t == stepTime) return 0.5 * amplitude;
    return 0.0;
}), stepTime(stepTime) {}

std::string UnitStepSignal::getSignalName() {
    std::stringstream chain;
    chain << "Szum impulsowy";
    return chain.str();
}