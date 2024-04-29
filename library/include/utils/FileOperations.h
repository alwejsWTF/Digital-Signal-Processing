#ifndef CYFROWEPRZETWARZANIESYGNALOW_FILEOPERATIONS_H
#define CYFROWEPRZETWARZANIESYGNALOW_FILEOPERATIONS_H

#include <vector>
#include <string>
#include <typedefs.h>

class FileOperations {
public:
    static void save(const SignalPtr& signal, const std::string& fileName);
    static std::pair<SignalPtr, std::string> load(const std::string& fileName);
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_FILEOPERATIONS_H
