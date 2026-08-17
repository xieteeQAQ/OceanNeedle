#include "ImportService.hpp"

#include <iostream>

ImportService::ImportService(
    StudentImporter &importer,
    StudentImportService &studentImportService,
    ImportRecordRepository &recordRepo,
    ImportDetailRepository &detailRepo)
    : importer(importer),
      studentImportService(studentImportService),
      recordRepo(recordRepo),
      detailRepo(detailRepo)
{
}

std::optional<ImportResult> ImportService::importFromCSV(const std::string &filename)
{

    std::vector<StudentRow> studentRows = importer.readCSV(filename);

    if (studentRows.empty())
        return std::nullopt;

    ImportResult result = studentImportService.importStudents(studentRows);

    auto record = saveImportRecord(filename, result);

    if (!record.has_value())
    {
        std::cerr << "record save failed\n";
        return std::nullopt;
    }

    if (!saveImportDetails(record->getId(), result))
    {
        std::cerr << "details save failed\n";
    }

    return result;
}

std::optional<ImportRecord> ImportService::saveImportRecord(
    const std::string &filename,
    const ImportResult &result)
{
    ImportRecord record(
        filename,
        ImportRecord::getCurrentTime(),
        result.successCount,
        result.failedCount);

    if (!recordRepo.save(record))
        return std::nullopt;

    return record;
}

bool ImportService::saveImportDetails(
    int recordId,
    const ImportResult &result)
{

    bool success = true;

    for (auto &d : result.details)
    {
        ImportDetail detail(
            recordId,
            d.rowNumber,
            d.studentName,
            d.status,
            d.message);

        if (!detailRepo.save(detail))
            success = false;
    }

    return success;
}