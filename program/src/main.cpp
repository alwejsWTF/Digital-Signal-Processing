#include <iostream>
#include "signals/SinusoidalSignal.h"

int main() {
    SinusoidalSignal sinSignal(2.0, 1.0, 0, 10);
    sinSignal.generate();
    sinSignal.display();
    return 0;
}
