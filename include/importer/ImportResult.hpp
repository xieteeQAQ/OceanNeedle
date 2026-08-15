#pragma once

#include <string>
#include <vector>

#include "ImportDetail.hpp"
#include "ImportMode.hpp"

struct ImportDetailData
{

    int rowNumber;


    std::string studentName;


    ImportStatus status;


    std::string message;

};

class ImportResult
{

public:
    int successCount = 0;

    int failedCount = 0;

    int skippedCount = 0;

    std::vector<ImportDetailData> details;


    void addSuccess()
    {
        successCount++;
    }

    void addFailed()
    {
        failedCount++;
    }

    void addSkipped()
    {
        skippedCount++;
    }
};