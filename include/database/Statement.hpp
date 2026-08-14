#pragma once

#include <sqlite3.h>
#include <string>

class Statement
{

private:
    sqlite3_stmt *stmt;

public:
    Statement(
        sqlite3 *db,
        const std::string &sql);

    ~Statement();

    bool bindText(
        int index,
        const std::string &value);

    bool bindInt(
        int index,
        int value);

    bool execute();

    void reset();

    int step();

    sqlite3_stmt* get();
};