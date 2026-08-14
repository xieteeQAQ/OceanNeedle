#pragma once

#include <sqlite3.h>
#include <filesystem>
#include <memory>

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

    std::unique_ptr<Statement> prepare(
        const std::string &sql);

    bool beginTransaction();

    bool commit();

    bool rollback();

    bool initialize();

    int lastInsertId();

private:
    std::filesystem::path locateDatabase();
};