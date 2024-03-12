#ifndef CYFROWEPRZETWARZANIESYGNALOW_SIGNAL_H
#define CYFROWEPRZETWARZANIESYGNALOW_SIGNAL_H

#include <vector>
#include <functional>

class Signal {
protected:
    std::vector<double> data;
    double startTime;
    double duration;
    std::function<double(double)> signalFunction;
public:
    Signal(double startTime, double duration, const std::function<double(double)> &func);
    virtual ~Signal() = default;

    virtual void generate();
    virtual void display() const;

    std::vector<double> getData() const;
    void setData(const std::vector<double> &data);

    double getStartTime() const;
    double getDuration() const;

    void setStartTime(double startTime);
    void setDuration(double duration);
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_SIGNAL_H
