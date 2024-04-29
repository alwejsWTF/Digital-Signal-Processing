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

double RectangularSymmetricSignal::getTerm() const {
    return term;
}

double RectangularSymmetricSignal::getDutyCycle() const {
    return dutyCycle;
}

void RectangularSymmetricSignal::setTerm(double term) {
    RectangularSymmetricSignal::term = term;
}

void RectangularSymmetricSignal::setDutyCycle(double dutyCycle) {
    RectangularSymmetricSignal::dutyCycle = dutyCycle;
}
