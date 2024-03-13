#include <utils/SignalOperations.h>
#include "signals/SinusoidalSignal.h"
#include <iostream>
#include <signals/GaussianNoise.h>
#include <signals/ImpulseNoise.h>
#include <signals/RectangularSignal.h>
#include <signals/RectangularSymmetricSignal.h>
#include <signals/TriangularSignal.h>
#include <signals/UniformDistributionNoise.h>
#include <signals/UnitImpulseSignal.h>
#include <signals/UnitStepSignal.h>
#include <utils/matplotlibcpp.h>

namespace plt = matplotlibcpp;

int main() {
    // SinusoidalSignal sinSignal(2.0, 1.0, 0, 10);
    // sinSignal.generate();
    // std::cout << "Signal1" << std::endl;
    // sinSignal.display();
    // std::cout << "==============================" << std::endl;
    // SinusoidalSignal sinSignal2(2.5, 3, 2, 10);
    // sinSignal2.generate();
    // std::cout << "Signal2" << std::endl;
    // sinSignal2.display();
    // std::cout << "==============================" << std::endl;
    // std::cout << "Signal1 + Signal2" << std::endl;
    // std::vector<double> data = SignalOperations::divide(sinSignal.getData(), sinSignal2.getData());
    // for (const auto val : data) std::cout << val << std::endl;

    //TriangularSignal trSignal(-20, 0.4, 0.5, 8.8, 1.2);
    ImpulseNoise signal(5.0, 2.0, 1.0, 0.3);
    signal.generate(100);
    std::cout << "Amplituda: " << signal.getMaxAmplitude() << std::endl
    << "Wartosc srednia: " << signal.meanValue() << std::endl
    << "Wartosc srednia bezwzgledna: " << signal.meanAbsoluteValue() << std::endl
    << "Moc srednia: " << signal.meanPower() << std::endl
    << "Wariancja: " << signal.variance() << std::endl
    << "Wartosc skuteczna: " << signal.rootMeanSquare() << std::endl;
    //trSignal.display();
    // sygnaly ciagle
    // plt::plot(signal.getTime(),signal.getData(), {{"marker", "x"},
    //     {"mec", "orangered"}, {"color", "mediumspringgreen"} });
    // sygnaly dyskretne
    plt::scatter(signal.getTime(), signal.getData(), 30, {{"marker", "x"}, {"c", "orangered"}});
    plt::title("Sygnał");
    plt::xlabel("t [s]");
    plt::ylabel("A", {{"rotation", "horizontal"}});
    plt::grid(true);
    plt::show();
    plt::close();

    return 0;
}
