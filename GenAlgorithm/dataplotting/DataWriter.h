#pragma once

#include "MainTypes.h"

#include <string>
#include <filesystem>

namespace dataplotting
{
class DataWriter
{
public:
    DataWriter(const std::string&);
    void saveData(const algorithm::types::ResultsPerIteration&);

private:
    std::string getFileName();

    const std::filesystem::path appPath;
    const std::string dataDirName{"results"};
};
}
