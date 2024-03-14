#ifndef CYFROWEPRZETWARZANIESYGNALOW_FILEOPERATIONS_H
#define CYFROWEPRZETWARZANIESYGNALOW_FILEOPERATIONS_H

#include <Signal.h>
#include <vector>
#include <string>

class FileOperations {
private:
    Signal signal;
public:
    FileOperations();
    ~FileOperations() = default;
    static void save(const std::vector<double>& data, const std::string& fileName);
    static std::vector<double> load(const std::string& fileName);
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_FILEOPERATIONS_H
