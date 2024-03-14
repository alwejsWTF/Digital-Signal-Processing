#include "signals/RectangularSignal.h"
#include <cmath>
#include <sstream>

RectangularSignal::RectangularSignal(double amplitude, double term, double dutyCycle, double startTime, double duration)
: ContinuousSignal(amplitude, startTime, duration, [amplitude, term, dutyCycle, startTime](const double t) {
    return std::fmod(t - startTime, term) < dutyCycle * term? amplitude : 0;
}), term(term), dutyCycle(dutyCycle) {}

std::string RectangularSignal::getSignalName() {
    std::stringstream chain;
    chain << "Sygnal prostokatny";
    return chain.str();
}
