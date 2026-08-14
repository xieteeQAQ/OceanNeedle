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