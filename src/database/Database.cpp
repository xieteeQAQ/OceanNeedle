#include "Database.hpp"
#include <iostream>

namespace fs = std::filesystem;

Database::Database()
{

    dbPath = locateDatabase();

    int result =
        sqlite3_open(
            dbPath.string().c_str(),
            &db);

    if (result != SQLITE_OK)
    {

        std::cerr
            << "Cannot open database: "
            << sqlite3_errmsg(db)
            << std::endl;

        db = nullptr;
    }
}

Database::~Database()
{

    if (db)
    {
        sqlite3_close(db);
    }
}

bool Database::isConnected()
{

    return db != nullptr;
}

fs::path Database::locateDatabase()
{

    fs::path path =
        "database/test.db";

    return path;
}

bool Database::execute(
    const std::string &sql)
{

    char *errorMessage = nullptr;

    int result =
        sqlite3_exec(
            db,
            sql.c_str(),
            nullptr,
            nullptr,
            &errorMessage);

    if (result != SQLITE_OK)
    {

        std::cerr
            << "SQL error: "
            << errorMessage
            << std::endl;

        sqlite3_free(errorMessage);

        return false;
    }

    return true;
}

std::unique_ptr<Statement> Database::prepare(
    const std::string &sql)
{

    return std::make_unique<Statement>(
        db,
        sql);
}

bool Database::beginTransaction()
{

    return execute(
        "BEGIN TRANSACTION;");
}

bool Database::commit()
{

    return execute(
        "COMMIT;");
}

bool Database::rollback()
{

    return execute(
        "ROLLBACK;");
}

bool Database::initialize()
{

    beginTransaction();

    execute(
        "PRAGMA foreign_keys = ON;");

    bool success = true;

    success &= execute(R"(
    CREATE TABLE IF NOT EXISTS College
    (
        id INTEGER PRIMARY KEY,
        name TEXT NOT NULL UNIQUE
    );
    )");

    success &= execute(R"(
    CREATE TABLE IF NOT EXISTS Major
    (
        id INTEGER PRIMARY KEY,

        name TEXT NOT NULL,

        college_id INTEGER NOT NULL,

        FOREIGN KEY(college_id)
            REFERENCES College(id),

        UNIQUE(name,college_id)
    );
    )");

    success &= execute(R"(
    CREATE TABLE IF NOT EXISTS Class
    (
        id INTEGER PRIMARY KEY,

        class_number TEXT NOT NULL,

        major_id INTEGER NOT NULL,

        FOREIGN KEY(major_id)
            REFERENCES Major(id),

        UNIQUE(major_id,class_number)
    );
    )");

    success &= execute(R"(
    CREATE TABLE IF NOT EXISTS Person
    (
        id INTEGER PRIMARY KEY,

        name TEXT NOT NULL,

        name_type TEXT NOT NULL,

        gender TEXT,

        gender_confidence INTEGER NOT NULL,

        residence TEXT,

        residence_confidence INTEGER NOT NULL
    );
    )");

    success &= execute(R"(
    CREATE TABLE IF NOT EXISTS Student
    (
        person_id INTEGER PRIMARY KEY,

        class_id INTEGER NOT NULL,

        FOREIGN KEY(person_id)
            REFERENCES Person(id),

        FOREIGN KEY(class_id)
            REFERENCES Class(id)
    );
    )");

    if (success)
    {
        commit();
    }
    else
    {
        rollback();
    }

    return success;
}

int Database::lastInsertId()
{

    return static_cast<int>(
        sqlite3_last_insert_rowid(db));
}