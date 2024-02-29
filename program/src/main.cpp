#include <iostream>
#include "SinusoidalSignal.h"

int main() {
    SinusoidalSignal sinSignal(2.0, 1.0, 0, 10); // Amplitude, Frequency, Phase
    sinSignal.generate();
    sinSignal.display();
    return 0;
}
