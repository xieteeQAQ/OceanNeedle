#include "ImportRecord.hpp"

#include <ctime>
#include <iostream>

ImportRecord::ImportRecord(
    std::string fileName,
    std::string importTime,
    int successCount,
    int failedCount)
{
    this->fileName = fileName;

    this->importTime = importTime;

    this->successCount = successCount;

    this->failedCount = failedCount;

    id = -1;
}

ImportRecord::ImportRecord(
    int id,
    std::string fileName,
    std::string importTime,
    int successCount,
    int failedCount)
{
    this->id = id;

    this->fileName = fileName;

    this->importTime = importTime;

    this->successCount = successCount;

    this->failedCount = failedCount;
}

int ImportRecord::getId() const
{
    return id;
}

void ImportRecord::setId(
    int id)
{
    this->id = id;
}

std::string ImportRecord::getFileName() const
{

    return fileName;
}

std::string ImportRecord::getImportTime() const
{
    return importTime;
}

int ImportRecord::getSuccessCount() const
{
    return successCount;
}

int ImportRecord::getFailedCount() const
{
    return failedCount;
}

std::string ImportRecord::getCurrentTime()
{
    std::time_t now =
        std::time(nullptr);

    char buffer[20];

    std::strftime(
        buffer,
        sizeof(buffer),
        "%Y-%m-%d %H:%M:%S",
        std::localtime(&now));

    return std::string(buffer);
}