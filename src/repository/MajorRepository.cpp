#include "MajorRepository.hpp"
#include "Statement.hpp"

MajorRepository::MajorRepository(
    Database &db)
    : database(db)
{
}

std::unique_ptr<Major> MajorRepository::findByName(
    const std::string &name)
{

    auto stmt =
        database.prepare(
            R"(
        SELECT
            id,
            name,
            college_id

        FROM Major

        WHERE name = ?;
        )");

    stmt->bindText(
        1,
        name);

    std::unique_ptr<Major> result = nullptr;

    int code =
        stmt->step();

    if (code == SQLITE_ROW)
    {

        int id =
            sqlite3_column_int(
                stmt->get(),
                0);

        std::string majorName =
            reinterpret_cast<const char *>(
                sqlite3_column_text(
                    stmt->get(),
                    1));

        int college =
            sqlite3_column_int(
                stmt->get(),
                2);

        result =
            std::make_unique<Major>(
                id,
                majorName,
                college);
    }

    return result;
}

bool MajorRepository::save(
    Major &Major)
{

    auto stmt =
        database.prepare(
            R"(
        INSERT INTO Major
        (
            name,
            college_id
        )

        VALUES
        (
            ?,
            ?
        );
        )");

    stmt->bindText(
        1,
        Major.getName());

    stmt->bindInt(
        2,
        Major.getCollegeId());

    bool result =
        stmt->execute();

    if (result)
    {
        Major.setId(
            database.lastInsertId());
    }

    return result;
}