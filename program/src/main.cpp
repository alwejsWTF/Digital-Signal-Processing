#include <iostream>
#include <conio.h>
#include <utils/FileOperations.h>

#include "utils/SignalOperations.h"
#include "utils/matplotlibcpp.h"
#include "allSignals.h"
#include "typedefs.h"
#include "utils/Sampler.h"
#include "utils/Quantizer.h"
#include "utils/SignalReconstruction.h"
#include "utils/Measures.h"

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
std::string getFileName();
SignalPtr createSignal(int chosen_signal);
int signalChoice();
void saveSignal(const SignalPtr& signal);
SignalPtr loadSignal();
void showScatter(const std::vector<double>& data, const std::vector<double>& time, const std::string& name);
void showPlot(const std::vector<double>& data, const std::vector<double>& time, const std::string& name);
void showHistMenu(const std::vector<double>& data, const std::string& name);
void plots(const std::vector<double>& data, const std::vector<double>& time, const std::string& name);
void results(const SignalPtr& signal);
void signalData(const SignalPtr& signal);
void signalMenu(const SignalPtr& signal);
void secondarySignalMenu(const SignalPtr& signal);
void signalInput(const SignalPtr& signal);
void operationMenu(const SignalPtr& signal, const SignalPtr& signal1);
void operationResult(const SignalPtr& signal);
void menu();
SignalPtr generateSignal();

namespace plt = matplotlibcpp;

int main() {
    //menu();
    SignalPtr signal = std::make_shared<SinusoidalSignal>(1, 1, 0, 5, 5);
    signal->generate();
    //auto [sampled, sampledTimes] = Sampler::uniformSample(signal->getTime(), signal->getData(), 10);
    auto quantized = Quantizer::uniformQuantize(signal->getData(), 4);
    auto [reconstructed, reconstructedTimes] = SignalReconstruction::zeroOrderHold(quantized, signal->getTime());
    plt::figure(1);
    plt::plot(signal->getTime(),signal->getData(),
              {{"marker", "x"},{"mec", "orangered"}, {"color", "mediumspringgreen"} });
    plt::title(signal->getSignalName());
    plt::grid(true);
    plt::xlabel("t [s]");
    plt::ylabel("A", {{"rotation", "horizontal"}});

//    plt::figure(2);
//    plt::plot(sampledTimes,sampled,
//              {{"marker", "x"},{"mec", "orangered"}, {"color", "mediumspringgreen"} });
//    plt::title(signal->getSignalName() + " - próbkowanie");
//    plt::grid(true);
//    plt::xlabel("t [s]");
//    plt::ylabel("A", {{"rotation", "horizontal"}});

    plt::figure(3);
    plt::plot(signal->getTime(),quantized,
              {{"marker", "x"},{"mec", "orangered"}, {"color", "mediumspringgreen"} });
    plt::title(signal->getSignalName() + " - kwantyzacja");
    plt::grid(true);
    plt::xlabel("t [s]");
    plt::ylabel("A", {{"rotation", "horizontal"}});

    plt::figure(4);
    plt::plot(reconstructedTimes,reconstructed,
              {{"marker", "x"},{"mec", "orangered"}, {"color", "mediumspringgreen"} });
    plt::title(signal->getSignalName() + " - rekonstrukcja");
    plt::grid(true);
    plt::xlabel("t [s]");
    plt::ylabel("A", {{"rotation", "horizontal"}});

    double mse = Measures::meanSquaredError(signal->getData(), reconstructed);
    double snr = Measures::signalToNoiseRatio(signal->getData(), reconstructed);
    double psnr = Measures::peakSignalToNoiseRatio(signal->getData(), reconstructed);
    double md = Measures::maximumDifference(signal->getData(), reconstructed);

    std::cout << "MSE: " << mse << std::endl;
    std::cout << "SNR: " << snr << std::endl;
    std::cout << "PSNR: " << psnr << std::endl;
    std::cout << "MD: " << md << std::endl;

    SignalPtr signal2 = std::make_shared<SinusoidalSignal>(1, 0.01, 0, 10, 5);
    signal2->generate();

    plt::figure(5);
    plt::plot(signal2->getTime(),signal2->getData(),
              {{"marker", "x"},{"mec", "orangered"}, {"color", "mediumspringgreen"} });
    plt::title(signal->getSignalName() + " - aliasing");
    plt::grid(true);
    plt::xlabel("t [s]");
    plt::ylabel("A", {{"rotation", "horizontal"}});

    plt::show();
    plt::close();
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

std::string getFileName() {
    std::string fileName;
    std::cout << "Input file name: ";
    std::cin >> fileName;
    return fileName;
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
            signal = std::make_shared<UniformDistributionNoise>(getAmplitude(), getStartTime(), getDuration(), getSamplingRate());
            break;
        case 2:
            signal = std::make_shared<GaussianNoise>(getAmplitude(), getStartTime(), getDuration(), getSamplingRate());
            break;
        case 3:
            signal = std::make_shared<SinusoidalSignal>(getAmplitude(), term, getStartTime(), duration, getSamplingRate());
            break;
        case 4:
            signal = std::make_shared<SinusoidalHalfRectifiedSignal>(getAmplitude(), term, getStartTime(), duration, getSamplingRate());
            break;
        case 5:
            signal = std::make_shared<SinusoidalFullRectifiedSignal>(getAmplitude(), term, getStartTime(), duration, getSamplingRate());
            break;
        case 6:
            signal = std::make_shared<RectangularSignal>(getAmplitude(), term, getDutyCycle(), getStartTime(), duration, getSamplingRate());
            break;
        case 7:
            signal = std::make_shared<RectangularSymmetricSignal>(getAmplitude(), term, getDutyCycle(), getStartTime(), duration, getSamplingRate());
            break;
        case 8:
            signal = std::make_shared<TriangularSignal>(getAmplitude(), term, getDutyCycle(), getStartTime(), duration, getSamplingRate());
            break;
        case 9:
            signal = std::make_shared<UnitStepSignal>(getAmplitude(), getStartTime(), getDuration(), getSamplingRate(), getStepTime());
            break;
        case 10:
            signal = std::make_shared<UnitImpulseSignal>(getAmplitude(), getStartTime(), getDuration(), getSamplingRate(), getStepSampleNumber(), getFirstSample());
            break;
        case 11:
            signal = std::make_shared<ImpulseNoise>(getAmplitude(), getStartTime(), getDuration(), getSamplingRate(), getProbability());
            break;
        default:
            std::cout << "Invalid choice.\n";
            break;
    }
    return signal;
}

int signalChoice() {
    int chosen_signal = 0;
    while (11 < chosen_signal || chosen_signal < 1 ) {
        std::cout << "=================SIGNAL CHOICE=================\n"
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

SignalPtr generateSignal() {
    int chosen_signal = signalChoice();
    SignalPtr signal = createSignal(chosen_signal);
    signal->generate();
    return signal;
}

void openSignalMenu() {
    signalMenu(generateSignal());
}

void saveSignal(const SignalPtr& signal) {
    FileOperations::save(signal, getFileName());
}

SignalPtr loadSignal() {
    return FileOperations::load(getFileName());
}

void showScatter(const std::vector<double>& data, const std::vector<double>& time, const std::string& name){
    plt::scatter(time, data, 30,
                 {{"marker", "x"}, {"c", "orangered"}});
    plt::title(name);
    plt::grid(true);
    plt::xlabel("t [s]");
    plt::ylabel("A", {{"rotation", "horizontal"}});
}

void showPlot(const std::vector<double>& data, const std::vector<double>& time, const std::string& name) {
    plt::plot(time,data,
              {{"marker", "x"},{"mec", "orangered"}, {"color", "mediumspringgreen"} });
    plt::title(name);
    plt::grid(true);
    plt::xlabel("t [s]");
    plt::ylabel("A", {{"rotation", "horizontal"}});
}

void showHist(const std::vector<double>& data, const int number, const std::string& name) {
    plt::hist(data, number, "springgreen", "black", 0.9, false);
    plt::title(name);
    plt::grid(true);
    plt::xlabel("A");
    plt::ylabel("n", {{"rotation", "horizontal"}});
}

void showHistMenu(const std::vector<double>& data, const std::string& name) {
    int choice = 0;
    int number = 15;
    while (choice != 1 && choice != 2 && choice != 3) {
        std::cout << "Do you want to input bar number?\n"
                  << "1. Yes.\n"
                  << "2. No.\n"
                  << "3. Return.\n"
                  << "Choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                do {
                    std::cout << "Input bar number: ";
                    std::cin >> number;
                } while (number < 5 || number > 100);
                showHist(data, number, name);
                plt::show();
                plt::close();
                break;
            case 2:
                number = ceil(1 + 3.322 * log10(data.size()));
                showHist(data, number, name);
                plt::show();
                plt::close();
                break;
            case 3:
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }
}

void plots(const std::vector<double>& data, const std::vector<double>& time, const std::string& name) {
    int choice = 0;
    while (choice != 5) {
        std::cout << "=================PLOTS=================\n"
                  << "1. Graph A from t (without lines).\n"
                  << "2. Graph A from t (with lines).\n"
                  << "3. Histogram.\n"
                  << "4. Show all plots.\n"
                  << "5. Return.\n"
                  << "Choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                showScatter(data, time, name);
                plt::show();
                plt::close();
                break;
            case 2:
                showPlot(data, time, name);
                plt::show();
                plt::close();
                break;
            case 3:
                showHistMenu(data, name);
                break;
            case 4:
                plt::figure(1);
                showScatter(data, time, name);
                plt::figure(2);
                showPlot(data, time, name);
                plt::figure(3);
                showHistMenu(data, name);
                plt::close();
                break;
            case 5:
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }
}

void results(const SignalPtr& signal) {
    std::cout << "=================RESULT=================\n"
              << "Amplituda: " << signal->getMaxAmplitude() << std::endl
              << "Wartosc srednia: " << signal->meanValue() << std::endl
              << "Wartosc srednia bezwzgledna: " << signal->meanAbsoluteValue() << std::endl
              << "Moc srednia: " << signal->meanPower() << std::endl
              << "Wariancja: " << signal->variance() << std::endl
              << "Wartosc skuteczna: " << signal->rootMeanSquare() << std::endl
              << "Press any key to continue...\n";
    _getch();
}

void signalData(const SignalPtr& signal) {
    std::cout << "=================SIGNAL DATA=================\n"
              << signal->display()
              << "\nPress any key to continue...\n";
    _getch();
}

void signalMenu(const SignalPtr& signal) {
    int choice = 0;
    while (choice != 6) {
        std::cout << "=================SIGNAL MENU=================\n"
                  << "1. Write to binary file.\n"
                  << "2. Show plots.\n"
                  << "3. Show results.\n"
                  << "4. Show signal data.\n"
                  << "5. Make operations on signals.\n"
                  << "6. Return.\n"
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
                signalData(signal);
                break;
            case 5:
                signalInput(signal);
                break;
            case 6:
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }
}

void secondarySignalMenu(const SignalPtr& signal) {
    int choice = 0;
    while (choice != 5) {
        std::cout << "=================SECONDARY SIGNAL MENU=================\n"
                  << "1. Write to binary file.\n"
                  << "2. Show plots.\n"
                  << "3. Show results.\n"
                  << "4. Show signal data.\n"
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
                signalData(signal);
                break;
            case 5:
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }
}

void signalInput(const SignalPtr& signal) {
    int choice_main = 0;
    SignalPtr signal1;
    while (choice_main != 3) {
        std::cout << "=================SIGNAL INPUT=================\n"
                  << "1. Load from binary file.\n"
                  << "2. Generate.\n"
                  << "3. Return.\n"
                  << "Choice: ";
        std::cin >> choice_main;
        switch (choice_main) {
            case 1:
                signal1 = loadSignal();
                if (signal1 != nullptr){
                    secondarySignalMenu(signal1);
                    operationMenu(signal, signal1);
                }
                break;
            case 2:
                signal1 = generateSignal();
                secondarySignalMenu(signal1);
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
    int choiceSecondary = 0;
    std::vector<double> data;
    SignalPtr result;
    while (choice != 5) {
        std::cout << "=================OPERATION MENU=================\n"
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
                result = std::make_shared<Signal>(data, signal->getTime(), signal->getStartTime(), signal->getDuration(), signal->getSamplingRate());
                result->setAmplitude(result->getMaxAmplitude());
                operationResult(result);
                break;
            case 2:
                data = SignalOperations::subtract(signal->getData(), signal1->getData());
                result = std::make_shared<Signal>(data, signal->getTime(), signal->getStartTime(), signal->getDuration(), signal->getSamplingRate());
                result->setAmplitude(result->getMaxAmplitude());
                operationResult(result);
                break;
            case 3:
                data = SignalOperations::multiply(signal->getData(), signal1->getData());
                result = std::make_shared<Signal>(data, signal->getTime(), signal->getStartTime(), signal->getDuration(), signal->getSamplingRate());
                result->setAmplitude(result->getMaxAmplitude());
                operationResult(result);
                break;
            case 4:
                while (choiceSecondary != 1 && choiceSecondary != 2) {
                    std::cout << "Chose what division by 0 returns:\n"
                              << "1. 0.\n"
                              << "2. Nan.\n"
                              << "Choice: ";
                    std::cin >> choiceSecondary;
                }
                switch (choiceSecondary) {
                    case 1:
                    case 2:
                        data = SignalOperations::divide(signal->getData(), signal1->getData(), choiceSecondary);
                        break;
                }
                result = std::make_shared<Signal>(data, signal->getTime(), signal->getStartTime(), signal->getDuration(), signal->getSamplingRate());
                result->setAmplitude(result->getMaxAmplitude());
                operationResult(result);
                choiceSecondary = 0;
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
    while (choice != 5) {
        std::cout << "=================OPERATION RESULT=================\n"
                  << "1. Write to binary file.\n"
                  << "2. Show plots.\n"
                  << "3. Show results.\n"
                  << "4. Show signal data.\n"
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
                signalData(signal);
                break;
            case 5:
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }
}

void menu() {
    int choice = 0;
    SignalPtr signal;
    while (choice != 3) {
        std::cout << "=================MENU=================\n"
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
                signal = loadSignal();
                if (signal != nullptr)
                    signalMenu(signal);
                break;
            case 3:
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }
}