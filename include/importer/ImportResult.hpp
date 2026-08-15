#pragma once

#include <string>
#include <vector>

struct ImportError
{

    int row;

    std::string reason;
};

class ImportResult
{

public:
    int successCount = 0;

    int failedCount = 0;

    std::vector<ImportError> errors;

    void addSuccess()
    {
        successCount++;
    }

    void addError(
        int row,
        const std::string &reason)
    {

        failedCount++;

        errors.push_back(
            {row,
             reason});
    }
};