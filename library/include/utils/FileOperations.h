#ifndef CYFROWEPRZETWARZANIESYGNALOW_FILEOPERATIONS_H
#define CYFROWEPRZETWARZANIESYGNALOW_FILEOPERATIONS_H

#include <vector>
#include <string>
#include <typedefs.h>
#include "nlohmann/json.hpp"

class FileOperations {
public:
    static void save(const SignalPtr& signal, const std::string& fileName);
    static std::pair<SignalPtr, nlohmann::json> load(const std::string& fileName);

    SignalPtr copySignal(const SignalPtr &signal, std::string signalType);
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_FILEOPERATIONS_H
