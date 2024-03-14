#ifndef CYFROWEPRZETWARZANIESYGNALOW_TYPEDEFS_H
#define CYFROWEPRZETWARZANIESYGNALOW_TYPEDEFS_H

#include <memory>

class Signal;

template<class T>
using Ptr = std::shared_ptr<T>;

typedef std::shared_ptr<Signal> SignalPtr;

#endif //CYFROWEPRZETWARZANIESYGNALOW_TYPEDEFS_H
