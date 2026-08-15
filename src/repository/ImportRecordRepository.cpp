#include "ImportRecordRepository.hpp"
#include "Statement.hpp"

#include <iostream>

ImportRecordRepository::ImportRecordRepository(
    Database &database)
    : database(database)
{
}

bool ImportRecordRepository::save(
    ImportRecord &record)
{

    auto stmt =
        database.prepare(
            R"(
        INSERT INTO ImportRecord
        (
            file_name,
            import_time,
            success_count,
            failed_count
        )

        VALUES
        (
            ?,
            ?,
            ?,
            ?
        );
        )");

    stmt->bindText(
        1,
        record.getFileName());

    stmt->bindText(
        2,
        record.getImportTime());

    stmt->bindInt(
        3,
        record.getSuccessCount());

    stmt->bindInt(
        4,
        record.getFailedCount());

    bool success = stmt->execute();

    if (success)
    {
        int id =
            database.lastInsertId();

        record.setId(id);
    }

    return success;
}