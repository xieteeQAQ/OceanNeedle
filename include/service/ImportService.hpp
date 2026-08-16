#pragma once

#include <string>

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

    ImportResult importFromCSV(const std::string &filename);

private:
    bool saveImportRecord(
        const std::string &filename,
        const ImportResult &result,
        int &recordId);

    bool saveImportDetails(
        int recordId,
        const ImportResult &result);

    StudentImporter &importer;
    StudentImportService &studentImportService;
    ImportRecordRepository &recordRepo;
    ImportDetailRepository &detailRepo;
};