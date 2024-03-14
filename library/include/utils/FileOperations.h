#ifndef CYFROWEPRZETWARZANIESYGNALOW_FILEOPERATIONS_H
#define CYFROWEPRZETWARZANIESYGNALOW_FILEOPERATIONS_H

#include <vector>
#include <string>
#include <typedefs.h>

class FileOperations {
public:
    FileOperations();
    ~FileOperations() = default;
    static void save(const SignalPtr& signal, const std::string& fileName);
    static SignalPtr load(const std::string& fileName);
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_FILEOPERATIONS_H
