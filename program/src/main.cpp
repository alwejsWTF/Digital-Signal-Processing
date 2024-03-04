#include <utils/SignalOperations.h>
#include "signals/SinusoidalSignal.h"
#include <iostream>

int main() {
    SinusoidalSignal sinSignal(2.0, 1.0, 0, 10);
    sinSignal.generate();
    std::cout << "Signal1" << std::endl;
    sinSignal.display();
    std::cout << "==============================" << std::endl;
    SinusoidalSignal sinSignal2(2.5, 3, 2, 10);
    sinSignal2.generate();
    std::cout << "Signal2" << std::endl;
    sinSignal2.display();
    std::cout << "==============================" << std::endl;
    std::cout << "Signal1 + Signal2" << std::endl;
    std::vector<double> data = SignalOperations::divide(sinSignal.getData(), sinSignal2.getData());
    for (const auto val : data) std::cout << val << std::endl;
    return 0;
}
