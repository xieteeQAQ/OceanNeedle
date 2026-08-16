#include "ClassRepository.hpp"
#include "Statement.hpp"

ClassRepository::ClassRepository(
    Database &db)
    : database(db)
{
}

std::unique_ptr<Class> ClassRepository::findByNumber(
    const std::string &number,
    int majorId)
{

    auto stmt =
        database.prepare(
            R"(
        SELECT
            id,
            class_number,
            major_id

        FROM Class

        WHERE class_number = ?
        AND major_id = ?;
        )");

    stmt->bindText(
        1,
        number);

    stmt->bindInt(
        2,
        majorId);

    std::unique_ptr<Class> result = nullptr;

    int code = stmt->step();

    if (code == SQLITE_ROW)
    {

        int id =
            sqlite3_column_int(
                stmt->get(),
                0);

        std::string classNumber =
            reinterpret_cast<const char *>(
                sqlite3_column_text(
                    stmt->get(),
                    1));

        int major =
            sqlite3_column_int(
                stmt->get(),
                2);

        result =
            std::make_unique<Class>(
                id,
                classNumber,
                major);
    }

    return result;
}

bool ClassRepository::save(
    Class &classInfo)
{

    auto stmt =
        database.prepare(
            R"(
        INSERT INTO Class
        (
            class_number,
            major_id
        )

        VALUES
        (
            ?,
            ?
        );
        )");

    stmt->bindText(
        1,
        classInfo.getClassNumber());

    stmt->bindInt(
        2,
        classInfo.getMajorId());

    bool result = stmt->execute();

    if (result)
    {
        classInfo.setId(
            database.lastInsertId());
    }

    return result;
}

std::unique_ptr<Class> ClassRepository::findById(
    int id)
{

    auto stmt =
        database.prepare(
            R"(
        SELECT
            id,
            class_number,
            major_id

        FROM Class

        WHERE id = ?;
        )");

    stmt->bindInt(
        1,
        id);

    std::unique_ptr<Class> result = nullptr;

    int code = stmt->step();

    if (code == SQLITE_ROW)
    {

        int classId =
            sqlite3_column_int(
                stmt->get(),
                0);

        std::string classNumber =
            reinterpret_cast<const char *>(
                sqlite3_column_text(
                    stmt->get(),
                    1));

        int major =
            sqlite3_column_int(
                stmt->get(),
                2);

        result =
            std::make_unique<Class>(
                classId,
                classNumber,
                major);
    }

    return result;
}

std::unique_ptr<Class> ClassRepository::findOrCreateByNumber(
    const std::string &number,
    int majorId)
{

    auto classInfo =
        findByNumber(
            number,
            majorId);

    if (!classInfo)
    {

        Class newClass(
            number,
            majorId);

        if (save(newClass))
        {
            classInfo =
                std::make_unique<Class>(
                    newClass);
        }
    }

    return classInfo;
}