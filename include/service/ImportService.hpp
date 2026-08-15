#pragma once

#include "StudentImporter.hpp"
#include "StudentImportService.hpp"
#include "ImportRecordRepository.hpp"
#include "ImportDetailRepository.hpp"

class ImportService
{

private:
    StudentImporter &importer;

    StudentImportService &studentService;

    ImportRecordRepository &recordRepo;

    ImportDetailRepository &detailRepo;

public:
    ImportService(
        StudentImporter &importer,
        StudentImportService &studentService,
        ImportRecordRepository &recordRepo,
        ImportDetailRepository &detailRepo);

    ImportResult importStudents(
        const std::string &filename,
        int majorId);
};