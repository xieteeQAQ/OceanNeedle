#pragma once

#include "ImportMode.hpp"

#include <string>

class ImportDetail
{

private:
    int id;

    int importRecordId;

    int rowNumber;

    std::string studentName;

    std::string status;

    std::string message;

public:
    ImportDetail(
        int importRecordId,
        int rowNumber,
        std::string studentName,
        ImportStatus status,
        std::string message);

    int getId() const;

    void setId(int id);

    int getImportRecordId() const;

    int getRowNumber() const;

    std::string getStudentName() const;

    std::string getStatus() const;

    std::string getMessage() const;
};