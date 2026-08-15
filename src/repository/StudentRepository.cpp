#include "StudentRepository.hpp"
#include "Statement.hpp"

StudentRepository::StudentRepository(
    Database &db)
    : database(db)
{
}

bool StudentRepository::save(
    Student &student)
{

    auto stmt =
        database.prepare(
            R"(
        INSERT INTO Student
        (
            person_id,
            class_id
        )

        VALUES
        (
            ?,
            ?
        );
        )");

    stmt->bindInt(
        1,
        student.getPersonId());

    stmt->bindInt(
        2,
        student.getClassId());

    bool result =
        stmt->execute();

    return result;
}

std::unique_ptr<Student> StudentRepository::findByPersonId(
    int personId)
{

    auto stmt =
        database.prepare(
            R"(
        SELECT
            person_id,
            class_id
        FROM
            Student
        WHERE
            person_id = ?;
        )");

    stmt->bindInt(
        1,
        personId);

    std::unique_ptr<Student> result = nullptr;

    int code =
        stmt->step();

    if (code == SQLITE_ROW)
    {
        int studentPersonId =
            sqlite3_column_int(
                stmt->get(),
                0);
        int studentClassId =
            sqlite3_column_int(
                stmt->get(),
                1);

        result =
            std::make_unique<Student>(
                studentPersonId,
                studentClassId);
    }

    return result;
}