#include "signals/RectangularSymmetricSignal.h"
#include <cmath>
#include <sstream>

RectangularSymmetricSignal::RectangularSymmetricSignal(double amplitude, double term, double dutyCycle, double startTime, double duration, double samplingRate)
: ContinuousSignal(amplitude, startTime, duration, samplingRate, [amplitude, term, dutyCycle, startTime](const double t) {
    return std::fmod((t - startTime), term) < dutyCycle * term ? amplitude : -amplitude;
}), term(term), dutyCycle(dutyCycle) {}

std::string RectangularSymmetricSignal::getSignalName() {
    std::stringstream chain;
    chain << "Sygnal prostokatny symetryczny";
    return chain.str();
}

std::string RectangularSymmetricSignal::getSignalType() {
    return "RectangularSymmetricSignal";
}

double RectangularSymmetricSignal::getTerm() const {
    return term;
}

double RectangularSymmetricSignal::getDutyCycle() const {
    return dutyCycle;
}
