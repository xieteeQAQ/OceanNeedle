#include "PersonRepository.hpp"
#include "Statement.hpp"

PersonRepository::PersonRepository(
    Database &db)
    : database(db)
{
}

bool PersonRepository::save(
    Person &person)
{

    auto stmt =
        database.prepare(
            R"(
        INSERT INTO Person
        (
            name,
            name_type,
            gender,
            gender_confidence,
            residence,
            residence_confidence
        )

        VALUES
        (
            ?,
            ?,
            ?,
            ?,
            ?,
            ?
        );
        )");

    stmt->bindText(
        1,
        person.getName());

    stmt->bindText(
        2,
        person.getNameType());

    stmt->bindText(
        3,
        person.getGender());

    stmt->bindInt(
        4,
        person.getGenderConfidence());

    stmt->bindText(
        5,
        person.getResidence());

    stmt->bindInt(
        6,
        person.getResidenceConfidence());

    bool result =
        stmt->execute();

    if (result)
    {
        int id =
            database.lastInsertId();

        person.setId(id);
    }

    return result;
}