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

std::unique_ptr<Person> PersonRepository::findByName(
    const std::string &name)
{

    auto stmt =
        database.prepare(
            R"(
        SELECT
            id,
            name,
            name_type,
            gender,
            gender_confidence,
            residence,
            residence_confidence
        FROM
            Person
        WHERE
            name = ?;
        )");

    stmt->bindText(
        1,
        name);

    std::unique_ptr<Person> result = nullptr;

    int code =
        stmt->step();

    if (code == SQLITE_ROW)
    {
        int id =
            sqlite3_column_int(
                stmt->get(),
                0);

        std::string personName =
            reinterpret_cast<const char *>(
                sqlite3_column_text(
                    stmt->get(),
                    1));

        std::string nameType =
            reinterpret_cast<const char *>(
                sqlite3_column_text(
                    stmt->get(),
                    2));

        std::string gender =
            reinterpret_cast<const char *>(
                sqlite3_column_text(
                    stmt->get(),
                    3));

        int genderConfidence =
            sqlite3_column_int(
                stmt->get(),
                4);

        std::string residence =
            reinterpret_cast<const char *>(
                sqlite3_column_text(
                    stmt->get(),
                    5));

        int residenceConfidence =
            sqlite3_column_int(
                stmt->get(),
                6);

        result =
            std::make_unique<Person>(
                id,
                personName,
                nameType,
                gender,
                genderConfidence,
                residence,
                residenceConfidence);
                
        result->setId(id);
    }

    return result;
}

std::unique_ptr<Person> PersonRepository::findById(
    int id)
{

    auto stmt =
        database.prepare(
            R"(
        SELECT
            id,
            name,
            name_type,
            gender,
            gender_confidence,
            residence,
            residence_confidence
        FROM
            Person
        WHERE
            id = ?;
        )");

    stmt->bindInt(
        1,
        id);

    std::unique_ptr<Person> result = nullptr;

    int code =
        stmt->step();

    if (code == SQLITE_ROW)
    {
        int id =
            sqlite3_column_int(
                stmt->get(),
                0);

        std::string personName =
            reinterpret_cast<const char *>(
                sqlite3_column_text(
                    stmt->get(),
                    1));

        std::string nameType =
            reinterpret_cast<const char *>(
                sqlite3_column_text(
                    stmt->get(),
                    2));

        std::string gender =
            reinterpret_cast<const char *>(
                sqlite3_column_text(
                    stmt->get(),
                    3));

        int genderConfidence =
            sqlite3_column_int(
                stmt->get(),
                4);

        std::string residence =
            reinterpret_cast<const char *>(
                sqlite3_column_text(
                    stmt->get(),
                    5));

        int residenceConfidence =
            sqlite3_column_int(
                stmt->get(),
                6);

        result =
            std::make_unique<Person>(
                id,
                personName,
                nameType,
                gender,
                genderConfidence,
                residence,
                residenceConfidence);

        result->setId(id);
    }

    return result;
}

std::unique_ptr<Person> PersonRepository::findOrCreateByName(
    const std::string &name,
    const std::string &nameType,
    const std::string &gender,
    int genderConfidence,
    const std::string &residence,
    int residenceConfidence)
{
    auto person =
        findByName(name);

    if (!person)
    {

        Person newPerson(
            name,
            nameType,
            gender,
            genderConfidence,
            residence,
            residenceConfidence);

        if (save(newPerson))
        {
            person =
                std::make_unique<Person>(
                    newPerson);
        }
    }

    return person;
}