#ifndef CYFROWEPRZETWARZANIESYGNALOW_SIGNAL_H
#define CYFROWEPRZETWARZANIESYGNALOW_SIGNAL_H

#include <vector>
#include <iostream>

class Signal {
public:
    Signal();
    virtual ~Signal();

    virtual void generate() = 0;
    virtual void display() const = 0;
};


#endif //CYFROWEPRZETWARZANIESYGNALOW_SIGNAL_H
