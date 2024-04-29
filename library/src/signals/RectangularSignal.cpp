#include "signals/RectangularSignal.h"
#include <cmath>
#include <sstream>

RectangularSignal::RectangularSignal(double amplitude, double term, double dutyCycle, double startTime, double duration, double samplingRate)
: ContinuousSignal(amplitude, startTime, duration, samplingRate, [amplitude, term, dutyCycle, startTime](const double t) {
    return std::fmod(t - startTime, term) < dutyCycle * term? amplitude : 0;
}), term(term), dutyCycle(dutyCycle) {}

std::string RectangularSignal::getSignalName() {
    std::stringstream chain;
    chain << "Sygnal prostokatny";
    return chain.str();
}

double RectangularSignal::getTerm() const {
    return term;
}

double RectangularSignal::getDutyCycle() const {
    return dutyCycle;
}

void RectangularSignal::setTerm(double term) {
    RectangularSignal::term = term;
}

void RectangularSignal::setDutyCycle(double dutyCycle) {
    RectangularSignal::dutyCycle = dutyCycle;
}
