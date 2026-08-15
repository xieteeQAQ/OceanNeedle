#pragma once

#include <string>

class ImportRecord
{

private:
    int id;

    std::string fileName;

    std::string importTime;

    int successCount;

    int failedCount;

public:
    ImportRecord(
        std::string fileName,
        std::string importTime,
        int successCount,
        int failedCount);

    ImportRecord(
        int id,
        std::string fileName,
        std::string importTime,
        int successCount,
        int failedCount);

    int getId() const;

    void setId(int id);

    std::string getFileName() const;

    std::string getImportTime() const;

    int getSuccessCount() const;

    int getFailedCount() const;

    static std::string getCurrentTime();
};