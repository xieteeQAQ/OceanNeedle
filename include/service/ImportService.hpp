#pragma once

#include <string>
#include <vector>
#include <optional>

#include "StudentImporter.hpp"
#include "StudentImportService.hpp"
#include "ImportRecordRepository.hpp"
#include "ImportDetailRepository.hpp"
#include "ImportResult.hpp"

class ImportService
{
public:
    ImportService(
        StudentImporter &importer,
        StudentImportService &studentImportService,
        ImportRecordRepository &recordRepo,
        ImportDetailRepository &detailRepo);

    std::optional<ImportResult> importFromCSV(const std::string &filename);

private:
    std::optional<ImportRecord> saveImportRecord(
        const std::string &filename,
        const ImportResult &result);

    bool saveImportDetails(
        int recordId,
        const ImportResult &result);

    StudentImporter &importer;
    StudentImportService &studentImportService;
    ImportRecordRepository &recordRepo;
    ImportDetailRepository &detailRepo;
};