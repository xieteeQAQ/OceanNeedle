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

    bool result = stmt->execute();

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

    int code = stmt->step();

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

bool StudentRepository::exists(
    int personId,
    int classId)
{

    auto stmt =
        database.prepare(
            R"(
        SELECT 1
        FROM Student
        WHERE person_id=?
        AND class_id=?
        LIMIT 1;
        )");

    stmt->bindInt(
        1,
        personId);

    stmt->bindInt(
        2,
        classId);

    return stmt->step() == SQLITE_ROW;
}

std::vector<Student> StudentRepository::findAll()
{

    std::vector<Student> result;

    auto stmt = database.prepare(
        "SELECT person_id, class_id FROM Student;");

    while (stmt->step() == SQLITE_ROW)
    {
        int personId = sqlite3_column_int(stmt->get(), 0);
        int classId = sqlite3_column_int(stmt->get(), 1);

        result.push_back(Student(personId, classId));
    }

    return result;
}