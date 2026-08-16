#include "ImportDetailRepository.hpp"
#include "Statement.hpp"

ImportDetailRepository::ImportDetailRepository(
    Database &db)
    : database(db)
{
}

bool ImportDetailRepository::save(
    ImportDetail &importDetail)
{

    auto stmt =
        database.prepare(
            R"(
        INSERT INTO ImportDetail
        (
            import_record_id,

            row_number,

            student_name,

            status,

            message
        )

        VALUES
        (
            ?,
            ?,
            ?,
            ?,
            ?
        )
        )");

    stmt->bindInt(
        1,
        importDetail.getImportRecordId());

    stmt->bindInt(
        2,
        importDetail.getRowNumber());

    stmt->bindText(
        3,
        importDetail.getStudentName());

    stmt->bindText(
        4,
        importDetail.getStatus());

    stmt->bindText(
        5,
        importDetail.getMessage());

    bool success = stmt->execute();

    if (success)
    {

        int id =
            database.lastInsertId();

        importDetail.setId(id);
    }

    return success;
}