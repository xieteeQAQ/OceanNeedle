#include "CollegeRepository.hpp"
#include "Statement.hpp"

CollegeRepository::CollegeRepository(
    Database &db)
    : database(db)
{
}

bool CollegeRepository::save(
    College &college)
{

    auto stmt =
        database.prepare(
            R"(
        INSERT INTO College
        (
            name
        )

        VALUES
        (
            ?
        );
        )");

    stmt->bindText(
        1,
        college.getName());

    bool result =
        stmt->execute();

    if (result)
    {
        int id =
            database.lastInsertId();

        college.setId(id);
    }

    return result;
}

std::unique_ptr<College> CollegeRepository::findByName(
    const std::string &name)
{

    auto stmt =
        database.prepare(
            R"(
        SELECT
            id,
            name
        FROM
            College
        WHERE
            name = ?;
        )");

    stmt->bindText(
        1,
        name);

    std::unique_ptr<College> result = nullptr;

    int code =
        stmt->step();

    if (code == SQLITE_ROW)
    {

        int id =
            sqlite3_column_int(
                stmt->get(),
                0);

        std::string collegeName =
            reinterpret_cast<const char *>(
                sqlite3_column_text(
                    stmt->get(),
                    1));

        result = std::make_unique<College>(
            id,
            collegeName);
    }

    return result;
}

std::unique_ptr<College> CollegeRepository::findById(
    int id)
{

    auto stmt =
        database.prepare(
            R"(
        SELECT
            id,
            name
        FROM
            College
        WHERE
            id = ?;
        )");

    stmt->bindInt(
        1,
        id);

    std::unique_ptr<College> result = nullptr;

    int code =
        stmt->step();

    if (code == SQLITE_ROW)
    {

        int collegeId =
            sqlite3_column_int(
                stmt->get(),
                0);

        std::string collegeName =
            reinterpret_cast<const char *>(
                sqlite3_column_text(
                    stmt->get(),
                    1));

        result = std::make_unique<College>(
            collegeId,
            collegeName);
    }

    return result;
}

std::unique_ptr<College> CollegeRepository::findOrCreateByName(
    const std::string &name)
{

    auto college =
        findByName(name);

    if (!college)
    {

        College newCollege(name);

        if (save(newCollege))
        {
            college =
                std::make_unique<College>(
                    newCollege);
        }
    }

    return college;
}