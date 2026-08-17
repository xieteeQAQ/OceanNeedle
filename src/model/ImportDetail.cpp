#include "ImportDetail.hpp"

ImportDetail::ImportDetail(
    int importRecordId,
    int rowNumber,
    std::string studentName,
    ImportStatus status,
    std::string message)
{

    this->importRecordId = importRecordId;

    this->rowNumber = rowNumber;

    this->studentName = studentName;

    if (status == ImportStatus::FAILED)
    {

        this->status = "FAILED";
    }
    else if (status == ImportStatus::SKIPPED)
    {

        this->status = "SKIPPED";
    }
    else if (status == ImportStatus::SUCCESS)
    {
        
        this->status = "SUCCESS";
    }

    this->message = message;
}

int ImportDetail::getId() const
{

    return this->id;
}

void ImportDetail::setId(int id)
{

    this->id = id;
}

int ImportDetail::getImportRecordId() const
{

    return this->importRecordId;
}

int ImportDetail::getRowNumber() const
{

    return this->rowNumber;
}

std::string ImportDetail::getStudentName() const
{

    return this->studentName;
}

std::string ImportDetail::getStatus() const
{

    return this->status;
}

std::string ImportDetail::getMessage() const
{

    return this->message;
}
