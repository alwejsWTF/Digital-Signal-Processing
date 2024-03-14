#include <iostream>
#include <conio.h>

#include "utils/SignalOperations.h"
#include "utils/matplotlibcpp.h"
#include "allSignals.h"
#include "typedefs.h"

double getSamplingRate();
double getAmplitude();
double getStartTime();
double getDuration();
double getTerm();
double getDutyCycle();
double getProbability();
double getStepTime();
int getFirstSample();
int getStepSampleNumber();
SignalPtr createSignal(int chosen_signal);
int SignalAndNoiseChoice();
void saveSignal(const SignalPtr& signal);
SignalPtr loadSignal();
void plots(const std::vector<double>& data, const std::vector<double>& time, const std::string& name);
void results(const SignalPtr& signal);
void signalMenu(const SignalPtr& signal);
void signalAndNoiseInput(const SignalPtr& signal);
void operationMenu(const SignalPtr& signal, const SignalPtr& signal1);
void operationResult(const SignalPtr& signal);
void menu();
SignalPtr generateSignalAndNoise();

namespace plt = matplotlibcpp;

int main() {
    menu();
    return 0;
}

double getSamplingRate() {
    double samplingRate;
    std::cout << "Sampling rate: ";
    std::cin >> samplingRate;
    return samplingRate;
}

double getAmplitude() {
    double amplitude;
    std::cout << "Amplitude: ";
    std::cin >> amplitude;
    return amplitude;
}

double getStartTime() {
    double startTime;
    std::cout << "Start time (t_1): ";
    std::cin >> startTime;
    return startTime;
}

double getDuration() {
    double duration;
    std::cout << "Duration: ";
    std::cin >> duration;
    return duration;
}

double getTerm() {
    double term;
    std::cout << "Term: ";
    std::cin >> term;
    return term;
}

double getDutyCycle() {
    double dutyCycle;
    std::cout << "Duty cycle: ";
    std::cin >> dutyCycle;
    return dutyCycle;
}

double getProbability() {
    double probability;
    std::cout << "Probability: ";
    std::cin >> probability;
    return probability;
}

double getStepTime() {
    double stepTime;
    std::cout << "Step Time: ";
    std::cin >> stepTime;
    return stepTime;
}

int getFirstSample() {
    int firstSample;
    std::cout << "First Sample: ";
    std::cin >> firstSample;
    return firstSample;
}

int getStepSampleNumber() {
    int stepSampleNumber;
    std::cout << "Step sample number: ";
    std::cin >> stepSampleNumber;
    return stepSampleNumber;
}

SignalPtr createSignal(int chosen_signal) {
    SignalPtr signal;
    double duration;
    double term;
    if (chosen_signal >= 3 && chosen_signal <= 8) {
        double x = getDuration();
        term = getTerm();
        duration = x - fmod(x, term);
    }
    switch (chosen_signal) {
        case 1:
            signal = std::make_shared<UniformDistributionNoise>(getAmplitude(), getStartTime(), getDuration());
            break;
        case 2:
            signal = std::make_shared<GaussianNoise>(getAmplitude(), getStartTime(), getDuration());
            break;
        case 3:
            signal = std::make_shared<SinusoidalSignal>(getAmplitude(), term, getStartTime(), duration);
            break;
        case 4:
            signal = std::make_shared<SinusoidalHalfRectifiedSignal>(getAmplitude(), term, getStartTime(), duration);
            break;
        case 5:
            signal = std::make_shared<SinusoidalFullRectifiedSignal>(getAmplitude(), term, getStartTime(), duration);
            break;
        case 6:
            signal = std::make_shared<RectangularSignal>(getAmplitude(), term, getDutyCycle(), getStartTime(), duration);
            break;
        case 7:
            signal = std::make_shared<RectangularSymmetricSignal>(getAmplitude(), term, getDutyCycle(), getStartTime(), duration);
            break;
        case 8:
            signal = std::make_shared<TriangularSignal>(getAmplitude(), term, getDutyCycle(), getStartTime(), duration);
            break;
        case 9:
            signal = std::make_shared<UnitStepSignal>(getAmplitude(), getStartTime(), getDuration(), getStepTime());
            break;
        case 10:
            signal = std::make_shared<UnitImpulseSignal>(getAmplitude(), getStartTime(), getDuration(), getStepSampleNumber(), getFirstSample());
            break;
        case 11:
            signal = std::make_shared<ImpulseNoise>(getAmplitude(), getStartTime(), getDuration(), getProbability());
            break;
        default:
            std::cout << "Invalid choice.\n";
            break;
    }
    return signal;
}

int SignalAndNoiseChoice() {
    int chosen_signal = 0;
    while (11 < chosen_signal || chosen_signal < 1 ) {
        std::cout << "======SIGNAL AND NOISE======:\n"
                  << "1. Uniform distribution noise\n"
                  << "2. Gaussian noise\n"
                  << "3. Sinusoidal signal\n"
                  << "4. Sinusoidal half rectified signal\n"
                  << "5. Sinusoidal full rectified signal\n"
                  << "6. Rectangular signal\n"
                  << "7. Rectangular symmetric signal\n"
                  << "8. Triangular signal\n"
                  << "9. Unit step signal\n"
                  << "10. Unit impulse signal\n"
                  << "11. Impulse noise\n"
                  << "Choice: ";
        std::cin >> chosen_signal;
    }
    return chosen_signal;
}

SignalPtr generateSignalAndNoise() {
    int chosen_signal = SignalAndNoiseChoice();
    SignalPtr signal = createSignal(chosen_signal);
    double samplingRate = getSamplingRate();
    signal->generate(samplingRate);
    return signal;
}

void openSignalMenu() {
    signalMenu(generateSignalAndNoise());
}

void saveSignal(const SignalPtr& signal) {
    std::cout << "save implementation\n";
}

SignalPtr loadSignal() {
    std::cout << "load implementation\n";
    SignalPtr signal;
    return signal;
}

void plots(const std::vector<double>& data, const std::vector<double>& time, const std::string& name) {
    int choice = 0;
    while (choice != 4) {
        std::cout << "======PLOTS======\n"
                  << "1. Graph A from t (without lines).\n"
                  << "2. Graph A from t (with lines).\n"
                  << "3. Histogram\n"
                  << "4. Return.\n"
                  << "Choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                plt::scatter(time, data, 30,
                             {{"marker", "x"}, {"c", "orangered"}});
                plt::title(name);
                plt::grid(true);
                plt::xlabel("t [s]");
                plt::ylabel("A", {{"rotation", "horizontal"}});
                plt::show();
                plt::close();
                break;
            case 2:
                plt::plot(time,data,
                          {{"marker", "x"},{"mec", "orangered"}, {"color", "mediumspringgreen"} });
                plt::title(name);
                plt::grid(true);
                plt::xlabel("t [s]");
                plt::ylabel("A", {{"rotation", "horizontal"}});
                plt::show();
                plt::close();
                break;
            case 3:
                plt::hist(data, 20);
                plt::title(name);
                plt::grid(true);
                plt::xlabel("A");
                plt::ylabel("n", {{"rotation", "horizontal"}});
                plt::show();
                plt::close();
                break;
            case 4:
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }
}

void results(const SignalPtr& signal) {
    std::cout << "======RESULT======\n"
              << "Amplituda: " << signal->getMaxAmplitude() << std::endl
              << "Wartosc srednia: " << signal->meanValue() << std::endl
              << "Wartosc srednia bezwzgledna: " << signal->meanAbsoluteValue() << std::endl
              << "Moc srednia: " << signal->meanPower() << std::endl
              << "Wariancja: " << signal->variance() << std::endl
              << "Wartosc skuteczna: " << signal->rootMeanSquare() << std::endl
              << "Press any key to continue...\n";
    _getch();
    std::cout << signal->display();
    _getch();
}

void signalMenu(const SignalPtr& signal) {
    int choice = 0;
    while (choice != 5) {
        std::cout << "======SIGNAL MENU======\n"
                  << "1. Write to binary file.\n"
                  << "2. Show plots.\n"
                  << "3. Show results.\n"
                  << "4. Make oparations on signals.\n"
                  << "5. Return.\n"
                  << "Choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                saveSignal(signal);
                break;
            case 2:
                plots(signal->getData(), signal->getTime(), signal->getSignalName());
                break;
            case 3:
                results(signal);
                break;
            case 4:
                signalAndNoiseInput(signal);
                break;
            case 5:
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }
}

void signalAndNoiseInput(const SignalPtr& signal) {
    int choice_main = 0;
    SignalPtr signal1;
    while (choice_main != 3) {
        std::cout << "======SIGNAL AND NOISE INPUT======\n"
                  << "1. Load from binary file.\n"
                  << "2. Generate.\n"
                  << "3. Return.\n"
                  << "Choice: ";
        std::cin >> choice_main;
        switch (choice_main) {
            case 1:
                signal1 = loadSignal();
                operationMenu(signal, signal1);
                break;
            case 2:
                signal1 = generateSignalAndNoise();
                operationMenu(signal, signal1);
                break;
            case 3:
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;

        }
    }
}

void operationMenu(const SignalPtr& signal, const SignalPtr& signal1) {
    int choice = 0;
    std::vector<double> data;
    SignalPtr result;
    while (choice != 5) {
        std::cout << "======OPERATION MENU======\n"
                  << "1. Addition.\n"
                  << "2. Subtraction.\n"
                  << "3. Multiplication.\n"
                  << "4. Division.\n"
                  << "5. Return.\n"
                  << "Choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                data = SignalOperations::add(signal->getData(), signal1->getData());
                result = std::make_shared<Signal>(data, signal->getTime());
                operationResult(result);
                break;
            case 2:
                data = SignalOperations::subtract(signal->getData(), signal1->getData());
                result = std::make_shared<Signal>(data, signal->getTime());
                operationResult(result);
                break;
            case 3:
                data = SignalOperations::multiply(signal->getData(), signal1->getData());
                result = std::make_shared<Signal>(data, signal->getTime());
                operationResult(result);
                break;
            case 4:
                data = SignalOperations::divide(signal->getData(), signal1->getData());
                result = std::make_shared<Signal>(data, signal->getTime());
                operationResult(result);
                break;
            case 5:
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }
}

void operationResult(const SignalPtr& signal) {
    int choice = 0;
    while (choice != 4) {
        std::cout << "======OPERATION RESULT======\n"
                  << "1. Write to binary file.\n"
                  << "2. Show plots.\n"
                  << "3. Show results.\n"
                  << "4. Return.\n"
                  << "Choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                saveSignal(signal);
                break;
            case 2:
                plots(signal->getData(), signal->getTime(), signal->getSignalName());
                break;
            case 3:
                results(signal);
                break;
            case 4:
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }
}

void menu() {
    int choice = 0;
    while (choice != 3) {
        std::cout << "======MENU======\n"
                  << "1. Generate signal or noise.\n"
                  << "2. Read from binary file.\n"
                  << "3. Quit.\n"
                  << "Choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                openSignalMenu();
                break;
            case 2:
                loadSignal();
                break;
            case 3:
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }
}