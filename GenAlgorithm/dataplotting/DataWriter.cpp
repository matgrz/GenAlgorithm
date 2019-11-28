#include "DataWriter.h"

#include <ctime>
#include <fstream>

namespace dataplotting
{
DataWriter::DataWriter(const std::string& path) : appPath{path}
{
    if (!std::filesystem::exists(path + dataDirName))
        std::filesystem::create_directory(path + dataDirName);
}

void DataWriter::saveData(const algorithm::types::ResultsPerIteration& results)
{
    std::ofstream ofs(appPath / dataDirName / getFileName());
    ofs << "iteration,value,x, y\n";

    for (const auto& resultPair : results)
    {
        const int iteration = resultPair.first;
        for (const auto& result : resultPair.second)
            ofs << iteration << "," << result.z << "," << result.x << "," << result.y << "\n";
    }
    ofs.close();
}
std::string DataWriter::getFileName()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    std::string fileName{ std::to_string(1900 + ltm->tm_year) + "-" + std::to_string(1 + ltm->tm_mon) +
                          "-" + std::to_string(ltm->tm_mday) + "_" + std::to_string(1 + ltm->tm_hour) +
                          "-" + std::to_string(1 + ltm->tm_min) + "-" + std::to_string(1 + ltm->tm_sec) };

    return fileName.append("_result.csv");
}
}
