#ifndef CYFROWEPRZETWARZANIESYGNALOW_FILEOPERATIONS_H
#define CYFROWEPRZETWARZANIESYGNALOW_FILEOPERATIONS_H

#include <vector>
#include <string>

class FileOperations {
public:
    static void saveSignalData(const std::vector<double>& data, const std::string& fileName);
    static std::vector<double> loadSignalData(const std::string& fileName);
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_FILEOPERATIONS_H
