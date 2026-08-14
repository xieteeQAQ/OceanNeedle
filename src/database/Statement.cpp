#include "Statement.hpp"
#include <iostream>

Statement::Statement(
    sqlite3 *db,
    const std::string &sql)
{

    int result =
        sqlite3_prepare_v2(
            db,
            sql.c_str(),
            -1,
            &stmt,
            nullptr);

    if (result != SQLITE_OK)
    {

        std::cerr
            << "Prepare failed"
            << std::endl;

        stmt = nullptr;
    }
}

Statement::~Statement()
{

    if (stmt)
    {
        sqlite3_finalize(stmt);
    }
}

bool Statement::bindText(
    int index,
    const std::string &value)
{

    return sqlite3_bind_text(
               stmt,
               index,
               value.c_str(),
               -1,
               SQLITE_TRANSIENT) == SQLITE_OK;
}

bool Statement::bindInt(
    int index,
    int value)
{

    return sqlite3_bind_int(
               stmt,
               index,
               value) == SQLITE_OK;
}

bool Statement::execute()
{

    int result =
        sqlite3_step(stmt);

    return result == SQLITE_DONE;
}

void Statement::reset()
{

    sqlite3_reset(stmt);
}

int Statement::step()
{
    return sqlite3_step(stmt);
}

sqlite3_stmt *Statement::get()
{
    return stmt;
}