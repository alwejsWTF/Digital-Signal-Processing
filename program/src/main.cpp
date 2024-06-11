#include <iostream>
#include <conio.h>
#include <chrono>

#include <utils/FileOperations.h>
#include "utils/SignalOperations.h"
#include "utils/matplotlibcpp.h"
#include "allSignals.h"
#include "signals/Quantizer.h"
#include "signals/SignalReconstruction.h"
#include "utils/Measures.h"
#include "utils/crossCorrelation.h"
#include "utils/filters.h"
#include "utils/sensor.h"
#include "utils/convolution.h"
#include "utils/TransformUtilities.h"
#include "transforms/FourierTransform.h"
#include "transforms/CosineTransform.h"
#include "transforms/HadamardTransform.h"

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
SignalPtr generateSignal();
SignalPtr copySignal(const SignalPtr &signal, nlohmann::json json);
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
void quantizationMenu(const SignalPtr& signal);
void quantizationPlotMenu(const SignalPtr &quantizedSignal, const SignalPtr &originalSignal);
void compareQuanSignals(const SignalPtr &quantizedSignal, const SignalPtr &originalSignal,
                        const SignalPtr &originalLine);
std::pair<std::vector<double>, std::vector<double>> fakeZOH(const std::vector<double> data,
                                                            const std::vector<double> time);
void reconstructionMenu(const SignalPtr& signal);
void reconstructionPlotMenu (const SignalPtr& signal, const SignalPtr& reconstructedSignal,
                             const SignalPtr& reconstructedSignalLine, int choosenSignalRecon);
void compareRecoSignals(const SignalPtr &reconstructedSignal, const SignalPtr &originalSignal,
                        const SignalPtr &reconstructedSignalLine, int choice);
void showQuanRecoResults(const SignalPtr &resultSignal, const SignalPtr &originalSignal);
void aliasingMenu(const SignalPtr &originalSignal);
void plotTwoSignals(const SignalPtr &originalSignal, const SignalPtr &aliasedSignal);
void plotTwoSignalsWithLines(const SignalPtr &originalSignal, const SignalPtr &aliasedSignal);
void plotTwoSignalsBothWithBetterLines(const SignalPtr &originalSignal, const SignalPtr &aliasedSignal,
                                       const SignalPtr &originalLines, const SignalPtr &aliasedLines);
void plotConvolution(const std::vector<double> &data1, const std::vector<double> &time1,
                     const std::vector<double> &data2, const std::vector<double> &time2,
                     const std::vector<double> &data3, const std::vector<double> &time3, const std::string& name);
void plotFilters(const std::vector<double> &data1, const std::vector<double> &time1,
                 const std::vector<double> &data2, const std::vector<double> &time2,
                 const std::vector<double> &data3, const std::vector<double> &time3, const std::string& name);
std::pair<std::vector<double>, std::vector<double>>filterSignal(const SignalPtr& signal,
                                                                const std::vector<double>& filter);
void plotSensor(const std::vector<double> &transmittedSignal, const std::vector<double> &transmittedSignalTime,
                const std::vector<double> &receivedSignal, const std::vector<double> &receivedSignalTime,
                const std::vector<double> &crossCorrelation, const std::vector<double> &crossCorrelationTime);
void filterSignalMenu(const SignalPtr& signal);
void sensorSignalMenu(const SignalPtr& signal);
void transformSignal(const SignalPtr& signal);
void plotTransform(const std::vector<std::complex<double>>& transform, const std::string& title, bool mode, double duration);
void menu();

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
    double term = 0;
    while (term == 0) {
        std::cout << "Term: ";
        std::cin >> term;
    }
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

SignalPtr copySignal(const SignalPtr &signal, nlohmann::json json) {
    SignalPtr newSignal;
    if (json.contains("name")) {
        if (json["name"] == "Szum o rozkladzie jednostajnym") {
            auto tmpSignal = std::dynamic_pointer_cast<UniformDistributionNoise>(signal);
            newSignal = std::make_shared<UniformDistributionNoise>(signal->getAmplitude(), signal->getStartTime(), signal->getDuration(), signal->getSamplingRate());
        } else if (json["name"] == "Szum gaussowski") {
            auto tmpSignal = std::dynamic_pointer_cast<GaussianNoise>(signal);
            newSignal = std::make_shared<GaussianNoise>(signal->getAmplitude(), signal->getStartTime(), signal->getDuration(), signal->getSamplingRate());
        } else if (json["name"] == "Sygnal sinusoidalny") {
            auto tmpSignal = std::dynamic_pointer_cast<SinusoidalSignal>(signal);
            if (json.contains("term")) {
                if (json["term"] != NULL)
                    newSignal = std::make_shared<SinusoidalSignal>(signal->getAmplitude(), json["term"], signal->getStartTime(), signal->getDuration(), signal->getSamplingRate());
            } else
                newSignal = std::make_shared<SinusoidalSignal>(signal->getAmplitude(), tmpSignal->getTerm(), signal->getStartTime(), signal->getDuration(), signal->getSamplingRate());
        } else if (json["name"] == "Sygnal sinusoidalny wyprostowany jednopolowkowo") {
            auto tmpSignal = std::dynamic_pointer_cast<SinusoidalHalfRectifiedSignal>(signal);
            if (json.contains("term")) {
                if (json["term"] != NULL)
                    newSignal = std::make_shared<SinusoidalHalfRectifiedSignal>(signal->getAmplitude(), json["term"], tmpSignal->getStartTime(), signal->getDuration(), signal->getSamplingRate());
            } else
                newSignal = std::make_shared<SinusoidalHalfRectifiedSignal>(signal->getAmplitude(), tmpSignal->getTerm(), tmpSignal->getStartTime(), signal->getDuration(), signal->getSamplingRate());
        } else if (json["name"] == "Sygnal sinusoidalny wyprostowany dwupolowkowo") {
            auto tmpSignal = std::dynamic_pointer_cast<SinusoidalFullRectifiedSignal>(signal);
            if (json.contains("term")) {
                if (json["term"] != NULL)
                    newSignal = std::make_shared<SinusoidalFullRectifiedSignal>(signal->getAmplitude(), json["term"], tmpSignal->getStartTime(), signal->getDuration(), signal->getSamplingRate());
            } else
                newSignal = std::make_shared<SinusoidalFullRectifiedSignal>(signal->getAmplitude(), tmpSignal->getTerm(), tmpSignal->getStartTime(), signal->getDuration(), signal->getSamplingRate());
        } else if (json["name"] == "Sygnal prostokatny") {
            auto tmpSignal = std::dynamic_pointer_cast<RectangularSignal>(signal);
            if (json.contains("term") && json.contains("dutyCycle")) {
                if (json["term"] != NULL && json["dutyCycle"] != NULL)
                    newSignal = std::make_shared<RectangularSignal>(signal->getAmplitude(), json["term"], json["dutyCycle"], signal->getStartTime(), signal->getDuration(), signal->getSamplingRate());
            } else
                newSignal = std::make_shared<RectangularSignal>(signal->getAmplitude(), tmpSignal->getTerm(), tmpSignal->getDutyCycle(), signal->getStartTime(), signal->getDuration(), signal->getSamplingRate());
        } else if (json["name"] == "Sygnal prostokatny symetryczny") {
            auto tmpSignal = std::dynamic_pointer_cast<RectangularSymmetricSignal>(signal);
            if (json.contains("term") && json.contains("dutyCycle")) {
                if (json["term"] != NULL && json["dutyCycle"] != NULL)
                    newSignal = std::make_shared<RectangularSymmetricSignal>(signal->getAmplitude(), json["term"], json["dutyCycle"], signal->getStartTime(), signal->getDuration(), signal->getSamplingRate());
            } else
            newSignal = std::make_shared<RectangularSymmetricSignal>(signal->getAmplitude(), tmpSignal->getTerm(), tmpSignal->getDutyCycle(), signal->getStartTime(), signal->getDuration(), signal->getSamplingRate());
        } else if (json["name"] == "Sygnal trojkatny") {
            auto tmpSignal = std::dynamic_pointer_cast<TriangularSignal>(signal);
            if (json.contains("term") && json.contains("dutyCycle")) {
                if (json["term"] != NULL && json["dutyCycle"] != NULL)
                    newSignal = std::make_shared<TriangularSignal>(signal->getAmplitude(), json["term"], json["dutyCycle"], signal->getStartTime(), signal->getDuration(), signal->getSamplingRate());
            } else
            newSignal = std::make_shared<TriangularSignal>(signal->getAmplitude(), tmpSignal->getTerm(), tmpSignal->getDutyCycle(), signal->getStartTime(), signal->getDuration(), signal->getSamplingRate());
        } else if (json["name"] == "Skok jednostkowy") {
            auto tmpSignal = std::dynamic_pointer_cast<UnitStepSignal>(signal);
            if (json.contains("stepTime")) {
                if (json["stepTime"] != NULL)
                    newSignal = std::make_shared<UnitStepSignal>(signal->getAmplitude(), signal->getStartTime(), signal->getDuration(), signal->getSamplingRate(), json["stepTime"]);
            } else
                newSignal = std::make_shared<UnitStepSignal>(signal->getAmplitude(), signal->getStartTime(), signal->getDuration(), signal->getSamplingRate(), tmpSignal->getStepTime());
        } else if (json["name"] == "Impuls jednostkowy") {
            auto tmpSignal = std::dynamic_pointer_cast<UnitImpulseSignal>(signal);
            if (json.contains("stepSampleNumber") && json.contains("firstSample")) {
                if (json["stepSampleNumber"] != NULL && json["firstSample"] != NULL)
                newSignal = std::make_shared<UnitImpulseSignal>(signal->getAmplitude(), signal->getStartTime(), signal->getDuration(), signal->getSamplingRate(), json["stepSampleNumber"], json["firstSample"]);
            } else
                newSignal = std::make_shared<UnitImpulseSignal>(signal->getAmplitude(), signal->getStartTime(), signal->getDuration(), signal->getSamplingRate(), tmpSignal->getStepSampleNumber(), tmpSignal->getFirstSample());
        } else if (json["name"] == "Szum impulsowy") {
            auto tmpSignal = std::dynamic_pointer_cast<ImpulseNoise>(signal);
            if (json.contains("probability")) {
                if (json["probability"] != NULL)
                    newSignal = std::make_shared<ImpulseNoise>(signal->getAmplitude(), signal->getStartTime(), signal->getDuration(), signal->getSamplingRate(), json["probability"]);
            } else
                newSignal = std::make_shared<ImpulseNoise>(signal->getAmplitude(), signal->getStartTime(), signal->getDuration(), signal->getSamplingRate(), tmpSignal->getProbability());
        } else {
            std::cout << "Wrong signal name.";
        }
    } else {
        std::cout << "No signal name.";
    }
    newSignal->setData(signal->getData());
    newSignal->setTime(signal->getTime());
    return newSignal;
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
    SignalPtr loadedSignal;
    nlohmann::json j = nlohmann::json::object();
    std::tie(loadedSignal, j) = FileOperations::load(getFileName());
    SignalPtr newSignal = copySignal(loadedSignal, j);
    return newSignal;
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
    while (choice != 12) {
        std::cout << "=================SIGNAL MENU=================\n"
                  << "1. Write to binary file.\n"
                  << "2. Show plots.\n"
                  << "3. Show results.\n"
                  << "4. Show signal data.\n"
                  << "5. Make operations on signals.\n"
                  << "6. Quantize signal.\n"
                  << "7. Reconstruct signal.\n"
                  << "8. Aliasing.\n"
                  << "9. Filter signal.\n"
                  << "10. Sensor signal.\n"
                  << "11. Transform.\n"
                  << "12. Return.\n"
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
                quantizationMenu(signal);
                break;
            case 7:
                reconstructionMenu(signal);
                break;
            case 8:
                aliasingMenu(signal);
                break;
            case 9:
                filterSignalMenu(signal);
                break;
            case 10:
                sensorSignalMenu(signal);
                choice = 0;
                break;
            case 11:
                transformSignal(signal);
                choice = 0;
                break;
            case 12:
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }
}

void filterSignalMenu(const SignalPtr& signal) {
    int numCoeffs = 0;
    double cutoffFreq = 0;
    int windowChoice = 0;
    WindowType windowType;
    int filterChoice = 0;
    FilterType filterType;
    while (windowChoice < 1 || windowChoice > 4) {
        std::cout << "=================FILTER SIGNAL MENU=================\n"
                  << "Choose window.\n"
                  << "1. RECTANGULAR\n"
                  << "2. HAMMING\n"
                  << "3. HANNING\n"
                  << "4. BLACKMAN\n"
                  << "Choice: ";
        std::cin >> windowChoice;
    }
    while (filterChoice != 1 && filterChoice !=2) {
        std::cout << "Choose filter type.\n"
                  << "1. LOW_PASS\n"
                  << "2. HIGH_PASS\n"
                  << "Choice: ";
        std::cin >> filterChoice;
    }
    while (numCoeffs <= 0) {
        std::cout << "Input number of coefficients:";
        std::cin >> numCoeffs;
    }
    while (cutoffFreq <= 0) {
        std::cout << "Input frequency cutoff:";
        std::cin >> cutoffFreq;
    }
    switch (windowChoice) {
        case 1:
            windowType = RECTANGULAR;
            break;
        case 2:
            windowType = HAMMING;
            break;
        case 3:
            windowType = HANNING;
            break;
        case 4:
            windowType = BLACKMAN;
            break;
        default:
            break;
    }
    switch (filterChoice) {
        case 1:
            filterType = LOW_PASS;
            break;
        case 2:
            filterType = HIGH_PASS;
            break;
        default:
            break;
    }
    std::vector<double> filterData;
    std::vector<double> filterTimes;
    std::tie(filterData, filterTimes) = designFilter(numCoeffs, signal->getSamplingRate(), cutoffFreq, windowType, filterType);
    std::vector<double> data;
    std::vector<double> time;
    std::tie(data, time) = filterSignal(signal, filterData);
    plotFilters(data, time, filterData, filterTimes,
                    signal->getData(), signal->getTime(), "signal filtration");
}

std::pair<std::vector<double>, std::vector<double>>filterSignal(const SignalPtr& signal,
                                                                const std::vector<double>& filter) {
    return discreteConvolution(signal->getData(), 1.0 / signal->getSamplingRate(),
                               filter, 1.0 / signal->getSamplingRate());
}


void plotFilters(const std::vector<double> &data1, const std::vector<double> &time1,
                     const std::vector<double> &data2, const std::vector<double> &time2,
                     const std::vector<double> &data3, const std::vector<double> &time3, const std::string& name) {
    plt::scatter(time3, data3,
                 25.0,
                 { {"marker", "o"}, {"color", "mediumspringgreen"} });
    plt::title("Before " + name);
    plt::grid(true);
    plt::xlabel("t [s]");
    plt::ylabel("A", {{"rotation", "horizontal"}});
    plt::show();

    plt::scatter(time2, data2,
                 25.0,
                 { {"marker", "x"}, {"color", "orchid"} });
    plt::title("Signal filter");
    plt::grid(true);
    plt::xlabel("t [s]");
    plt::ylabel("A", {{"rotation", "horizontal"}});
    plt::show();
    plt::scatter(time1, data1,
                 25.0,
                 { {"marker", "x"}, {"color", "midnightblue"} });
    plt::title("After " + name);
    plt::grid(true);
    plt::xlabel("t [s]");
    plt::ylabel("A", {{"rotation", "horizontal"}});
    plt::show();
    plt::close();
}


void transformSignal(const SignalPtr& signal) {
//    double fs = 16.0;
//    double duration = 8.0;
//    std::vector<double> signal1 = TransformUtilities::generateSignal1(duration, fs);

    std::vector<std::complex<double>> x(signal->getData().size());
    for (size_t i = 0; i < signal->getData().size(); ++i) {
        x[i] = std::complex<double>(signal->getData()[i], 0.0);
    }
    std::vector<std::complex<double>> transformedSignal;
    auto start = std::chrono::high_resolution_clock::now();
    auto stop = std::chrono::high_resolution_clock::now();
    int choice = 0;
    std::string title;
    while (choice != 6) {
        std::cout << "=================TRANSFORM SIGNAL MENU=================\n"
                     "1. DFT\n"
                     "2. DCT II\n"
                     "3. Walsh-Hadamard\n"
                     "4. DIT FFT\n"
                     "5. DIF FFT\n"
                     "6. Return\n"
                     "Choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                start = std::chrono::high_resolution_clock::now();
                transformedSignal = FourierTransform::computeDFT(signal->getData());
                stop = std::chrono::high_resolution_clock::now();
                title = "Discrete Fourier Transform";
                break;
            case 2:
                start = std::chrono::high_resolution_clock::now();
                transformedSignal = CosineTransform::computeDCT(signal->getData());
                stop = std::chrono::high_resolution_clock::now();
                title = "Discrete Cosine Transform";
                break;
            case 3:
                start = std::chrono::high_resolution_clock::now();
                transformedSignal = HadamardTransform::computeHadamard(signal->getData());
                stop = std::chrono::high_resolution_clock::now();
                title = "Walsh-Hadamard Transform";
                break;
            case 4:
                start = std::chrono::high_resolution_clock::now();
                transformedSignal = FourierTransform::computeDITFFT(x);
                stop = std::chrono::high_resolution_clock::now();
                title = "Decimation-In-Time Fast Fourier Transform";
                break;
            case 5:
                start = std::chrono::high_resolution_clock::now();
                transformedSignal = FourierTransform::computeDIFFFT(x);
                stop = std::chrono::high_resolution_clock::now();
                title = "Decimation-In-Frequency Fast Fourier Transform(☞ﾟヮﾟ)☞";
                break;
            default:
                break;
        }
        auto execution_time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Time taken by function: " << execution_time.count() << " microseconds" << std::endl;
        plt::plot(signal->getTime(), signal->getData(), {{"marker", "x"},{"mec", "orangered"}, {"color", "mediumspringgreen"} });
        plt::title( "Original Signal");
        plt::grid(true);
        plt::xlabel("t [s]");
        plt::ylabel("A");
        plt::show();

        plotTransform(transformedSignal, title, false, signal->getDuration());
        plotTransform(transformedSignal, title, true, signal->getDuration());
    }
}

void plotTransform(const std::vector<std::complex<double>>& transform, const std::string& title, bool mode, double duration) {
    std::vector<double> freq(transform.size());
    std::vector<double> upper(transform.size()), lower(transform.size());

    for (int i = 0; i < transform.size(); ++i) {
        freq[i] = i / duration;
        if (mode) {
            upper[i] = std::abs(transform[i]);
            lower[i] = std::arg(transform[i]);
        } else {
            upper[i] = transform[i].real();
            lower[i] = transform[i].imag();
        }
    }

    plt::figure_size(1200, 600);
    plt::suptitle(title);
    plt::subplot(2, 1, 1);
    plt::grid(true);
    plt::plot(freq, upper, {{"marker", "."},{"mec", "orangered"}, {"color", "mediumspringgreen"} });
    plt::xlabel("Frequency");
    plt::ylabel(mode ? "Module" : "Real");

    plt::subplot(2, 1, 2);
    plt::grid(true);
    plt::plot(freq, lower, {{"marker", "."},{"mec", "orangered"}, {"color", "mediumspringgreen"} });
    plt::xlabel("Frequency");
    plt::ylabel(mode ? "Argument" : "Imaginary");

    plt::show();
}


void sensorSignalMenu(const SignalPtr& signal) {
    double propagationSpeed = 340; // Prędkość dźwięku w powietrzu (m/s)
    double objectDistance = 12; // Odległość obiektu (m)
    double objectSpeed = 0; // Prędkość obiektu (m/s)
    std::cout << "=================SENSOR SIGNAL MENU=================\n"
              << "Input propagation speed: ";
    std::cin >> propagationSpeed;
    std::cout << "Input object distance: ";
    std::cin >> objectDistance;
    std::cout << "Input object speed: ";
    std::cin >> objectSpeed;
    Sensor sensor(signal, 1, propagationSpeed);
    double calculatedDistance = sensor.simulateEchoAndCalculateDistance(objectDistance, objectSpeed);
    std::vector<double> transmittedSignal = sensor.getTransmitted();
    std::vector<double> transmittedSignalTime = sensor.getTimeVector();
    std::vector<double> receivedSignal = sensor.getReceived();
    std::vector<double> receivedSignalTime = sensor.getTimeVector();
    std::vector<double> crossCorrelation = sensor.getCrossCorrelationPlot();
    std::vector<double> crossCorrelationTime = sensor.getTimeVectorCrossPlot();
//    std::vector<double> crossCorrelation = sensor.getCrossCorrelation();
//    std::vector<double> crossCorrelationTime = sensor.getTimeVectorCross();
    std::cout << "Real distance to object: " << objectDistance << " m" << std::endl;
    std::cout << "Calculated distance to object: " << calculatedDistance << " m" << std::endl;
    std::cout << "Press any key to continue...\n";
    _getch();
    plotSensor(transmittedSignal, transmittedSignalTime, receivedSignal, receivedSignalTime, crossCorrelation, crossCorrelationTime);
}

void plotSensor(const std::vector<double> &transmittedSignal, const std::vector<double> &transmittedSignalTime,
                 const std::vector<double> &receivedSignal, const std::vector<double> &receivedSignalTime,
                 const std::vector<double> &crossCorrelation, const std::vector<double> &crossCorrelationTime) {
    plt::scatter(transmittedSignalTime, transmittedSignal,
                 15.0,
                 { {"marker", "x"}, {"color", "midnightblue"} });
    plt::title("Transmitted signal");
    plt::grid(true);
    plt::xlabel("t [s]");
    plt::ylabel("A", {{"rotation", "horizontal"}});
    plt::show();

    plt::scatter(receivedSignalTime, receivedSignal,
                 15.0,
                 { {"marker", "x"}, {"color", "midnightblue"} });
    plt::title("Received signal");
    plt::grid(true);
    plt::xlabel("t [s]");
    plt::ylabel("A", {{"rotation", "horizontal"}});
    plt::show();
    plt::scatter(crossCorrelationTime, crossCorrelation,
                 15.0,
                 { {"marker", "x"}, {"color", "midnightblue"} });
    plt::title("Cross correlated signal");
    plt::grid(true);
    plt::xlabel("t [s]");
    plt::ylabel("A", {{"rotation", "horizontal"}});
    plt::show();
    plt::close();
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
    std::vector<double> points;
    std::vector<double> timeVector;
    SignalPtr result;
    nlohmann::json j = nlohmann::json::object();
    j["name"] = signal->getSignalName();
    while (choice != 7) {
        std::cout << "=================OPERATION MENU=================\n"
                  << "1. Addition.\n"
                  << "2. Subtraction.\n"
                  << "3. Multiplication.\n"
                  << "4. Division.\n"
                  << "5. Discrete convolution.\n"
                  << "6. Correlation.\n"
                  << "7. Return.\n"
                  << "Choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                result = copySignal(signal, j);
                data = SignalOperations::add(signal->getData(), signal1->getData());
                result->setData(data);
                operationResult(result);
                break;
            case 2:
                result = copySignal(signal, j);
                data = SignalOperations::subtract(signal->getData(), signal1->getData());
                result->setData(data);
                operationResult(result);
                break;
            case 3:
                result = copySignal(signal, j);
                data = SignalOperations::multiply(signal->getData(), signal1->getData());
                result->setData(data);
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
                data = SignalOperations::divide(signal->getData(), signal1->getData(), choiceSecondary);
                result = copySignal(signal, j);
                result->setData(data);
                operationResult(result);
                choiceSecondary = 0;
                break;
            case 5:
                std::tie(points, timeVector) = discreteConvolution(signal->getData(), 1.0 / signal->getSamplingRate(),
                                                                signal1->getData(), 1.0 / signal1->getSamplingRate());
                plotConvolution(points, timeVector, signal->getData(), signal->getTime(),
                                signal1->getData(), signal1->getTime(), "discrete convolution");
                result = copySignal(signal, j);
                result->setData(points);
                result->setTime(timeVector);
                operationResult(result);
                break;
            case 6:
                std::tie(points, timeVector) = directCrossCorrelation(signal->getData(), 1.0 / signal->getSamplingRate(),
                                                                   signal1->getData(), 1.0 / signal1->getSamplingRate());
                plotConvolution(points, timeVector, signal->getData(), signal->getTime(),
                                signal1->getData(), signal1->getTime(), "correlation");
                result = copySignal(signal, j);
                result->setData(points);
                result->setTime(timeVector);
                operationResult(result);
                break;
            case 7:
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }
}

void plotConvolution(const std::vector<double> &data1, const std::vector<double> &time1,
                     const std::vector<double> &data2, const std::vector<double> &time2,
                     const std::vector<double> &data3, const std::vector<double> &time3, const std::string& name) {
    plt::scatter(time3, data3,
                 25.0,
                 { {"marker", "o"}, {"color", "mediumspringgreen"} });
    plt::scatter(time2, data2,
                 25.0,
                 { {"marker", "x"}, {"color", "orchid"} });
    plt::title("Before " + name);
    plt::grid(true);
    plt::xlabel("t [s]");
    plt::ylabel("A", {{"rotation", "horizontal"}});
    plt::show();
    plt::scatter(time1, data1,
                 15.0,
                 { {"marker", "x"}, {"color", "midnightblue"} });
    plt::title("After " + name);
    plt::grid(true);
    plt::xlabel("t [s]");
    plt::ylabel("A", {{"rotation", "horizontal"}});
    plt::show();
    plt::close();
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

void quantizationMenu(const SignalPtr& signal) {
    int level = 0;
    int method = 0;
    int choice = 0;
    bool flag;
    nlohmann::json j = nlohmann::json::object();
    j["name"] = signal->getSignalName();
    SignalPtr quantizedSignal = copySignal(signal, j);
    std::vector<double> data = quantizedSignal->getData();
    SignalPtr quantizedSignalLine = copySignal(signal, j);
    while (choice != 2) {
        std::cout << "=================SIGNAL QUANTIZATION MENU=================\n"
                  << "1. Quantize signal.\n"
                  << "2. Return.\n"
                  << "Choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                std::cout << "=================PARAMETERS INPUT=================\n";
                while (level <= 0) {
                    std::cout << "Input number of levels (greater than 0): ";
                    std::cin >> level;
                }
                while (method != 1 && method != 2) {
                    std::cout << "\nChoose method of point assigment:\n"
                              << "1. Round points.\n"
                              << "2. Floor points.\n"
                              << "Choice: ";
                    std::cin >> method;
                }
                flag  = (method == 1);
                quantizedSignal->setData(Quantizer::uniformQuantize(data, level, flag));
                quantizationPlotMenu(quantizedSignal, signal);
                method = 0;
                level = 0;
                break;
            case 2:
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }
}

void quantizationPlotMenu(const SignalPtr &quantizedSignal, const SignalPtr &originalSignal) {
    int choice = 0;
    nlohmann::json j = nlohmann::json::object();
    j["name"] = originalSignal->getSignalName();
    SignalPtr continuousSignal = copySignal(originalSignal, j);
    continuousSignal->setSamplingRate(originalSignal->getSamplingRate()*100);
    continuousSignal->generate();
    while (choice != 5) {
        std::cout << "=================QUANTIZED SIGNAL MENU=================\n"
                  << "1. Quantized signal plots.\n"
                  << "2. Compare signal.\n"
                  << "3. Show results.\n"
                  << "4. Save signal.\n"
                  << "5. Return.\n"
                  << "Choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                plots(quantizedSignal->getData(), quantizedSignal->getTime(), "Sygnal po kwantyzacji");
                break;
            case 2:
                compareQuanSignals(quantizedSignal, originalSignal, continuousSignal);
                break;
            case 3:
                showQuanRecoResults(quantizedSignal, originalSignal);
                break;
            case 4:
                saveSignal(quantizedSignal);
                break;
            case 5:
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }
}

void compareQuanSignals(const SignalPtr &quantizedSignal, const SignalPtr &originalSignal, const SignalPtr &originalLine) {
    plt::plot(originalLine->getTime(), originalLine->getData(),
              { {"color", "orchid"} });
    plt::scatter(quantizedSignal->getTime(), quantizedSignal->getData(),
                 100.0,
                 {{"marker", "."}, {"color", "orangered"} });
    plt::scatter(originalSignal->getTime(), originalSignal->getData(),
                 100.0,
                 {{"marker", "x"}, {"color", "navy"} });
    plt::title(quantizedSignal->getSignalName() + " - kwantyzacja");
    plt::grid(true);
    plt::xlabel("t [s]");
    plt::ylabel("A", {{"rotation", "horizontal"}});
    plt::show();
    plt::close();
}

std::pair<std::vector<double>, std::vector<double>> fakeZOH(const std::vector<double> data, const std::vector<double> time) {
    std::vector<double> newData;
    std::vector<double> newTime;
    for (int i = 0; i < data.size() - 1; i++) {
        newData.push_back(data[i]);
        newTime.push_back(time[i]);
        newData.push_back(data[i]);
        newTime.push_back(time[i+1]);
    }
    return {newData, newTime};
}

void reconstructionMenu(const SignalPtr& signal) {
    int multiplier = 1;
    int choice = 0;
    std::vector<double> reconstructed;
    std::vector<double> reconstructedTimes;
    std::vector<double> fakeZohData;
    std::vector<double> fakeZohTime;
    nlohmann::json j = nlohmann::json::object();
    j["name"] = signal->getSignalName();
    std::cout << "=================SIGNAL RECONSTRUCTION MENU=================\n";
    while (choice != 4) {
        std::cout << "Choose reconstruction choice\n"
                  << "1. First order hold.\n"
                  << "2. Zero order hold.\n"
                  << "3. Sinc reconstruction.\n"
                  << "4. Return.\n"
                  << "Choice: ";
        std::cin >> choice;
        while (multiplier <= 1 && choice != 4) {
            std::cout << "Input multiplier: ";
            std::cin >> multiplier;
        }
        switch (choice) {
            case 1:
                std::tie(reconstructed, reconstructedTimes) =
                        SignalReconstruction::reconstructFOH(signal->getData(),
                                                             signal->getTime().front(),
                                                             signal->getSamplingRate(),
                                                             multiplier);
                break;
            case 2:
                std::tie(reconstructed, reconstructedTimes) =
                        SignalReconstruction::reconstructZOH(signal->getData(),
                                                             signal->getTime().front(),
                                                             signal->getSamplingRate(),
                                                             multiplier);
                std::tie(fakeZohData, fakeZohTime) = fakeZOH(signal->getData(), signal->getTime());
                break;
            case 3:
                std::tie(reconstructed, reconstructedTimes) =
                        SignalReconstruction::reconstructSinc(signal->getData(),
                                                              signal->getTime().front(),
                                                              signal->getSamplingRate(),
                                                              multiplier);
                break;
            case 4:
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
        if (choice != 4) {
            SignalPtr reconstructedSignal = copySignal(signal, j);
            reconstructedSignal->setData(reconstructed);
            reconstructedSignal->setTime(reconstructedTimes);
            reconstructedSignal->setSamplingRate(signal->getSamplingRate() * multiplier);
            SignalPtr reconstructedSignalLine = copySignal(signal, j);
            reconstructedSignalLine->setData(fakeZohData);
            reconstructedSignalLine->setTime(fakeZohTime);
            reconstructionPlotMenu(signal, reconstructedSignal, reconstructedSignalLine, choice);
            multiplier = 0;
        }
    }
}

void reconstructionPlotMenu (const SignalPtr& signal, const SignalPtr& reconstructedSignal, const SignalPtr& reconstructedSignalLine, int choosenSignalRecon) {
    int choice = 0;
    while (choice != 6) {
        std::cout << "=================RECONSTRUCTED SIGNAL MENU=================\n"
                  << "1. Original signal plots.\n"
                  << "2. Reconstructed signal plots.\n"
                  << "3. Compare signals.\n"
                  << "4. Show results.\n"
                  << "5. Save signal.\n"
                  << "6. Return.\n"
                  << "Choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                plots(signal->getData(), signal->getTime(), signal->getSignalName());
                break;
            case 2:
                plots(reconstructedSignal->getData(), reconstructedSignal->getTime(), "Sygnal po rekonstrukcji");
                break;
            case 3:
                compareRecoSignals(reconstructedSignal, signal, reconstructedSignalLine, choosenSignalRecon);
                break;
            case 4:
                showQuanRecoResults(reconstructedSignal, signal);
                break;
            case 5:
                saveSignal(reconstructedSignal);
                break;
            case 6:
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }
}

void compareRecoSignals(const SignalPtr &reconstructedSignal, const SignalPtr &originalSignal, const SignalPtr &reconstructedSignalLine, int choice) {
    nlohmann::json j = nlohmann::json::object();
    j["name"] = originalSignal->getSignalName();
    std::vector<double> reconstructed;
    std::vector<double> reconstructedTimes;
    SignalPtr continuousSignal = copySignal(originalSignal, j);
    continuousSignal->setSamplingRate(continuousSignal->getSamplingRate()*100);
    continuousSignal->generate();
    plt::plot(continuousSignal->getTime(),continuousSignal->getData(),
              { {"linewidth", "3"}, {"color", "orchid"} });
    if (choice == 2) {
        plt::plot(reconstructedSignalLine->getTime(),reconstructedSignalLine->getData(),
                  { {"linewidth", "1"}, {"color", "lime"} });
    }
    if (choice == 1 || choice == 3) {
        plt::plot(reconstructedSignal->getTime(),reconstructedSignal->getData(),
                  { {"linewidth", "1"}, {"color", "lime"} });
    }
    plt::scatter(originalSignal->getTime(), originalSignal->getData(),
                 150.0,
                 {{"marker", "x"}, {"color", "midnightblue"} });
    plt::title(reconstructedSignal->getSignalName() + " - rekonstrukcja");
    plt::grid(true);
    plt::xlabel("t [s]");
    plt::ylabel("A", {{"rotation", "horizontal"}});
    plt::show();
    plt::close();
}

void showQuanRecoResults(const SignalPtr &resultSignal, const SignalPtr &originalSignal) {
    nlohmann::json j = nlohmann::json::object();
    j["name"] = originalSignal->getSignalName();
    SignalPtr continuousSignal = copySignal(originalSignal, j);
    continuousSignal->setSamplingRate(resultSignal->getSamplingRate());
    continuousSignal->generate();
    double mse = Measures::meanSquaredError(continuousSignal->getData(), resultSignal->getData());
    double snr = Measures::signalToNoiseRatio(continuousSignal->getData(), resultSignal->getData());
    double psnr = Measures::peakSignalToNoiseRatio(continuousSignal->getData(), resultSignal->getData());
    double md = Measures::maximumDifference(continuousSignal->getData(), resultSignal->getData());
    double enob = Measures::enob(continuousSignal->getData(), resultSignal->getData());
    std::cout << "=================SIGNAL METRICS=================\n";
    std::cout << "MSE: " << mse << std::endl;
    std::cout << "SNR: " << snr << std::endl;
    std::cout << "PSNR: " << psnr << std::endl;
    std::cout << "MD: " << md << std::endl;
    std::cout << "ENOB: " << enob << std::endl;
}

void aliasingMenu(const SignalPtr &originalSignal) {
    std::vector<double> reconstructed;
    std::vector<double> reconstructedTimes;
    int multiplier = 1;
    nlohmann::json j = nlohmann::json::object();
    j["name"] = originalSignal->getSignalName();
    std::cout << "=================SIGNAL CREATION MENU=================\n";
    SignalPtr aliasedSignal = std::make_shared<SinusoidalSignal>(getAmplitude(), getTerm(), originalSignal->getStartTime(), originalSignal->getDuration(), getSamplingRate());
    aliasedSignal->generate();
    SignalPtr originalSignalCopy = copySignal(originalSignal, j);
    SignalPtr aliasedSignalCopy = copySignal(aliasedSignal, j);
    int choice = 0;
    while (choice != 6) {
        std::cout << "=================ALIASING MENU=================\n"
                  << "1. Show original signals.\n"
                  << "2. Show original signals with lines.\n"
                  << "4. Show original signals both with better lines.\n"
                  << "5. Show reconstructed signals.\n"
                  << "6. Return.\n"
                  << "Choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                plotTwoSignals(originalSignal, aliasedSignal);
                break;
            case 2:
                plotTwoSignalsWithLines(originalSignal, aliasedSignal);
                break;
            case 4:
                std::cout << "Input multiplier for sinc reconstruction: ";
                std::cin >> multiplier;
                std::tie(reconstructed, reconstructedTimes) =
                        SignalReconstruction::reconstructSinc(originalSignal->getData(),
                                                              originalSignal->getTime().front(),
                                                              originalSignal->getSamplingRate(),
                                                              multiplier);
                originalSignalCopy->setData(reconstructed);
                originalSignalCopy->setTime(reconstructedTimes);
                originalSignalCopy->setSamplingRate(originalSignal->getSamplingRate() * multiplier);
                std::tie(reconstructed, reconstructedTimes) =
                        SignalReconstruction::reconstructSinc(aliasedSignal->getData(),
                                                              aliasedSignal->getTime().front(),
                                                              aliasedSignal->getSamplingRate(),
                                                              multiplier);
                aliasedSignalCopy->setData(reconstructed);
                aliasedSignalCopy->setTime(reconstructedTimes);
                aliasedSignalCopy->setSamplingRate(aliasedSignal->getSamplingRate() * multiplier);
                plotTwoSignalsBothWithBetterLines(originalSignal, aliasedSignal, originalSignalCopy, aliasedSignalCopy);
                break;
            case 5:
                std::cout << "Input multiplier for sinc reconstruction: ";
                std::cin >> multiplier;
                std::tie(reconstructed, reconstructedTimes) =
                        SignalReconstruction::reconstructSinc(originalSignal->getData(),
                                                              originalSignal->getTime().front(),
                                                              originalSignal->getSamplingRate(),
                                                              multiplier);
                originalSignalCopy->setData(reconstructed);
                originalSignalCopy->setTime(reconstructedTimes);
                originalSignalCopy->setSamplingRate(originalSignal->getSamplingRate() * multiplier);
                std::tie(reconstructed, reconstructedTimes) =
                        SignalReconstruction::reconstructSinc(aliasedSignal->getData(),
                                                              aliasedSignal->getTime().front(),
                                                              aliasedSignal->getSamplingRate(),
                                                              multiplier);
                aliasedSignalCopy->setData(reconstructed);
                aliasedSignalCopy->setTime(reconstructedTimes);
                aliasedSignalCopy->setSamplingRate(aliasedSignal->getSamplingRate() * multiplier);
                plotTwoSignals(originalSignalCopy, aliasedSignalCopy);
                break;
            case 6:
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }
}

void plotTwoSignals(const SignalPtr &originalSignal, const SignalPtr &aliasedSignal) {
    nlohmann::json j = nlohmann::json::object();
    j["name"] = originalSignal->getSignalName();
    SignalPtr continuousSignal = copySignal(originalSignal, j);
    continuousSignal->setSamplingRate(originalSignal->getSamplingRate());
    continuousSignal->generate();
    plt::plot(continuousSignal->getTime(), continuousSignal->getData(),
              { {"color", "orchid"} });
    plt::scatter(aliasedSignal->getTime(), aliasedSignal->getData(),
                 200.0,
                 {{"marker", "."}, {"color", "mediumspringgreen"}});
    plt::scatter(originalSignal->getTime(), originalSignal->getData(),
                 200.0,
                 {{"marker", "x"}, {"color", "midnightblue"}});
    plt::title(originalSignal->getSignalName() + " - aliasing");
    plt::grid(true);
    plt::xlabel("t [s]");
    plt::ylabel("A", {{"rotation", "horizontal"}});
    plt::show();
    plt::close();
}

void plotTwoSignalsWithLines(const SignalPtr &originalSignal, const SignalPtr &aliasedSignal) {
    plt::plot(originalSignal->getTime(), originalSignal->getData(),
              { {"marker", "x"}, {"markersize", "10"}, {"mec", "midnightblue"}, {"mfc", "midnightblue"}, {"color", "orchid"} });
    plt::plot(aliasedSignal->getTime(), aliasedSignal->getData(),
              { {"marker", "."}, {"markersize", "10"}, {"mec", "orangered"}, {"mfc", "orangered"}, {"color", "mediumspringgreen"} });
    plt::title(originalSignal->getSignalName() + " - aliasing");
    plt::grid(true);
    plt::xlabel("t [s]");
    plt::ylabel("A", {{"rotation", "horizontal"}});
    plt::show();
    plt::close();
}
void plotTwoSignalsBothWithBetterLines(const SignalPtr &originalSignal, const SignalPtr &aliasedSignal, const SignalPtr &originalLines, const SignalPtr &aliasedLines) {
    plt::plot(originalLines->getTime(), originalLines->getData(),
              { {"color", "orchid"} });
    plt::plot(aliasedLines->getTime(), aliasedLines->getData(),
              { {"color", "mediumspringgreen"} });
    plt::scatter(originalSignal->getTime(), originalSignal->getData(),
                 200.0,
                 {{"marker", "x"}, {"color", "midnightblue"}});
    plt::scatter(aliasedSignal->getTime(), aliasedSignal->getData(),
                 200.0,
                 {{"marker", "."}, {"color", "orangered"}});
    plt::title(originalSignal->getSignalName() + " - aliasing");
    plt::grid(true);
    plt::xlabel("t [s]");
    plt::ylabel("A", {{"rotation", "horizontal"}});
    plt::show();
    plt::close();
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