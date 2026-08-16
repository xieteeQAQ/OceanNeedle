#include "ImportService.hpp"

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