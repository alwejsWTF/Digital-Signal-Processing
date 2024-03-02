#ifndef CYFROWEPRZETWARZANIESYGNALOW_SIGNAL_H
#define CYFROWEPRZETWARZANIESYGNALOW_SIGNAL_H

class Signal {
public:
    Signal() = default;
    virtual ~Signal() = default;

    virtual void generate() = 0;
    virtual void display() const = 0;
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_SIGNAL_H
