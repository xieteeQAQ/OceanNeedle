#pragma once

#include <sqlite3.h>
#include <filesystem>
#include "Statement.hpp"

class Database
{
private:
    sqlite3 *db;
    std::filesystem::path dbPath;

public:
    Database();

    ~Database();

    bool isConnected();

    bool execute(
        const std::string &sql);

    Statement *prepare(
        const std::string &sql);

    bool beginTransaction();

    bool commit();

    bool rollback();

    bool initialize();

    int lastInsertId();

private:
    std::filesystem::path locateDatabase();
};